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
#ifndef EXPRESSIONS_HPP_0x45524943
#define EXPRESSIONS_HPP_0x45524943
 
#include <type_traits>
#include <tuple>
#include <blazar/types.hpp>
#include <blazar/shape.hpp>
#include <blazar/strides.hpp>

namespace blazar::expressions {
 
template<class Expression>
class Trait {
public:
    using type = typename std::decay<Expression>::type;
};

template<class Primitive, class ... Expressions>
class Expression {
public:
    Primitive primitive;
    std::tuple<typename Trait<Expressions>::type ...> sources;

    constexpr Expression(Primitive primitive, Expressions const& ... sources) 
    :   primitive(primitive)
    ,   sources(sources...)
    {}
};
 
template<class Operation, class... Operands>
class Operator : public Expression<Operation, Operands...> {
public: 
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
    :   Expression<Operation, Operands...>(operation, operands...) 
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
    
    [[nodiscard]] constexpr auto rank() const -> rank_type {
        return rank_;
    }
    
    [[nodiscard]] constexpr auto bytes() const -> std::size_t {
        return size() * type_.size();
    }  

private:
    Type      type_;    
    Shape     shape_;
    Strides   strides_;
    size_type size_;   
    rank_type rank_; 
};



}

#endif