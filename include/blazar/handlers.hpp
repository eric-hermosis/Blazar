#ifndef HANDLERS_HPP_0x45524943 
#define HANDLERS_HPP_0x45524943 

#include <blazar/types.hpp>
#include <blazar/environments.hpp>
#include <iostream>

namespace blazar { 

class Handler { 
    
};
  
class Handlers {
public: 
    template<typename Symbol, typename... Types>
    static auto get(Symbol, Environment const& environment, Types const&... types) -> Handler;

    template<typename Symbol, auto Arity>
    static auto get(Symbol symbol, Environment const& environment, std::array<Type, Arity> const& types) -> Handler{
        return std::apply( [&](auto const&... type) {
            return Handlers::get(symbol, environment, type...);
        }, types);
    }
 
    template<typename Symbol, auto Arity>
    static auto get(Symbol symbol, Environment const& environment, Type const (&types)[Arity]) -> Handler{ 
        return [&]<std::size_t... Index>(std::index_sequence<Index...>) {
            return Handlers::get(symbol, environment, types[Index]...);
        }(std::make_index_sequence<Arity>{});
    } 
};
    
}

#endif