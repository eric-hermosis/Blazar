#ifndef GRAPHS_HPP
#define GRAPHS_HPP

#include <concepts>
#include <blazar/types.hpp>
#include <blazar/layouts.hpp>

namespace blazar {

class Node;
class Symbol; 
class Storage; 

template<class Expression>
concept Composable = requires(Expression const& expression) {
    { expression.type()   } -> std::same_as<Type const&>;
    { expression.layout() } -> std::same_as<Layout const&>;
};  

class Vertex {
public:
    constexpr Vertex() = default;

    constexpr ~Vertex() {
        if !consteval {
            release();
        }
    }

    constexpr Vertex(Vertex const& other) {
        if !consteval {
            copy(other);
        }
    }

    constexpr Vertex(Vertex && other) noexcept {
        if !consteval {
            move(other);
        }
    }

    constexpr auto operator=(Vertex const& other) -> Vertex& {
        if !consteval {
            copy(other);
            return *this;
        }
    }

    constexpr auto operator=(Vertex && other) noexcept -> Vertex& {
        if !consteval {
            move(other);
            return *this;
        }
    }

    operator bool() const noexcept;

    Vertex(Symbol const& symbol, Type const& type, Layout const& layout); 
    Vertex(Symbol const& symbol, Type const& type, Layout const& layout, Storage const& storage); 
    void move(Vertex& other) noexcept;
    void copy(Vertex const& other); 
    void link(Vertex const& other); 
    void release();
    void prune();

private:
    Node* node_ = nullptr;
};   

class Vertices {
public:
    std::size_t count = 0;  
};

}

#endif