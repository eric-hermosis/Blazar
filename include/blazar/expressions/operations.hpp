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
#ifndef OPERATIONS_HPP_0x45524943
#define OPERATIONS_HPP_0x45524943

#include <blazar/types.hpp>
#include <blazar/shape.hpp>
#include <blazar/strides.hpp>
#include <blazar/expressions/expression.hpp>
 
namespace blazar::expressions {

template<class Symbol, class Operand>
class Unary : public Expression<Symbol, Operand> {
public: 
    constexpr Unary(Symbol symbol, Operand const& operand) 
    :   Expression<Symbol, Operand>(symbol, operand) 
    {}
    
    [[nodiscard]] constexpr auto type() const -> Type const & {
        return std::get<0>(this->sources).type();
    }

    [[nodiscard]] constexpr auto shape() const -> Shape const& {
        return std::get<0>(this->sources).shape();
    }

    [[nodiscard]] constexpr auto strides() const -> Strides const& {
        return std::get<0>(this->sources).strides();
    }

    [[nodiscard]] constexpr auto size() const -> size_type {
        return std::get<0>(this->sources).size();
    }
    
    [[nodiscard]] constexpr auto rank() const -> rank_type {
        return std::get<0>(this->sources).rank();
    }

    [[nodiscard]] constexpr auto bytes() const -> std::size_t {
        return size() * type().size();
    }   
};
 
template<class Symbol, class Operand, class Cooperand>
class Binary : public Expression<Symbol, Operand, Cooperand> {
public: 
    constexpr static auto promote(Type const& first, Type const& second) -> Type {
        return (first.id() > second.id()) ? first : second;     
    }

    constexpr Binary(Symbol symbol, Operand const& operand, Cooperand const& cooperand)
    :   Expression<Symbol, Operand, Cooperand>(symbol, operand, cooperand) 
    {
        rank_ = std::max(operand.rank(), cooperand.rank());  
        
        if (rank_ > 0) {

            shape_.resize(rank_); 
            strides_.resize(rank_);

            for(auto dimension = 0; dimension < rank_; ++dimension) {
                auto first  = (dimension < rank_ -  operand.rank()) ? 1  : operand.size(dimension - (rank_ - operand.rank()));
                auto second = (dimension < rank_ - cooperand.rank()) ? 1 : cooperand.size(dimension - (rank_ - cooperand.rank()));
                
                if (! (first == second || first == 1 || second == 1)) {
                    throw Exception("Shapes are not broadcast-compatible.");
                }

                shape_[dimension] = std::max(first, second);

            }
            size_ = 1;
        
            for(auto dimension = rank_ - 1; dimension >= 0; --dimension) {
                strides_[dimension] = size_;
                size_ *= shape_[dimension];
            } 
        } 
        
        else {
            size_ = 1;
        }
     
        type_ = promote(operand.type(), cooperand.type());   
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
    
    [[nodiscard]] constexpr auto rank() const -> rank_type {
        return rank_;
    }
    
    [[nodiscard]] constexpr auto bytes() const -> std::size_t {
        return size() * type_.size();
    }  

private:
    Type    type_;    
    Shape   shape_;
    Strides strides_;
    size_type size_;   
    rank_type rank_; 
};

} namespace blazar::symbols { 
     
struct Negation {};
struct Addition {};
struct Division {};
struct Subtraction{}; 
struct Multiplication {}; 
struct Exponentiation {};

} namespace blazar::operations {

using namespace symbols; 
using namespace expressions;

template<class Operand>
constexpr auto operator-(Operand && operand) {
    return Unary<Negation, Operand>({}, std::forward<Operand>(operand));
}

template<class Augend, class Addend>
constexpr auto operator+(Augend && augend, Addend && addend) {
    return Binary<Addition, Augend, Addend>({}, std::forward<Augend>(augend), std::forward<Addend>(addend));
}

template<class Dividend, class Divisor>
constexpr auto operator/(Dividend && dividend, Divisor && divisor) {
    return Binary<Division, Dividend, Divisor>({}, std::forward<Dividend>(dividend), std::forward<Divisor>(divisor));
}

template<class Minuend, class Subtrahend>
constexpr auto operator-(Minuend && minuend, Subtrahend && subtrahend) {
    return Binary<Subtraction, Subtrahend, Minuend>({}, std::forward<Minuend>(minuend), std::forward<Subtrahend>(subtrahend));
}

template<class Multiplicand, class Multiplier>
constexpr auto operator*(Multiplicand && multiplicand, Multiplier && multiplier) {
    return Binary<Multiplication, Multiplicand, Multiplier>({}, std::forward<Multiplicand>(multiplicand), std::forward<Multiplicand>(multiplier));
}

template<class Base, class Exponent>
constexpr auto operator^(Base && base, Exponent && exponent) {
    return Binary<Exponentiation, Base, Exponent>({}, std::forward<Base>(base), std::forward<Exponent>(exponent));
} 

} namespace blazar {

using blazar::operations::operator+;
using blazar::operations::operator-;
using blazar::operations::operator*;
using blazar::operations::operator/;
using blazar::operations::operator^;

}

#endif