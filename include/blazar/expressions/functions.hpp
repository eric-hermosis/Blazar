// Copyright 2026 Eric Hermosis
//
// This file is part of the Tannic Tensor Library.
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
#ifndef FUNCTIONS_HPP_0x45524943 
#define FUNCTIONS_HPP_0x45524943 

#include "../types.hpp"
#include "../shape.hpp"
#include "../strides.hpp" 
#include "expression.hpp"

namespace blazar::expressions {

template<class Symbol, class ... Arguments>
class Function; 

template<class Symbol, class Argument>
class Function<Symbol, Argument> : public Expression<Symbol, Argument> {
public: 
    constexpr Function(Symbol function, Argument const& argument)
    :   Expression<Symbol, Argument>(function, argument)
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

} namespace blazar::symbols {
    
struct Log {}; 
struct Exp {};
struct Sqrt {};
struct Rsqrt {};
struct Abs {};
struct Sin {};
struct Cos {};
struct Tan {};
struct Sinh {};
struct Cosh {};
struct Tanh {};

} namespace blazar::functions {

using namespace expressions;
using namespace symbols;

template<class Argument>
constexpr auto log(Argument&& argument) {
    return Function<Log, Argument>({}, std::forward<Argument>(argument));
}

template<class Argument>
constexpr auto exp(Argument&& argument) {
    return Function<Exp, Argument>({}, std::forward<Argument>(argument));
}

template<class Argument>
constexpr auto sqrt(Argument&& argument) {
    return Function<Sqrt, Argument>({}, std::forward<Argument>(argument));
}  

template<class Argument>
constexpr auto rsqrt(Argument&& argument) {
    return Function<Rsqrt, Argument>(std::forward<Argument>(argument));
}

template<class Argument>
constexpr auto abs(Argument&& argument) {
    return Function<Abs, Argument>({}, std::forward<Argument>(argument));
}

template<class Argument>
constexpr auto sin(Argument&& argument) {
    return Function<Sin, Argument>({}, std::forward<Argument>(argument));
} 

template<class Argument>
constexpr auto cos(Argument&& argument) {
    return Function<Cos, Argument>({}, std::forward<Argument>(argument));
}
 
template<class Argument>
constexpr auto tan(Argument&& argument) {
    return Function<Tan, Argument>({}, std::forward<Argument>(argument));
}
 
template<class Argument>
constexpr auto sinh(Argument&& argument) {
    return Function<Sinh, Argument>({}, std::forward<Argument>(argument));
}
 
template<class Argument>
constexpr auto cosh(Argument&& argument) {
    return Function<Cosh, Argument>({}, std::forward<Argument>(argument));
}
 
template<class Argument>
constexpr auto tanh(Argument&& argument) {
    return Function<Tanh, Argument>({}, std::forward<Argument>(argument));
}

} namespace blazar {
    
using functions::log;
using functions::exp;
using functions::sqrt;
using functions::rsqrt;
using functions::abs;
using functions::sin;
using functions::cos;
using functions::tan;
using functions::sinh;
using functions::cosh;
using functions::tanh;

} //namespace tannic 

#endif // FUNCTIONS_HPP_0x45524943 