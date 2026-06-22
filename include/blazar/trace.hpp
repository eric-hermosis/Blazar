// Copyright 2026 Eric Hermosis
//
// This file is part of the Blazar Tensor Library.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
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

    [[nodiscard]] static auto create(Symbol const& symbol, Type const& type, Layout const& layout) -> Node*; 
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
    auto create(std::size_t index) -> Task*;  
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