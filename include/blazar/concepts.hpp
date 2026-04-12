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

#ifndef CONCEPTS_HPP_0x45524943 
#define CONCEPTS_HPP_0x45524943  

#include <concepts>
#include <iterator>   

namespace blazar {

template<typename Type>
concept Iterable = requires(Type type) { std::begin(type); std::end(type); };   

template <typename Type>
concept Iterator = std::input_iterator<Type>;  

template<typename Type>
concept Integral = std::integral<Type>;
    
} // namespace blazar

#endif // CONCEPTS_HPP_0x45524943