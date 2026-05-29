#ifndef VARIABLES_HPP_0x45524943 
#define VARIABLES_HPP_0x45524943 

#include <blazar/types.hpp>
#include <blazar/concepts.hpp>
#include <blazar/layout/shape.hpp>
#include <blazar/layout/strides.hpp>  
#include <blazar/expressions/views/slice.hpp>

namespace blazar::expressions { 

using concepts::Integral;
  
class Variable {
public:    

    constexpr Variable()
    :   type_(unknown)
    ,   size_(0)
    ,   rank_(0)
    ,   offset_(0) {}

    constexpr Variable(Type type)
    :   type_(type)
    ,   size_(1)
    ,   rank_(0)
    ,   offset_(0) {}

    constexpr Variable(Type type, Shape const& shape)
    :   type_(type) 
    ,   size_(1)
    ,   rank_(shape.size())
    ,   offset_(0)
    ,   shape_(shape)
    {    
        if (rank_ > 0) {
            strides_.resize(rank_);
 
            for(auto dimension = rank_ - 1; dimension >= 0; --dimension) {
                strides_[dimension] = size_;
                size_ *= shape[dimension];
            } 
        } 
    }
 
    constexpr Variable(Type type, Shape const& shape, Strides const& strides)
    :   type_(type) 
    ,   size_(1)
    ,   rank_(shape.size())
    ,   offset_(0)
    ,   shape_(shape)
    ,   strides_(strides) {  
        if (rank_ > 0) {
            for(auto dimension = rank_ - 1; dimension >= 0; --dimension) {
                size_ *= shape[dimension];
            } 
        } 
    }        

    [[nodiscard]] constexpr auto type() const noexcept -> Type const &{
        return type_;
    }

    [[nodiscard]] constexpr auto rank() const noexcept -> rank_type {
        return rank_;
    }

    [[nodiscard]] constexpr auto size() const noexcept -> size_type {
        return size_;
    } 
    
    [[nodiscard]] constexpr auto size(rank_type dimension) const noexcept -> size_type {
        return shape_[dimension];
    }

    [[nodiscard]] constexpr auto stride(rank_type dimension) const noexcept -> size_type {
        return strides_[dimension];
    }

    [[nodiscard]] constexpr auto offset() const noexcept -> index_type{
        return offset_;
    } 

    [[nodiscard]] constexpr auto shape() const noexcept -> Shape const& {
        return shape_;
    }

    [[nodiscard]] constexpr auto strides() const noexcept -> Strides const& {
        return strides_;
    } 
  
    [[nodiscard]] constexpr auto bytes() const -> std::size_t {
        return size() * type_.size();
    }       

    template<typename Self, Integral Index>
    constexpr auto operator[](this Self&& self, Index index) {
        return views::Slice<Self, Index>(self, index);
    }

    template<typename Self>
    constexpr auto operator[](this Self&& self, range range) {
        return views::Slice<Self, slicing::range_type>(self, range);
    } 

    template<typename Self, class ... Indexes>
    constexpr auto operator[](this Self&& self, Indexes... indexes) {
        return views::Slice<Self, Indexes...>(self, indexes...);
    }  

private:
    Type type_;    
    Shape shape_;
    Strides strides_;     
    size_type size_;   
    rank_type rank_; 
    index_type offset_;   
}; 

} namespace blazar {

using expressions::Variable;

}

#endif 