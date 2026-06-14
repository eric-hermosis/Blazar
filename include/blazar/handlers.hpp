#ifndef DISPATCHER_HPP_0x45524943 
#define DISPATCHER_HPP_0x45524943 
  
#include <blazar/environments.hpp>

namespace blazar { 

class Handler { 
    
};
  
class Handlers {
public: 
    template<typename Symbol, typename... Types>
    static auto get(Symbol, Environment const& environment, Types const&... types) -> Handler;
};
    
}

#endif