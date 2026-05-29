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
#ifndef OPERATORS_HPP_0x45524943
#define OPERATORS_HPP_0x45524943
    
#include <type_traits>
#include <tuple> 
#include <blazar/types.hpp>
#include <blazar/layout/shape.hpp>
#include <blazar/layout/strides.hpp>   

namespace blazar::expressions {
 
template<class Expression>
class Trait {
public:
    using type = typename std::decay<Expression>::type;
};
 
template<class Operation, class... Operands>
class Operator {
public: 
    std::decay<Operation>::type symbol; 
    std::tuple<typename Trait<Operands>::type ...> sources;  

    constexpr static auto promote(const Operands&... operands) -> Type {
        Type result = unknown;
        template for (auto const& operand : std::tuple{operands...}) {
            if (operand.type().id() > result.id()) {
                result = operand.type();
            }
        }
        return result;
    }

    constexpr Operator(Operation operation, Operands const&... operands)
    :   symbol(operation)
    ,   sources(operands...)
    ,   rank_(0)
    ,   size_(1)
    { 
        template for (auto const& operand : std::tuple{operands...}) {
            rank_ = std::max(rank_, operand.rank());
        }
        
        if (rank_ > 0) {
            shape_.resize(rank_);
            strides_.resize(rank_);

            for (auto dimension = 0; dimension < rank_; ++dimension) {
                size_type size = 1;
  
                template for (auto const& operand : std::tuple{operands...}) {
                    auto offset = rank_ - operand.rank();
                    auto broadcasted = (dimension < offset) ? 1 : operand.size(dimension - offset);

                    if (broadcasted != 1) {
                        if (size != 1 && size != broadcasted) {
                            throw Exception("Operands are not broadcast-compatible at dimension " + std::to_string(dimension));
                        }
                        size = broadcasted;
                    }
                }
                shape_[dimension] = size;
            } 
            
            for (auto dimension = rank_ - 1; dimension >= 0; --dimension) {
                strides_[dimension] = size_;
                size_ *= shape_[dimension];
            } 
        }  
        type_ = promote(operands...);   
    }
 
    [[nodiscard]] constexpr auto type() const -> Type const & {
        return type_;
    }

    [[nodiscard]] constexpr auto shape() const -> Shape const& {
        return shape_;
    }

    [[nodiscard]] constexpr auto strides() const -> Strides const& {
        return strides_;
    }

    [[nodiscard]] constexpr auto size() const -> size_type {
        return size_;
    }

    [[nodiscard]] constexpr auto size(index_type index) const -> size_type {
        return shape_[index];
    } 
    
    [[nodiscard]] constexpr auto rank() const -> rank_type {
        return rank_;
    }
    
    [[nodiscard]] constexpr auto bytes() const -> std::size_t {
        return size() * type_.size();
    }  

    [[nodiscard]] constexpr auto offset() const -> index_type {
        return 0;
    }  

private:
    Type      type_;    
    Shape     shape_;
    Strides   strides_;
    size_type size_;   
    rank_type rank_; 
};
 
} namespace blazar::operations {   
 
struct Negation {};
struct Addition {};
struct Division {};
struct Subtraction{}; 
struct Multiplication {}; 
struct Exponentiation {};

} namespace blazar::operators {

using namespace operations; 
using namespace expressions;

template<class Operand>
constexpr auto operator-(Operand && operand) {
    return Operator<Negation, Operand>({}, std::forward<Operand>(operand));
}

template<class Augend, class Addend>
constexpr auto operator+(Augend && augend, Addend && addend) {
    return Operator<Addition, Augend, Addend>({}, std::forward<Augend>(augend), std::forward<Addend>(addend));
}

template<class Dividend, class Divisor>
constexpr auto operator/(Dividend && dividend, Divisor && divisor) {
    return Operator<Division, Dividend, Divisor>({}, std::forward<Dividend>(dividend), std::forward<Divisor>(divisor));
}

template<class Minuend, class Subtrahend>
constexpr auto operator-(Minuend && minuend, Subtrahend && subtrahend) {
    return Operator<Subtraction, Minuend, Subtrahend>({}, std::forward<Minuend>(minuend), std::forward<Subtrahend>(subtrahend));
}

template<class Multiplicand, class Multiplier>
constexpr auto operator*(Multiplicand && multiplicand, Multiplier && multiplier) {
    return Operator<Multiplication, Multiplicand, Multiplier>({}, std::forward<Multiplicand>(multiplicand), std::forward<Multiplier>(multiplier));
}

template<class Base, class Exponent>
constexpr auto operator^(Base && base, Exponent && exponent) {
    return Operator<Exponentiation, Base, Exponent>({}, std::forward<Base>(base), std::forward<Exponent>(exponent));
} 

} namespace blazar {

using operators::operator+;
using operators::operator-;
using operators::operator*;
using operators::operator/;
using operators::operator^;

}

#endif