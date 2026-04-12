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

#ifndef SUBSCRIPT_HPP_0x45524943 
#define SUBSCRIPT_HPP_0x45524943 
 
#include <cassert>  
#include "core/types.h" 
#include "exceptions.hpp"

namespace blazar::indexing { 

struct range_type {
    index_type start = 0;
    index_type stop  = -1;
};
 
constexpr auto normalize(index_type index, size_type bound) -> index_type {
    if (index < 0) {
        index += bound;
    }
    if (index < 0 || index > bound) {
        throw Exception("Index out of bounds");
    }
    return index;
}  
 
constexpr auto normalize(range_type range, size_type bound) -> range_type {
    index_type start = range.start < 0 ? bound + range.start : range.start;
    index_type stop  = range.stop  < 0 ? bound + range.stop  : range.stop; 

    if (start < 0 || start > bound || stop < 0 || stop > bound) {
        throw Exception("Range out of bounds");
    }
    return {.start=start, .stop=stop};
}

} namespace blazar {

using range = indexing::range_type;

} 

#endif // INDEXING_HPP_0x45524943 