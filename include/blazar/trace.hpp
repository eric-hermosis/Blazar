#ifndef TRACE_HPP_0x45524943
#define TRACE_HPP_0x45524943

#include <blazar/core/trace.h>
#include <blazar/types.hpp>
#include <blazar/symbols.hpp> 
#include <blazar/layouts.hpp>
#include <cstdint>
#include <cstddef>

namespace blazar {

class Node {
public:
    Node(Symbol const& symbol, Type const& type, Layout const& layout);
    ~Node();
    Node(Node const& other) = delete;
    Node(Node && other) noexcept = delete;
    auto operator=(Node const& other) -> Node& = delete;
    auto operator=(Node && other) noexcept -> Node& = delete;
    auto operator new(std::size_t size) -> void*;
    void operator delete(void* address, std::size_t size) noexcept;    
    
    void acquire();
    void release();  
    void link(Node* source); 
    void prune();
    
    [[nodiscard]] static auto allocate(Symbol const& symbol, Type const& type, Layout const& layout) -> Node*;
    [[nodiscard]] auto references() -> std::uint32_t;

private: 
    node_t* body_;   
    std::uint32_t references_;
    std::uint8_t arity_;
    Node* sources_[4];
};

}

#endif