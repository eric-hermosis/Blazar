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

#ifndef NODES_HPP_0x45524943 
#define NODES_HPP_0x45524943 

#include <cstdint>
#include <cstddef>
#include <memory>
#include <blazar/resources.hpp>
#include <blazar/core/graph.h>

namespace blazar {

class Symbol;

class Node {      
public:  
    auto operator new(std::size_t) -> void*;
    void operator delete(void*, std::size_t) noexcept;    
    Node(Symbol const& symbol, int arity); 
    ~Node() = default;
    Node(Node const& other) = delete;
    Node(Node && other) noexcept = delete;
    auto operator=(Node const& other) -> Node& = delete;
    auto operator=(Node && other) noexcept -> Node& = delete;
    [[nodiscard]] auto references() const noexcept -> std::uint32_t; 

    void acquire();
    void release();  
 
private:
    std::uint32_t references_; 
    node_t body_; 
};

}

#endif 