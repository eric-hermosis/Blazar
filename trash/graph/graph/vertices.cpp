#include <blazar/graph/nodes.hpp>
#include <blazar/graph/vertices.hpp>
#include <utility>

namespace blazar {
 
Vertex::Vertex(Symbol const& symbol) {
    node_ = Node::allocate(symbol);
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

Vertex::operator bool() const noexcept {
    return node_ ? true : false;
}

auto Vertex::node() const noexcept -> Node* {
    return node_;
}

}