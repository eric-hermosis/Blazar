#ifndef EDGES_HPP_0x45524943 
#define EDGES_HPP_0x45524943 

#include <blazar/graph/vertices.hpp>

namespace blazar {

class Node;

class Edge { 
public:
    constexpr Edge() = default;
    Edge(Vertex const& source, Vertex const& target);

private:
    Node* source_;
    Node* target_;
};

}

#endif 