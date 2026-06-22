#include <cassert>
#include <stack>
#include <deque>
#include <vector> 
#include <blazar/core/memory.h> 
#include <blazar/memory.hpp>

namespace blazar {    

void Memory::set(std::size_t nbytes, Environment const& environment) {
    environment_ = environment;
    
    auto const& allocator = std::visit( 
        [](auto const& domain) -> Allocator const& { return domain.allocator(); }, 
        environment
    );

    body_ = memory_t {
        .domain = HOST,
        .allocator = {
            .name       = allocator.name.data(),
            .allocate   = allocator.allocate,
            .deallocate = allocator.deallocate
        },
        .buffer = {
            .size    = nbytes,
            .address = nullptr
        }
    }; 
} 

static thread_local struct {
    std::stack<Memory> stack;
    std::stack<Memory*, std::vector<Memory*>> free; 
} pool; 
 
auto Memory::create(std::size_t nbytes, Environment const& environment) -> Memory* {
    if (pool.free.empty()) {
        pool.stack.emplace();
        pool.free.push(&pool.stack.top());
    }
    auto memory = pool.free.top();
    memory->set(nbytes, environment);
    memory->acquire();
    pool.free.pop();
    return memory; 
} 

void Memory::allocate() {
    if (!body_.buffer.address) {
        body_.buffer.address = body_.allocator.allocate(body_.buffer.size);
    }
}

void Memory::deallocate() {
    if (body_.buffer.address) {
        body_.allocator.deallocate(body_.buffer.address, body_.buffer.size);
        body_.buffer.address = nullptr;   
    }
}

void Memory::acquire() {
    ++references_;
}

void Memory::release() { 
    assert(references_ > 0 && "Assertion error: releasing empty resource");
    if (--references_ == 0) {  
        deallocate();
        pool.free.push(this);
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