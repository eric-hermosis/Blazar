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
#include <blazar/exceptions.hpp>
 
using namespace blazar;

constexpr auto divide(int a, int b) -> int {
    if (b == 0) {
        throw Exception("Division by zero!");
    }
    return a / b;
}

int main() { 
    static_assert([] {
        try {
            divide(10, 0);
        } catch (const Exception& e) {
            return true; 
        }
        return false;
    }());

    std::cout << "Compile-time exception validation passed!" << std::endl;
    return 0;
} 