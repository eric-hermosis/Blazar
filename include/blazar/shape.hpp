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

#ifndef SHAPE_HPP_0x45524943 
#define SHAPE_HPP_0x45524943 

#include <iosfwd>
#include <array>
#include <cstdint>
#include <cassert>  
#include <initializer_list> 
 
#include "concepts.hpp"  
#include "exceptions.hpp"
#include "indexing.hpp" 

namespace blazar { 
    
class Shape {
public:
    static constexpr uint8_t limit = 8;    
    
    constexpr Shape() noexcept = default;

    template<Integral Size>
    constexpr Shape(std::initializer_list<Size> shape)
    {
        const auto dimensions = shape.size();

        if (dimensions > limit) {
            throw Exception(
                "Shape rank " + std::to_string(dimensions) +
                " exceeds limit of " + std::to_string(limit)
            );
        }

        size_ = static_cast<rank_type>(dimensions);

        size_type dimension = 0;

        for (auto size : shape) {
            if constexpr (std::is_signed_v<Size>) {
                if (size < -1) {
                    throw Exception(
                        "Invalid size for dimension " + std::to_string(dimension) +
                        ": " + std::to_string(size) +
                        ". Size must be >= -1."
                    );
                }
            }

            sizes_[dimension++] = static_cast<size_type>(size);
        }
    }

    template<Integral... Sizes>
    constexpr Shape(Sizes... sizes)
    :   size_(sizeof...(Sizes)) 
    {
        static_assert(sizeof...(Sizes) <= limit, "Shape rank exceeds limit.");
        
        size_type dimension = 0; 

        template for (auto size : std::tuple{sizes...}) {
            if constexpr (std::is_signed_v<decltype(size)>) {
                if (size < -1) {
                    throw Exception(
                        "Invalid size for dimension " + std::to_string(dimension) +
                        ": " + std::to_string(size) +
                        ". Size must be >= -1."
                    );
                }
            } 
            sizes_[dimension++] = static_cast<size_type>(size);
        }
    }
        
    template<Iterable Sizes>
    constexpr Shape(Sizes&& sizes) {
        size_type dimension = 0;

        for (auto size : sizes) {
            if (dimension >= limit) {
                throw Exception(
                    "Shape rank exceeds limit of " + std::to_string(limit)
                );
            }

            if constexpr (std::is_signed_v<std::decay_t<decltype(size)>>) {
                if (size < -1) {
                    throw Exception(
                        "Invalid size for dimension " + std::to_string(dimension) +
                        ": " + std::to_string(size) +
                        ". Size must be >= -1."
                    );
                }
            }

            sizes_[dimension++] = static_cast<size_type>(size);
        }

        size_ = dimension;
    }


    template<Iterator Iterator>
    constexpr Shape(Iterator begin, Iterator end)
    {
        size_type dimension = 0;

        for (Iterator iterator = begin; iterator != end; ++iterator) {
            if (dimension >= limit) {
                throw Exception(
                    "Shape rank exceeds limit of " + std::to_string(limit)
                );
            }

            auto size = *iterator;

            if constexpr (std::is_signed_v<std::decay_t<decltype(size)>>) {
                if (size < -1) {
                    throw Exception(
                        "Invalid size for dimension " + std::to_string(dimension) +
                        ": " + std::to_string(size) +
                        ". Size must be >= -1."
                    );
                }
            }

            sizes_[dimension++] = static_cast<size_type>(size);
        }

        size_ = dimension;
    }

    [[nodiscard]] constexpr auto address() noexcept -> size_type* {
        return sizes_.data();
    }

    [[nodiscard]] constexpr auto address() const noexcept ->  size_type const* {
        return sizes_.data();
    }
    
    [[nodiscard]] constexpr auto size() const noexcept -> rank_type { 
        return size_; 
    }
    
    [[nodiscard]] constexpr auto begin() { 
        return sizes_.begin(); 
    }
     
    [[nodiscard]] constexpr auto end() { 
        return std::next(sizes_.begin(), size_);
    }
 
    [[nodiscard]] constexpr auto begin() const { 
        return sizes_.begin(); 
    }  

    [[nodiscard]] constexpr auto end() const { 
        return std::next(sizes_.begin(), size_); 
    } 
 
    [[nodiscard]] constexpr auto cbegin() const { 
        return sizes_.cbegin(); 
    }
     
    [[nodiscard]] constexpr auto cend() const { 
        return std::next(sizes_.cbegin(), size_); 
    }
    
    [[nodiscard]] constexpr auto front() const { 
        if (size_ == 0) {
            throw Exception("Cannot call front() on an empty Shape");
        }
        return sizes_.front(); 
    }
    
    [[nodiscard]] constexpr auto back() const { 
        if (size_ == 0) {
            throw Exception("Cannot call back() on an empty Shape");  
        }
        return sizes_[size_-1];
    }       

    template<Integral Index>
    [[nodiscard]] constexpr auto operator[](Index index) const -> size_type const&{ 
        return sizes_[indexing::normalize(index, size())]; 
    }
    
    template<Integral Index>
    constexpr auto operator[](Index index) -> size_type& {
        return sizes_[indexing::normalize(index, size())]; 
    } 

    constexpr void append(size_type size) { 
        if (size_ + 1 > limit) {
            throw Exception(
                "Shape dimensions " + std::to_string(size_) + 
                " exceeds limit of " + std::to_string(limit)
            );
        }  

        if (size < -1) {
            throw Exception(
                "Invalid size for dimension " + std::to_string(size_) +
                ": " + std::to_string(size) +
                ". Size must be >= -1."
            );
        }

        sizes_[size_++] = size;
    }

    constexpr void resize(rank_type dimensions) {
        if (dimensions > limit) {
            throw Exception(
                "Shape dimensions limit exceeded: rank is " + std::to_string(size_) +
                ", but the maximum allowed is " + std::to_string(limit)
            );
        }

        if (dimensions > size_) {
            std::fill(sizes_.begin() + size_, sizes_.begin() + dimensions, 0);
        }
        size_ = dimensions; 
    }

private:
    rank_type size_{0};      
    std::array<size_type, limit> sizes_{}; 
};
 
constexpr auto operator==(Shape const& first, Shape const& second) -> bool {
    if (first.size() != second.size()) {
        return false;
    }

    for (auto dimension = 0; dimension < first.size(); ++dimension) {
        if (first[dimension] != second[dimension]) {
            return false;
        }
    }
    return true;
}   

auto operator<<(std::ostream&, Shape const& shape) -> std::ostream&;

} 

#endif