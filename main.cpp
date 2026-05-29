#include <blazar/expressions/variables.hpp>
#include <blazar/expressions/operators.hpp>

using namespace blazar; 
  
#include <iostream>

int main() { 
    Variable x(float32, {4,4}); 
    auto z = x[2];
}
