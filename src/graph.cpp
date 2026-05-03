#include <blazar/graph.hpp>
#include <blazar/nodes.hpp>
#include <utility>

namespace blazar {
 
Vertex::Vertex(Symbol const& symbol, int arity) {
    node_ = Node::allocate(symbol, arity);
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

}