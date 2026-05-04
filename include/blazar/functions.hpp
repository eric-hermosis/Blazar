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
#ifndef FUNCTIONS_HPP_0x45524943 
#define FUNCTIONS_HPP_0x45524943 

#include <blazar/types.hpp>
#include <blazar/shape.hpp>
#include <blazar/strides.hpp> 
#include <blazar/expressions.hpp>

namespace blazar::expressions {

template<class Function, class Argument>
class Functor : public Operator<Function, Argument> {
public:
    using Operator::Operator;
};

} namespace blazar::functions {
    
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
 
} namespace blazar::operators {

using namespace expressions; 
using namespace functions;

template<class Argument>
constexpr auto log(Argument&& argument) {
    return Functor<Log, Argument>({}, std::forward<Argument>(argument));
}

template<class Argument>
constexpr auto exp(Argument&& argument) {
    return Functor<Exp, Argument>({}, std::forward<Argument>(argument));
}

template<class Argument>
constexpr auto sqrt(Argument&& argument) {
    return Functor<Sqrt, Argument>({}, std::forward<Argument>(argument));
}  

template<class Argument>
constexpr auto rsqrt(Argument&& argument) {
    return Functor<Rsqrt, Argument>(std::forward<Argument>(argument));
}

template<class Argument>
constexpr auto abs(Argument&& argument) {
    return Functor<Abs, Argument>({}, std::forward<Argument>(argument));
}

template<class Argument>
constexpr auto sin(Argument&& argument) {
    return Functor<Sin, Argument>({}, std::forward<Argument>(argument));
} 

template<class Argument>
constexpr auto cos(Argument&& argument) {
    return Functor<Cos, Argument>({}, std::forward<Argument>(argument));
}
 
template<class Argument>
constexpr auto tan(Argument&& argument) {
    return Functor<Tan, Argument>({}, std::forward<Argument>(argument));
}
 
template<class Argument>
constexpr auto sinh(Argument&& argument) {
    return Functor<Sinh, Argument>({}, std::forward<Argument>(argument));
}
 
template<class Argument>
constexpr auto cosh(Argument&& argument) {
    return Functor<Cosh, Argument>({}, std::forward<Argument>(argument));
}
 
template<class Argument>
constexpr auto tanh(Argument&& argument) {
    return Functor<Tanh, Argument>({}, std::forward<Argument>(argument));
}

} namespace blazar {
    
using operators::log;
using operators::exp;
using operators::sqrt;
using operators::rsqrt;
using operators::abs;
using operators::sin;
using operators::cos;
using operators::tan;
using operators::sinh;
using operators::cosh;
using operators::tanh;

} 

#endif // FUNCTIONS_HPP_0x45524943 