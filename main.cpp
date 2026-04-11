#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string_view>

#include "include/blazar/types.hpp"

using namespace blazar;

int main() {
    Type t1(boolean);
    Type t2(float64);
    Type t3(complex128);
    std::cout << t2 << std::endl;
    return 0;
}