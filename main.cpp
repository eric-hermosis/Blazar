#include <iostream> 
#include <blazar/operations.hpp>
#include <blazar/environments.hpp>
#include <blazar/handlers.hpp>

using namespace blazar;

int main() {   
    auto dis = Handlers::get(operations::Addition{}, Host(), Type(float32), Type(float32));
}