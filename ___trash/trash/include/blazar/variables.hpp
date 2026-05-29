#ifndef VARIABLES_HPP_0x45524943 
#define VARIABLES_HPP_0x45524943 

#include <blazar/types.hpp>
#include <blazar/shape.hpp>
#include <blazar/strides.hpp> 
#include <blazar/concepts.hpp>

namespace blazar { 
  
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

    constexpr Variable(Type type, size_type size, rank_type rank, index_type offset, Shape shape, Strides strides)
    :   type_(type) 
    ,   size_(size)
    ,   rank_(rank)
    ,   offset_(offset)
    ,   shape_(std::move(shape))
    ,   strides_(std::move(strides)) {} 

    template<Composable Expression> 
    constexpr Variable(Expression const& expression) 
    :   type_(expression.type()) 
    ,   size_(expression.size()) 
    ,   rank_(expression.rank()) 
    ,   offset_(expression.offset()) 
    ,   shape_(expression.shape()) 
    ,   strides_(expression.strides()) {}
 
    template<Composable Expression> 
    constexpr Variable(Expression&& expression) 
    :   type_(std::forward<Expression>(expression).type()) 
    ,   size_(std::forward<Expression>(expression).size()) 
    ,   rank_(std::forward<Expression>(expression).rank()) 
    ,   offset_(std::forward<Expression>(expression).offset()) 
    ,   shape_(std::forward<Expression>(expression).shape()) 
    ,   strides_(std::forward<Expression>(expression).strides()) 
    {} 

    template<Composable Expression>
    constexpr auto operator=(Expression const& expression) -> Variable& { 
        *this = Variable(expression);
        return *this;
    }
    
    template<Composable Expression>
    constexpr auto operator=(Expression&& expression) -> Variable& {
        *this = Variable(std::forward<Expression>(expression));
        return *this;
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

    [[nodiscard]] constexpr auto offset() const noexcept -> index_type {
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

private: 
    Type type_;     
    rank_type rank_; 
    size_type size_;   
    index_type offset_;   
    Shape shape_;
    Strides strides_;       
}; 

}

#endif 