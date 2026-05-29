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

#ifndef TYPE_HPP_0x45524943
#define TYPE_HPP_0x45524943 

#include <iosfwd>
#include <cstdint>
#include <cstddef>
#include <string_view> 
#include <complex>  
#include <tuple>  
#include <blazar/core/types.h>

namespace blazar::types {  

constexpr auto pairs = std::tuple{
    std::pair{boolean, bool{}},
    std::pair{uint8,  std::uint8_t{}},
    std::pair{uint16, std::uint16_t{}},
    std::pair{uint32, std::uint32_t{}},
    std::pair{uint64, std::uint64_t{}}, 

    std::pair{int8,  std::int8_t {}},
    std::pair{int16, std::int16_t{}},
    std::pair{int32, std::int32_t{}},
    std::pair{int64, std::int64_t{}}, 

    std::pair{float32, float{}},
    std::pair{float64, double{}},
     
    std::pair{complex64,  std::complex<float>{}},
    std::pair{complex128, std::complex<double>{}}
};

constexpr struct {
    std::string_view name;
    std::size_t      size; 
    std::uint8_t     bits;  
}   

traits[TYPES] = {

    [boolean] = {
        .name = "boolean",
        .size = sizeof(std::uint8_t),
        .bits = 8,
    },

    [uint8] = {
        .name = "uint8",
        .size = sizeof(std::uint8_t),
        .bits = 8,
    },

    [uint16] = {
        .name = "uint16",
        .size = sizeof(std::uint16_t),
        .bits = 16,
    },

    [uint32] = {
        .name = "uint32",
        .size = sizeof(std::uint32_t),
        .bits = 32,
    },

    [uint64] = {
        .name = "uint64",
        .size = sizeof(std::uint64_t),
        .bits = 64,
    },

    [int8] = {
        .name = "int8",
        .size = sizeof(std::int8_t),
        .bits = 8,
    },

    [int16] = {
        .name = "int16",
        .size = sizeof(std::int16_t),
        .bits = 16,
    },

    [int32] = {
        .name = "int32",
        .size = sizeof(std::int32_t),
        .bits = 32,
    },

    [int64] = {
        .name = "int64",
        .size = sizeof(std::int64_t),
        .bits = 64,
    },

    [float16] = {
        .name = "float16",
        .size = 2,
        .bits = 16,
    },

    [bfloat16] = {
        .name = "bfloat16",
        .size = 2,
        .bits = 16,
    },

    [float32] = {
        .name = "float32",
        .size = sizeof(float),
        .bits = 32,
    },

    [float64] = {
        .name = "float64",
        .size = sizeof(double),
        .bits = 64,
    },

    [complex64] = {
        .name = "complex64",
        .size = 2 * sizeof(float),
        .bits = 64,
    },

    [complex128] = {
        .name = "complex128",
        .size = 2 * sizeof(double),
        .bits = 128,
    },

    [any] = {
        .name = "any"
    },

    [object] = {
        .name = "object" 
    },

    [unknown] = {
        .name = "unknown" 
    },
}; 
 
} namespace blazar {

class Type {
    
public:
    
    constexpr Type() noexcept
    :   type_(unknown) {}

    constexpr Type(type type) noexcept 
    :   type_(type) {}
  
    constexpr operator type() const {
        return type_;
    }
    
    [[nodiscard]] constexpr auto id() const noexcept -> int {
        return static_cast<int>(type_);
    }

    [[nodiscard]] constexpr auto name() const noexcept ->  std::string_view  {
        return types::traits[type_].name;
    }

    [[nodiscard]] constexpr auto size() const noexcept -> std::size_t {
        return types::traits[type_].size;
    }

    [[nodiscard]] constexpr auto bits() const noexcept -> std::uint8_t  {
        return types::traits[type_].bits;
    }

    template<typename T>
    [[nodiscard]] static constexpr auto of(T) noexcept -> Type {    
        
        template for (constexpr auto pair : types::pairs) { 
            if constexpr (std::is_same_v<T, decltype(pair.second)>) {
                return pair.first;
            }
        }

        if constexpr (std::is_class_v<T>) {
            return object; 
        }
 
        return unknown; 
    }

private:
    type type_;
};
  
auto operator<<(std::ostream&, Type type) -> std::ostream&; 

} // namespace blazar
    
#endif 