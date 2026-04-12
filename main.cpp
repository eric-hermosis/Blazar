#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string_view>

#include "include/blazar/types.hpp"
#include "include/blazar/shape.hpp"
#include "include/blazar/strides.hpp"

using namespace blazar;

int main() {
    Type t1(boolean);
    Type t2(float64);
    Type t3(complex128);
    Strides shape(1,2,3,4,6,7,8,9);
    std::cout << "t1: " << t1.name() << " size=" << t1.size() << "\n"; 
    std::cout << shape << std::endl;
    return 0;
}