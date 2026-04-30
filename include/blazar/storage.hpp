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

#ifndef STORAGE_HPP_0x45524943 
#define STORAGE_HPP_0x45524943 
  
#include <cstddef>
#include <cstdint>
#include <utility>
#include <blazar/resources.hpp> 

namespace blazar { 

class Memory;

class Storage {
public:      
    constexpr Storage() = default; 
    
    constexpr Storage(Storage const& other) { 
        if !consteval {
            copy(other);
        } 
    }

    constexpr Storage(Storage && other) noexcept { 
        if !consteval {
            move(other);
        } 
    }

    constexpr auto operator=(Storage const& other) -> Storage& {
        if !consteval { 
            copy(other); 
        }
        return *this;
    }

    constexpr auto operator=(Storage&& other) noexcept -> Storage& {
        if !consteval { 
            move(other); 
        }
        return *this;
    }

    constexpr ~Storage() { 
        if !consteval { 
            release(); 
        }
    }  
   
    explicit Storage(std::size_t, Environment const& environment = Host());
 
    [[nodiscard]] auto size() const noexcept -> std::size_t; 
    [[nodiscard]] auto environment() const noexcept -> Environment const&;  
    [[nodiscard]] auto get() const noexcept -> Memory const*;
 
protected:
    void release();
    void copy(Storage const& other);
    void move(Storage & other) noexcept;  

private:
    Memory* memory_ = nullptr;
};

} 

#endif 