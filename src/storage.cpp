#include <blazar/storage.hpp>
#include <blazar/memory.hpp>
#include <blazar/exceptions.hpp>

namespace blazar {

Storage::Storage(std::size_t size, Environment const& environment) {
    memory_ = Memory::allocate(size, environment);
}
 
void Storage::release() { 
    if (memory_) {
        memory_-> release();  
        memory_ = nullptr;
    }  
}

void Storage::copy(Storage const& other) {
    if (memory_ != other.memory_) {  
        if (other.memory_) {
            other.memory_ -> acquire();
        }
        release();
        memory_ = other.memory_;
    }
}

void Storage::move(Storage & other) noexcept { 
    if (memory_ != other.memory_) {
        release();
        memory_ = std::exchange(other.memory_, nullptr);
    }
}

auto Storage::size() const noexcept -> std::size_t {
    return memory_ ? memory_->size() : 0;
}

auto Storage::environment() const noexcept -> Environment const& {  
    static const Environment nowhere = std::monostate{};
    return memory_ ? memory_ -> environment() : nowhere;
}

auto Storage::get() const noexcept -> Memory const* {
    return memory_;
}

} 