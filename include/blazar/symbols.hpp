#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP 

#include <meta> 
#include <string_view>

namespace blazar {

class Symbol {
public:
    template<class Tag>
    constexpr Symbol(Tag const&)  
    :   name_(std::meta::identifier_of(^^Tag))  
    {}
    
    [[nodiscard]] constexpr auto name() const -> std::string_view { 
        return name_; 
    }

private:    
    std::string_view name_;
};

}

#endif