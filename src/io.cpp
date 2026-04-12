#include <iostream>
#include "blazar/core/types.h"
#include "blazar/core/layout.h"
#include "blazar/types.hpp"
#include "blazar/shape.hpp"
#include "blazar/strides.hpp"

namespace blazar::io {

void print(std::ostream& stream, rank_type rank) {
    stream << static_cast<int>(rank);
}

void print(std::ostream& stream, type type) {
    stream << Type(type).name();
}

void print(std::ostream& ostream, const shape_t& shape, rank_type dimensions, bool reference = false) {
    ostream << "(";
    for (rank_type dimension = 0; dimension < dimensions; ++dimension) { 
        ostream << reference ? shape.address[dimension] : shape.sizes[dimension];

        if (dimension + 1 < dimensions) {
            ostream << ", ";
        }
    }
    ostream << ")"; 
}

void print(std::ostream& ostream, const strides_t& strides, rank_type dimensions, bool reference = false) {
    ostream << "(";
    for (rank_type dimension = 0; dimension < dimensions; ++dimension) { 
        ostream << reference ? strides.address[dimension] : strides.sizes[dimension];
        if (dimension + 1 < dimensions) {
            ostream << ", ";
        }
    }
    ostream << ")"; 
}  

} namespace blazar {

auto operator<<(std::ostream& stream, Type type) -> std::ostream&{
    io::print(stream, type);
    return stream;
}

auto operator<<(std::ostream& ostream, Shape const& shape) -> std::ostream&{
    shape_t printable { .address = shape.address() };
    ostream << "Shape"; 
    io::print(ostream, printable, shape.size(), true);
    return ostream;
} 

auto operator<<(std::ostream& ostream, Strides const& strides) -> std::ostream& {
    strides_t printable { .address = strides.address() };
    ostream << "Strides"; 
    io::print(ostream, printable, strides.size(), true);
    return ostream;
} 

}