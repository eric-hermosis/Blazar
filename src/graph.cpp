#include <utility>
#include <cassert>
#include <blazar/trace.hpp>
#include <blazar/graph.hpp>

namespace blazar {

Vertex::Vertex(Symbol const& symbol, Type const& type, Layout const& layout) {
    node_ = Node::create(symbol, type, layout);
} 

Vertex::Vertex(Symbol const& symbol, Type const& type, Layout const& layout, Storage const& storage) {
    node_ = Node::create(symbol, type, layout);
    node_->set(storage);
} 

void Vertex::release() { 
    if (node_) {
        node_-> release();  
        node_ = nullptr;
    }  
}

void Vertex::copy(Vertex const& other) {
    if (node_ != other.node_) {  
        if (other.node_) {
            other.node_ -> acquire();
        }
        release();
        node_ = other.node_;
    }
}

void Vertex::move(Vertex & other) noexcept { 
    if (node_ != other.node_) {
        release();
        node_ = std::exchange(other.node_, nullptr);
    }
}

void Vertex::link(Vertex const& other) { 
    assert(node_);
    node_->link(other.node_);
}
 
void Vertex::prune() {
    assert(node_);
    node_->prune();
}
 
Vertex::operator bool() const noexcept {
    return node_ ? true : false;
}
 
}