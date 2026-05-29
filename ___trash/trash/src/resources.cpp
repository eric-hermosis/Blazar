#include <blazar/resources.hpp>
#include <blazar/exceptions.hpp>

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