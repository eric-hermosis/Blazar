#ifndef TRACE_HPP_0x45524943
#define TRACE_HPP_0x45524943

#include <blazar/core/trace.h>
#include <blazar/types.hpp>
#include <blazar/symbols.hpp> 
#include <blazar/layouts.hpp>
#include <cstdint>
#include <cstddef>
#include <vector>

namespace blazar {

class Node {
public: 
    Node();
    void set(Symbol const& symbol, Type const& type, Layout const& layout);
    void acquire();
    void release();  
    void link(Node* source); 
    void prune(); 

    [[nodiscard]] static auto allocate(Symbol const& symbol, Type const& type, Layout const& layout) -> Node*; 
    [[nodiscard]] auto arity() const noexcept -> std::uint8_t;

private:   
    node_t body_;   
    std::uint32_t references_ = 0; 
    std::vector<Node*> sources_; 
};

class Task {
public:
    Task();
    void set();
    void acquire();
    void release();  
    void link(Task* source); 
    void prune();  

    [[nodiscard]] static auto allocate() -> Task*; 
    [[nodiscard]] auto arity() const noexcept -> std::uint8_t;

private:
    std::uint32_t references_ = 0; 
    std::vector<Task*> sources_; 
};

}

#endif