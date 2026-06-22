#include <iostream> 
#include <blazar/graph.hpp>
#include <blazar/tensors.hpp>
#include <blazar/execution.hpp>
#include <blazar/operations.hpp>

using namespace blazar;
using execution::Items;

int main() {       
    Tensor x(float32, {2,2}); x.initialize();
    Tensor y(float32, {2,2}); y.initialize();
    Tensor z(float32, {2,2}); z.initialize(); 
    auto expr = x*y + y*z + z*x;
    auto vrts = Vertices(); 
    auto vrtx = expr.forward(vrts);

    auto itms = Items(vrts.count);
    auto item = expr.forward(itms); 
}