#ifndef EXPRESSIONS_HPP_0x45524943
#define EXPRESSIONS_HPP_0x45524943
 
#include <tuple> 
#include <type_traits>
#include <blazar/types.hpp>
#include <blazar/layouts.hpp>

namespace blazar::expressions {
    
using layouts::index_type;
using layouts::range_type;
 
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
};

}

#endif