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

#ifndef GRAPH_HPP_0x45524943 
#define GRAPH_HPP_0x45524943 
#include <blazar/symbols.hpp>

namespace blazar {

class Node;

class Vertex {
public:

    constexpr Vertex() = default; 
    
    constexpr Vertex(Vertex const& other) { 
        if !consteval {
            copy(other);
        } 
    }
              
    constexpr Vertex(Vertex && other) noexcept { 
        if !consteval {
            move(other);
        } 
    }

    constexpr auto operator=(Vertex const& other) -> Vertex& {
        if !consteval { 
            copy(other); 
        }
        return *this;
    }

    constexpr auto operator=(Vertex&& other) noexcept -> Vertex& {
        if !consteval { 
            move(other); 
        }
        return *this;
    }

    constexpr ~Vertex() { 
        if !consteval { 
            release(); 
        }
    }    

    Vertex(Symbol const&, int arity);

    void release();
    void copy(Vertex const&);
    void move(Vertex &) noexcept;

private:
    Node* node_ = nullptr;
};

}

#endif