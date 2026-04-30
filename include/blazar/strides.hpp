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

#ifndef STRIDES_HPP_0x45524943 
#define STRIDES_HPP_0x45524943 

#include <iosfwd>
#include <array>  
#include <initializer_list>

#include "concepts.hpp"
#include "shape.hpp" 
#include "indexing.hpp"
#include "exceptions.hpp" 

namespace blazar {
 
class Strides {
public:  
    static constexpr uint8_t limit = 8;    

    constexpr Strides() noexcept = default; 
  

    template<Integral Size>
    constexpr Strides(std::initializer_list<Size> shape)
    {
        const auto dimensions = shape.size();

        if (dimensions > limit) {
            throw Exception(
                "Strides rank " + std::to_string(dimensions) +
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
    constexpr Strides(Sizes... sizes) 
    :   size_(sizeof...(Sizes)) 
    {
        static_assert(sizeof...(Sizes) <= limit, "Strides rank exceeds limit.");
        size_type dimension = 0;
        (([&] {
            if constexpr (std::is_signed_v<Sizes>) {
                if (sizes < -1) {
                    throw Exception(
                        "Invalid size for dimension " + std::to_string(dimension) +
                        ": " + std::to_string(sizes) +
                        ". Size must be >= -1."
                    );
                }
            }

            sizes_[dimension++] = static_cast<size_type>(sizes);
        }()), ...);
    }
    
    template<Iterator Iterator>
    constexpr Strides(Iterator begin, Iterator end)
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
    
    constexpr Strides(const Shape& shape) noexcept
    :   size_(shape.size()) 
    {  
        if (size_ == 0) {
            return;
        }

        sizes_[size_ - 1] = 1;
        for (int size = size_ - 2; size >= 0; --size) {
            sizes_[size] = sizes_[size + 1] * shape[size + 1];
        } 
    }
 
    [[nodiscard]] constexpr auto address() noexcept -> size_type* {
        return sizes_.data();
    }

    [[nodiscard]] constexpr auto address() const noexcept -> size_type const* {
        return sizes_.data();
    }

    [[nodiscard]] constexpr auto size() const noexcept { 
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
            throw Exception("Cannot call front() on an empty Strides");
        }
        return sizes_.front(); 
    }
    
    [[nodiscard]] constexpr auto back() const { 
        if (size_ == 0) {
            throw Exception("Cannot call back() on an empty Strides");  
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
                "Strides dimensions " + std::to_string(size_) + 
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
                "Strides dimensions limit exceeded: rank is " + std::to_string(size_) +
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

constexpr auto operator==(Strides const& first, Strides const& second) -> bool {
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

auto operator<<(std::ostream&, Strides const& strides) -> std::ostream&;  

} // namespace blazar

#endif // STRIDES_HPP_0x45524943 