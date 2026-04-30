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
#ifndef TYPES_H_0x45524943
#define TYPES_H_0x45524943 
 
enum type {   
    boolean, 
    uint8,
    uint16,
    uint32,
    uint64,
    int8,
    int16,
    int32,
    int64,
    float16,
    bfloat16,
    float32,
    float64,
    complex64,   
    complex128,  
    any,
    object,
    unknown,
    TYPES
};  

#ifdef __cplusplus 
#include <cstdint>   
using rank_type  = std::uint8_t; 
using code_type  = std::int16_t; 
using size_type  = std::int64_t ;
using index_type = std::int64_t ;
#else
#include <stdint.h>  
typedef uint8_t rank_type;
typedef int16_t code_type;
typedef int64_t size_type;
typedef int64_t index_type; 
#endif 
 
#endif // TYPES_H_0x45524943