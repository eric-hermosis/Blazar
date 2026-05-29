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

#ifndef SLICING_HPP_0x45524943 
#define SLICING_HPP_0x45524943 
 
#include <cassert>  
#include <blazar/core/types.h>
#include <blazar/exceptions.hpp>

namespace blazar::slicing { 

struct range_type {
    index_type start = 0;
    index_type stop  = -1;
}; 
 
constexpr auto normalize(range_type range, size_type bound) -> range_type {
    index_type start = range.start < 0 ? bound + range.start : range.start;
    index_type stop  = range.stop  < 0 ? bound + range.stop  : range.stop; 

    if (start < 0 || start > bound || stop < 0 || stop > bound) {
        throw Exception("Range out of bounds");
    }
    return {.start=start, .stop=stop};
}

} namespace blazar {

using range = slicing::range_type;

} 

#endif