#include <iostream>
#include <blazar/types.hpp>
#include <blazar/layouts.hpp>   
#include <blazar/tensors.hpp>
#include <blazar/operations.hpp>
#include <blazar/views.hpp>
#include <blazar/tensors.hpp>
#include <meta> 
#include <string_view>

using namespace blazar;

constexpr auto forward(Tensor x, Tensor y, Tensor z) -> Tensor {
    x = x[{1,2}];
    return x*y + y*z + z*x;
}

int main() {  
    constexpr Tensor x(float32,{4, 4});
    constexpr Tensor y(float64,{2, 4});
    constexpr Tensor z(float16, {2, 1});
    constexpr Tensor result = forward(x, y, z);
    static_assert(result.layout().shape() == Shape(2,4));
    std::cout
        << result.type()
        << '\n';

    std::cout
        << result.layout().shape()
        << '\n';
}