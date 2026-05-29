#include <cassert>
#include <stack>
#include <deque>
#include <vector>
#include <blazar/memory.hpp>
#include <blazar/core/memory.h> 

namespace blazar::host {

static allocator_t allocator {
    .name = "malloc",
    .allocate = [](std::size_t size) noexcept -> void* { return std::malloc(size); },
    .deallocate = [](void* address, std::size_t size) noexcept -> void { std::free(address); }
};

} namespace blazar { 
   
static struct {
    struct slot_t { alignas(Memory) std::byte bytes[sizeof(Memory)]; };
    std::stack<slot_t, std::deque<slot_t>> storage;
    std::stack<void*, std::vector<void*>> free;
} pool;  

auto Memory::allocate(std::size_t nbytes, Environment const& environment) -> Memory* {
    return new Memory(nbytes, environment);
}

void Memory::acquire() {
    ++references_; 
}

void Memory::release() { 
    assert(references_ > 0 && "Assertion error: releasing empty resource");
    if (--references_ == 0) { 
        delete this;
    }
}

auto Memory::operator new(std::size_t) -> void* {
    if (pool.free.empty()) {
        pool.storage.emplace();
        pool.free.push(&pool.storage.top());
    }
    void* address = pool.free.top();
    pool.free.pop();
    return address;
}
 
void Memory::operator delete(void* address, std::size_t) noexcept {
    pool.free.push(address);
}
  
Memory::Memory(std::size_t nbytes, Environment const& environment)
:   environment_(environment)
,   references_(1)
,   body_{
        .domain = HOST,
        .allocator = &host::allocator,
        .buffer = {
            .size = nbytes,
            .address = nullptr
        }
    }
{    
    body_.buffer.address = body_.allocator->allocate(body_.buffer.size);
}

Memory::~Memory() {
    if (body_.buffer.address) {
        body_.allocator->deallocate(body_.buffer.address, body_.buffer.size);
        body_.buffer.address = nullptr;
        body_.buffer.size = 0;
    }
}

auto Memory::size() const noexcept -> std::size_t {
    return body_.buffer.size;
}

auto Memory::environment() const noexcept -> Environment const& {
    return environment_;
}

auto Memory::references() const noexcept -> std::uint32_t {
    return references_;
}
  
}