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
#include <blazar/traits.hpp>

namespace blazar {

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
        return traits::table[type_].name;
    }

    [[nodiscard]] constexpr auto size() const noexcept -> std::size_t {
        return traits::table[type_].size;
    }

    [[nodiscard]] constexpr auto bits() const noexcept -> std::uint8_t  {
        return traits::table[type_].bits;
    }

    template<typename T>
    [[nodiscard]] static constexpr auto of(T) noexcept -> Type {    
        
        template for (constexpr auto pair : traits::types) { 
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