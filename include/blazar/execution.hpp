#ifndef EXECUTION_HPP_0x45524943  
#define EXECUTION_HPP_0x45524943  

#include <iostream>
#include <blazar/graph.hpp>
#include <blazar/storage.hpp>

namespace blazar::execution {
 
class Item {
public: 
    Item() = default;
    Item(Storage const& storage);

private:
    Memory* memory_ = nullptr;
};

class Task {
public:

};

class Plan {
public: 
    template<class Expression>
    Plan(Expression const& expression) {
        std::cout << "Planing expression with " << expression.index() << " tasks" << std::endl;
        expression.forward(*this);
    } 

    template<class Expression>
    bool visited(Expression const& expression) {
        std::cout << "visited!" << std::endl; 
        return true;
    }

    template<class Expression>
    void visit(Expression const& expression) {
        
    }

    void execute() {
        std::cout << "EXECUTING PLAN!" << std::endl; 
    } 
    
};

}

#endif