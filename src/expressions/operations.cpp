#include <blazar/core/graph.h>
#include <blazar/symbols.hpp>
#include <blazar/expressions/operations.hpp> 

namespace blazar::operations {

Negation::operator Symbol() const { 
    static symbol_t symbol {
        .kind = OPERATION,
        .name = "Negation"
    };
    return Symbol(reinterpret_cast<std::uintptr_t>(&symbol));
} 

Addition::operator Symbol() const {
    static symbol_t symbol {
        .kind = OPERATION,
        .name = "Addition"
    };
    return Symbol(reinterpret_cast<std::uintptr_t>(&symbol));
}

Division::operator Symbol() const {
    static symbol_t symbol {
        .kind = OPERATION,
        .name = "Negation"
    };
    return Symbol(reinterpret_cast<std::uintptr_t>(&symbol));
}

Subtraction::operator Symbol() const {
    static symbol_t symbol {
        .kind = OPERATION,
        .name = "Subtraction"
    };
    return Symbol(reinterpret_cast<std::uintptr_t>(&symbol));
}

Multiplication::operator Symbol() const {
    static symbol_t symbol {
        .kind = OPERATION,
        .name = "Multiplication"
    };
    return Symbol(reinterpret_cast<std::uintptr_t>(&symbol));
} 

Exponentiation::operator Symbol() const {
    static symbol_t symbol {
        .kind = OPERATION,
        .name = "Exponentiation"
    };
    return Symbol(reinterpret_cast<std::uintptr_t>(&symbol));
}
    
}