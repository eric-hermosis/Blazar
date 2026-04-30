#include <cstdint>
#include <cstddef>
#include <memory>
#include <stack>
#include <deque>
#include <vector>
#include <cassert>
#include <blazar/memory.hpp>
#include <blazar/storage.hpp> 

#include <iostream>
using namespace blazar; 

int main() { 
    Storage storage(1024, Host()); 
    Storage storage2 = storage;
    std::cout << storage.get()->references() << std::endl;
}