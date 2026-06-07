#include <blazar/exceptions.hpp>
#include <blazar/runtime/domains.hpp>

namespace blazar {

Host::Host() {
    allocator_ = Allocator("malloc",
        [](std::size_t size) noexcept -> void* { return std::malloc(size); },
        [](void* address, std::size_t size) noexcept -> void { std::free(address); }
    );
}

auto Host::allocator() const -> Allocator const& {
    return allocator_;
}

Environment operator|(Environment const& first, Environment const& second) {
    if (std::holds_alternative<Host>(first) && std::holds_alternative<Host>(second)) {
        return Host();
    } 
    
    else {
        throw Exception("Incompatible Environments"); 
    } 
} 

}