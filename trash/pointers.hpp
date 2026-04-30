#ifndef POINTERS_HPP_0x45524943 
#define POINTERS_HPP_0x45524943 

#include <cstdint>
#include <cstddef>
#include <cassert> 
#include <utility>

namespace blazar {

template<class Object>
class Intrusive {
public:
    constexpr Intrusive() noexcept = default;  
    
    constexpr Intrusive(Intrusive const& other) { 
        if !consteval { 
            copy(other); 
        } 
    }
    
    constexpr Intrusive(Intrusive&& other) noexcept { 
        if !consteval { 
            move(other); 
        } 
    }

    constexpr auto operator=(Intrusive const& other) -> Intrusive& {
        if !consteval { 
            copy(other); 
        }
        return *this;
    }

    constexpr auto operator=(Intrusive&& other) noexcept -> Intrusive& {
        if !consteval { 
            move(other); 
        }
        return *this;
    }

    constexpr auto operator=(std::nullptr_t) noexcept -> Intrusive& {
        if !consteval { 
            release(); 
        } 
        
        else {
            object_ = nullptr;
        }
        return *this;
    }

    constexpr ~Intrusive() { 
        if !consteval { 
            release(); 
        }
    }  

    constexpr Intrusive(Object* object) 
    :   object_(object) {
        if !consteval {
            if (object_) {
                object_->acquire();
            }
        }
    } 

    void release() { 
        if(object_) {
            object_-> release();
            object_ = nullptr;
        }  
    }
    
    void copy(Intrusive const& other) { 
        if (object_ != other.object_) {  
            if (other.object_) {
                other.object_ -> acquire();
            }
            release();
            object_ = other.object_;
        }
    }
 
    void move(Intrusive& other) noexcept { 
        if (object_ != other.object_) {
            release();
            object_ = std::exchange(other.object_, nullptr);
        }
    }
 
    [[nodiscard]] constexpr auto operator->() const noexcept -> Object* { 
        assert(object_ != nullptr && "Fatal: Dereferencing a null Intrusive pointer!");
        return object_;
    }
 
    [[nodiscard]] constexpr auto operator*() const noexcept -> Object& {
        assert(object_ != nullptr && "Fatal: Dereferencing a null Intrusive pointer!");
        return *object_;
    }
 
    [[nodiscard]] constexpr auto get() const noexcept -> Object* {
        return object_;
    }
 
private:
    Object* object_ = nullptr;
}; 

}

#endif // POINTERS_HPP_0x45524943