#include <cassert>
#include <blazar/trace.hpp>
#include <stack>
#include <vector>
#include <deque>
#include <iostream>

namespace blazar { 

static thread_local struct {
    struct slot_t { alignas(Node) std::byte bytes[sizeof(Node)]; };
    std::stack<slot_t, std::deque<slot_t>> storage;
    std::stack<void*, std::vector<void*>> free;
} pool;  

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
    
Node::Node(Symbol const& symbol, Type const& type, Layout const& layout) 
:   references_(1)
,   arity_(0)
{
    shape_t shape;
    strides_t strides;

    for (auto dimension = 0; dimension < layout.rank(); dimension++) {
        shape.sizes[dimension] = layout.size(dimension);
        strides.sizes[dimension] = layout.stride(dimension);
    }

    body_ = new node_t {
        .name = symbol.name().data(),
        .type = type,
        .layout {
            .rank = layout.rank(),
            .size = layout.size(), 
            .shape   = std::move(shape),
            .strides = std::move(strides)
        }
    };
}

Node::~Node() {
    if (body_) {
        delete body_;
    }
}
 
auto Node::allocate(Symbol const& symbol, Type const& type, Layout const& layout) -> Node* {
    return new Node(symbol, type, layout);
}

void Node::acquire() {
    ++references_; 
}

void Node::release() { 
    assert(references_ > 0 && "Assertion error: releasing empty resource");
    if (--references_ == 0) { 
        for (auto index = 0; index < arity_; index++) {
            sources_[index] -> release(); 
        }
        delete this;
    }
}

void Node::link(Node* source) { 
    assert(source);
    source -> acquire();
    sources_[arity_++] = source; 
}

void Node::prune() {
    for (auto index = 0; index < arity_; index++) {
        sources_[index] -> release(); 
    }
    arity_ = 0;
}

}