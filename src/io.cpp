#include <iostream>
#include "blazar/types.hpp"

namespace blazar::io {

void print(std::ostream& stream, type type) {
    stream << Type(type).name();
}

} namespace blazar {

auto operator<<(std::ostream& stream, Type type) -> std::ostream&{
    io::print(stream, type);
    return stream;
}

}