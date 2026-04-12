// Copyright 2025 Eric Hermosis
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

#include "concepts.hpp"
#include "shape.hpp" 
#include "indexing.hpp"
#include "exceptions.hpp" 

namespace blazar {
 
class Strides {
public:  
    static constexpr uint8_t limit = 8;    
    constexpr Strides() noexcept = default; 
  
    template<Integral... Sizes>
    constexpr Strides(Sizes... sizes)
        : sizes_{static_cast<size_type>(sizes)...}
        , size_(sizeof...(sizes)) {
            if (size_ > limit) { 
                throw Exception(std::string_view(
                    "Strides rank limit exceeded: rank is " + std::to_string(size_) +
                    ", but the maximum allowed is " + std::to_string(limit)
                ).data());
            }
        } 

    template<Iterator Iterator>
    constexpr Strides(Iterator begin, Iterator end) { 
        rank_type dimension = 0;
        for (auto iterator = begin; iterator != end; ++iterator) { 
            sizes_.at(dimension++) = static_cast<size_type>(*iterator);
        }

        size_ = dimension;
        if (size_ > limit) {
            throw Exception(std::string_view(
                "Strides rank limit exceeded: rank is " + std::to_string(size_) +
                ", but the maximum allowed is " + std::to_string(limit)
            ).data());
        }
    } 
    
    constexpr Strides(const Shape& shape) noexcept
    :   size_(shape.size()) {  
        if (size_ == 0) {
            return;
        }

        sizes_.at(size_ - 1) = 1;
        for (int size = size_ - 2; size >= 0; --size) {
            sizes_.at(size) = sizes_.at(size + 1) * shape[size + 1];
        } 
    }
 
    constexpr auto address() noexcept -> size_type* {
        return sizes_.data();
    }

    [[nodiscard]] constexpr auto address() const noexcept -> size_type const* {
        return sizes_.data();
    }

    [[nodiscard]] constexpr auto size() const noexcept { 
        return size_; 
    } 

    constexpr auto begin() { 
        return sizes_.begin(); 
    }
    
    constexpr auto end() {
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
        return sizes_.front(); 
    }
 
    [[nodiscard]] constexpr auto back() const {
        return sizes_.at(size_);
    }
  
    template<Integral Index>
    [[nodiscard]] constexpr auto operator[](Index index) const -> size_type const& { 
        return sizes_.at(indexing::normalize(index, size()));
    }

    template<Integral Index>
    constexpr auto operator[](Index index) -> size_type& { 
        return sizes_.at(indexing::normalize(index, size())); 
    }

    constexpr void append(size_type size) { 
        if (size_ + 1 > limit) {
            throw Exception(std::string_view(
                "Strides rank limit exceeded: rank is " + std::to_string(size_) +
                ", but the maximum allowed is " + std::to_string(limit)
            ).data());
        }
        sizes_.at(size_) = size;
        size_ += 1; 
    } 

    constexpr void resize(rank_type dimensions) {
        if (size_ > limit) {
            throw Exception(std::string_view(
                "Strides dimensions limit exceeded: rank is " + std::to_string(size_) +
                ", but the maximum allowed is " + std::to_string(limit)
            ).data());
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