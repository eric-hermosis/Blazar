#include <iostream>
#include <string_view>
#include <meta>
#include <cstddef>
#include <tuple>
#include <utility>
#include <cstdint>
#include <complex>
#include <stdfloat>
#include <meta>
#include <tuple>
#include <utility> 
#include <unordered_set>
#include <blazar/core/graph.h>
#include <blazar/graph/nodes.hpp>
#include <blazar/operations.hpp>
#include <blazar/variables.hpp>

#include <iostream>
#include <unordered_set>
#include <string>

#include <iostream>
#include <unordered_set>
#include <string>

void print(std::ostream& stream, const node_t* node, std::unordered_set<const node_t*>& visited, const std::string& prefix, bool is_last) {
    if (!node)
        return;

    stream << prefix; 
    stream << (is_last ? "└── " : "├── "); 
    stream << node->symbol.name;

    if (visited.count(node)) {
        stream << " [shared]\n";
        return;
    }

    stream << '\n'; 
    visited.insert(node);

    if (!node->sources || node->arity == 0)
        return;
 

    for (std::size_t index = 0; index < node->arity; ++index) {
        auto* child = node->sources[index];

        if (!child)
            continue;
 
        print(stream, child, visited, prefix + (is_last ? "    " : "│   "), (index + 1 == node->arity));
    }
}

void print(std::ostream& stream, const graph_t* graph) {
    if (!graph || !graph->head)
        return;

    std::unordered_set<const node_t*> visited;   
    visited.insert(graph->head);

    stream << graph->head->symbol.name << '\n';
    for (std::size_t index = 0; index < graph->head->arity; ++index) {
        auto* child = graph->head->sources[index]; 
        if (!child)
            continue;
 
        print(stream, child, visited, "", (index + 1 == graph->head->arity));
    }
}
 
using namespace blazar;

int main() { 
    Variable x; x.acquire();
    Variable y; y.acquire();
    Variable z; z.acquire();

    Graph graph(x*y + y*z + z*x);

    auto head = graph.head_;
    Node* node = head.node();
    graph_t g{&node->body_};
    print(std::cout, &g);
} 