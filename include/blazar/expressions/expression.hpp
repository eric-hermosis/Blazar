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
#ifndef EXPRESSION_HPP_0x45524943
#define EXPRESSION_HPP_0x45524943
 
#include <type_traits>
#include <tuple>

namespace blazar::expressions {

template<class Expression>
class Trait {
public:
    using Type = typename std::decay<Expression>::type;
};

template<class Symbol, class ... Sources>
class Expression {
public:
    Symbol symbol;
    std::tuple<typename Trait<Sources>::Type ...> sources;

    constexpr Expression(Symbol symbol, Sources const& ... sources) 
    :   symbol(symbol)
    ,   sources(sources...)
    {}
};

}

#endif