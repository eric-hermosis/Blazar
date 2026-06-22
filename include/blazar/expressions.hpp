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
 
#include <tuple> 
#include <type_traits>
#include <blazar/types.hpp>
#include <blazar/layouts.hpp>
#include <blazar/graph.hpp> 
#include <blazar/execution.hpp> 
#include <blazar/handlers.hpp>

namespace blazar::expressions {
    
using layouts::index_type;
using layouts::range_type; 
using execution::Item;
using execution::Items;

template<class Expression>
class Trait {
public:
    using type = typename std::decay<Expression>::type;
};
 
template<class Symbol, class Source> class View;
struct Slice; 

template<class Symbol, class ... Expressions>
class Expression {
public: 
    using Index = std::size_t;
    std::decay<Symbol>::type symbol;
    std::tuple<typename Trait<Expressions>::type ...> sources;  

    constexpr Expression(Symbol symbol, Expressions const& ... expressions) 
    :   symbol(symbol)
    ,   sources(expressions...) {}

    template<typename Self>
    constexpr auto operator[](this Self&& self, index_type index) {
        return View<Slice, Self>(std::forward<Self>(self), index);
    }

    template<typename Self>
    constexpr auto operator[](this Self&& self, range_type range) {
        return View<Slice, Self>(std::forward<Self>(self), range);
    } 

    template<typename Self, class ... Arguments>
    constexpr auto operator[](this Self&& self, Arguments... arguments) {
        return View<Slice, Self>(std::forward<Self>(self), arguments...);
    }

    template<typename Self>
    auto forward(this Self&& self, Vertices& vertices) -> Vertex const& {
        if(!self.vertex_) { 
            self.vertex_ = Vertex(self.symbol, self.type(), self.layout());
            self.index_  = Index(vertices.count++);  
            template for (auto const& source : self.sources) {    
                self.vertex_.link(source.forward(vertices));
            }   
        }
        return self.vertex_;
    } 

    template<typename Self>
    auto forward(this Self&& self, Items& items) -> Item {   
        if (items.has(self.index_)) {
            return items.get(self.index_);
        } 
        
        else {
            return std::apply([&](auto && ... sources) -> Item {
                return items.build(
                    self.symbol,
                    self.index_, 
                    self.vertex_, 
                    std::forward<decltype(sources)>(sources).forward(items)...
                );
            }, self.sources);
        } 
    }
 
    auto index() const -> Index {
        return index_;
    }

    auto vertex() const -> Vertex const& {
        return vertex_;
    }  

private:
    mutable Index index_;
    mutable Vertex vertex_; 
};

}

#endif