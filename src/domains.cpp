#include <blazar/exceptions.hpp>
#include <blazar/resources/domains.hpp>

namespace blazar {
  
Environment operator|(Environment const& first, Environment const& second) {
    if (std::holds_alternative<Host>(first) && std::holds_alternative<Host>(second)) {
        return Host();
    } 
    
    else {
        throw Exception("Incompatible Environments"); 
    } 
} 

}