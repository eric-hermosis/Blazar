#include <blazar/variables.hpp>
#include <blazar/operations.hpp>

using namespace blazar;

constexpr bool test() {
    Variable a(float64, {2,2});
    Variable b(float32, {2,3,4});
    a = b + b * b;
    return a.rank() == 3 && a.size() == 24;
}

static_assert(test());
  
#include <iostream>

int main() {
    std::cout << test() << std::endl;
}