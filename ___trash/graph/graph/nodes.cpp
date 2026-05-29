#include <stack>
#include <deque>
#include <vector>
#include <cassert>
#include <blazar/graph/nodes.hpp>

namespace blazar {

static struct {
    struct slot_t { alignas(Node) std::byte bytes[sizeof(Node)]; };
    std::stack<slot_t, std::deque<slot_t>> storage;
    std::stack<void*, std::vector<void*>> free;
} pool;

auto Node::allocate(Symbol const& symbol) -> Node* {
    return new Node(symbol);
}
 
auto Node::operator new(std::size_t) -> void* {
    if (pool.free.empty()) {
        pool.storage.emplace();
        pool.free.push(&pool.storage.top());
    }

    void* address = pool.free.top();
    pool.free.pop();
    return address;
}

void Node::operator delete(void* address, std::size_t) noexcept {
    pool.free.push(address);
}

Node::Node(Symbol const& symbol) 
:   references_(1)
,   body_ {
        .arity  = 0, 
        .symbol = {.name = symbol.name().data() }
} {} 

void Node::acquire() {
    ++references_; 
}

void Node::release() { 
    assert(references_ > 0 && "Assertion error: releasing empty resource");
    if (--references_ == 0) { 
        delete this;
    }
} 
    
void Node::link(Node* source) {
    body_.sources[body_.arity++] = &source->body_;
}

auto Node::references() const noexcept -> std::uint32_t {
    return references_;
}

}