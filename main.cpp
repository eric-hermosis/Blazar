#include <blazar/tensors.hpp>
#include <blazar/operations.hpp>

using namespace blazar;

int main() {   
    Tensor x(float32, {2,2}); x.initialize();
    Tensor y(float32, {2,1}); y.initialize();
    Tensor z(float32, {1,2}); z.initialize();
    auto expr = x*y + y*z + z*x;
}

