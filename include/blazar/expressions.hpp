#ifndef EXPRESSIONS_HPP_0x45524943
#define EXPRESSIONS_HPP_0x45524943
 
#include <tuple> 
#include <type_traits>
#include <blazar/types.hpp>
#include <blazar/layouts.hpp>
#include <blazar/graph.hpp> 
#include <blazar/execution.hpp>

namespace blazar::expressions {
    
using layouts::index_type;
using layouts::range_type;
using execution::Item;
using execution::Plan;

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
    auto forward(this Self&& self, Graph& graph) -> Vertex const& {
        if(!self.vertex_) { 
            self.vertex_ = Vertex(self.symbol, self.type(), self.layout());
            template for (auto const& source : self.sources) {    
                self.vertex_.link(source.forward(graph));
            }  
            self.index_ = ++graph.size;  
        }
        return self.vertex_;
    }

    template<typename Self>
    auto forward(this Self&& self, Plan& plan) -> Item {
        if (plan.visited(self)) {
            return Item();

        } else {
            plan.visit(self);
            return Item();
        } 
    }
 
    auto index() const -> int {
        return index_;
    }

    auto vertex() const -> Vertex const& {
        return vertex_;
    }

private:
    mutable int index_;
    mutable Vertex vertex_; 
};

}

#endif