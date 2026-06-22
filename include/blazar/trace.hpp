#ifndef TRACE_HPP_0x45524943
#define TRACE_HPP_0x45524943

#include <blazar/core/trace.h> 
#include <blazar/types.hpp>
#include <blazar/symbols.hpp> 
#include <blazar/layouts.hpp>
#include <blazar/storage.hpp>
#include <blazar/memory.hpp>
#include <cstdint>
#include <cstddef>
#include <vector>

namespace blazar {

class Node {
public: 
    Node();
    ~Node();
    Node(Node const&) = delete;
    Node(Node &&) noexcept = delete;
    auto operator=(Node const&) noexcept -> Node& = delete;
    auto operator=(Node &&) -> Node& = delete;
    void set(Symbol const& symbol, Type const& type, Layout const& layout);
    void set(Storage const& storage);
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
    Memory* memory_ = nullptr;
};

} namespace blazar::execution {

class Task {
public:
    Task();
    auto arity() const noexcept -> std::size_t; 
    void link(Task* source);
    void prune(); 

private:
    std::vector<Task*> sources_;
    Memory* memory_ = nullptr;
};
  
class Tasks {
public:
    Tasks(std::size_t count); 
    auto allocate(std::size_t index) -> Task*;  
    void resize(std::size_t); 
    void clear();  
    bool has(std::size_t index) noexcept;
    auto get(std::size_t index) -> Task*; 

private:
    task_t body_;
    std::vector<Task*> checklist_;
};

}

#endif