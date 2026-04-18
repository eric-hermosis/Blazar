#include <type_traits>
#include <tuple> 
 
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <blazar/shape.hpp>
using namespace blazar;

int main() { 
    Shape shape(1,2,3,4,5); 
    std::cout << shape << std::endl;
}