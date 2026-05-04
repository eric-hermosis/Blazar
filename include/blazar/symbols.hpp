#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP 

#include <meta> 
#include <string_view>

namespace blazar {

class Symbol {
public:
    template<class Primitive>
    constexpr Symbol(Primitive const& primitive)  
    :   name_(std::meta::identifier_of(^^Primitive))  
    {}
    
    [[nodiscard]] constexpr auto name() const -> std::string_view { 
        return name_; 
    }

private:    
    std::string_view name_;
};

}

#endif