#ifndef TENSORS_HPP_0x45524943
#define TENSORS_HPP_0x45524943

#include <blazar/types.hpp>
#include <blazar/layouts.hpp>
#include <blazar/views.hpp>
#include <blazar/storage.hpp>
#include <blazar/graph.hpp>
#include <blazar/symbols.hpp>
#include <blazar/execution.hpp>

namespace blazar::variables {
 
using layouts::index_type;
using layouts::range_type; 
using expressions::View;
using expressions::Slice;   
using execution::Item;
using execution::Items;

class Tensor {
public: 
    constexpr Tensor(Type const& type)
    :   type_(type) {}

    constexpr Tensor(Type const& type, Shape const& shape)
    :   type_(type)
    ,   layout_(shape) {}

    constexpr Tensor(Type const& type, Shape const& shape, Strides const& strides)
    :   type_(type)
    ,   layout_(shape, strides) {}

    constexpr Tensor(Composable auto const& expression) 
    :   type_(expression.type())
    ,   layout_(expression.layout()) {
        if !consteval {
            auto vertices = Vertices();  
            auto items    = Items(vertices.count);
            vertex_ = expression.forward(vertices);
            vertex_.prune();
        }
    }

    constexpr auto operator=(Composable auto const& expression) -> Tensor& {
        type_   = expression.type();
        layout_ = expression.layout();        
        if !consteval {  
            auto vertices = Vertices();   
            vertex_ = expression.forward(vertices);
            vertex_.prune();
        }
        return *this;
    } 

    template<typename Self>
    constexpr auto operator[](this Self&& self, index_type index) {
        return View<Slice, Self>(self, index);
    }

    template<typename Self>
    constexpr auto operator[](this Self&& self, range_type range) {
        return View<Slice, Self>(self, range);
    } 

    template<typename Self, class ... Arguments> 
    requires (sizeof...(Arguments) > 0) && (... && (std::integral<Arguments> || std::convertible_to<std::decay_t<Arguments>, range_type>))
    constexpr auto operator[](this Self&& self, Arguments... arguments) {
        return View<Slice, Self>(self, arguments...);
    }  

    [[nodiscard]] constexpr auto type() const -> Type const& {
        return type_;
    }

    [[nodiscard]] constexpr auto layout() const -> Layout const& {
        return layout_;
    }

    void initialize(Environment const& environment = Host()) const {
        storage_ = Storage(layout_.size(), environment); 
        vertex_  = Vertex(*this, type(), layout(), storage_); 
    }
 
    auto forward(Vertices& graph) const -> Vertex const& { 
        return vertex_;
    }   

    auto forward(Items& items) const -> Item {
        return Item();
    }

private:
    Type type_;
    Layout layout_;
    mutable Storage storage_;
    mutable Vertex  vertex_;
};

} namespace blazar {

using variables::Tensor;

}

#endif