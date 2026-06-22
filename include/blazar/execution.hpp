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
#ifndef EXECUTION_HPP_0x45524943  
#define EXECUTION_HPP_0x45524943  

#include <vector>
#include <memory>
#include <tuple>
#include <blazar/graph.hpp>
#include <blazar/storage.hpp> 
#include <blazar/handlers.hpp>
#include <blazar/environments.hpp>

namespace blazar::execution { 

class Task;
class Tasks;

class Item {
public:
    Item() = default;
    Item(Task* task);  
    auto get() const -> Task*;
    void succeed(Item const&); 

private:  
    Task* task_ = nullptr; 
};

class Items {
public:  
    using Index = std::size_t;

    Items(std::size_t count);
    ~Items();
    Items(Items&&) = delete;
    Items& operator=(Items&&) = delete; 
    Items(const Items&) = delete;
    Items& operator=(const Items&) = delete;   

    template<class Symbol, class ... Items>
    auto build(Symbol, Index index, Vertex const& vertex, Items const& ... items) -> Item {
        auto item = create(index); 
        template for (auto const& prior : std::tuple{items...}) {
            item.succeed(prior);
        }
        return item;
    } 
 
    bool has(Index index);
    auto get(Index index) -> Item;    
    auto create(Index index) -> Item;

private:
    std::unique_ptr<Tasks> tasks_; 
};
 
}

#endif