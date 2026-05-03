#include <blazar/core/graph.h>
#include <blazar/nodes.hpp> 
#include <blazar/variables.hpp>
#include <blazar/symbols.hpp>

namespace blazar {

void Variable::acquire() const {
    static symbol_t symbol {
        .kind = VARIABLE,
        .name = "Variable"
    };
    vertex_ = Vertex(Symbol(reinterpret_cast<std::uintptr_t>(&symbol)), 0);
}

}