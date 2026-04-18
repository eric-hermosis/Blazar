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