#ifndef SLICE_HPP_0x45524943 
#define SLICE_HPP_0x45524943 

#include <blazar/concepts.hpp>
#include <blazar/exceptions.hpp>
#include <blazar/types.hpp>
#include <blazar/layout/indexing.hpp>
#include <blazar/layout/slicing.hpp>
#include <blazar/layout/shape.hpp>
#include <blazar/layout/strides.hpp>

namespace blazar::views {
 
template<class Source, class ... Indexes>
class Slice {
public:       
    Source source;
    std::tuple<Indexes...> indexes;    

    constexpr Slice(Source const& source, Indexes... indexes) 
    :   source(source) 
    ,   type_(source.type())
    ,   rank_(0)
    ,   offset_(source.offset())
    {
        auto dimension = 0;  
        
        template for (auto const& argument: std::make_tuple(indexes...)) {

            using Argument = std::decay_t<decltype(argument)>; 

            if constexpr (std::is_same_v<Argument, slicing::range_type>) { 
                auto range = slicing::normalize(argument, source.shape()[dimension]);
                auto size = range.stop - range.start; 
                shape_.append(size);
                strides_.append(source.strides()[dimension]); 
                offset_ += range.start * source.strides()[dimension]; 
                rank_++; 
                dimension++;
            } 
            
            else if constexpr (std::is_integral_v<Argument>) { 
                auto index = indexing::normalize(argument, source.shape()[dimension]);
                offset_ += index * source.strides()[dimension];
                dimension++;
            }

            else {         
                throw Exception("Invalid index type"); 
            }  
        }
 
        while (dimension < source.rank()) {
            shape_.append(source.shape()[dimension]);
            strides_.append(source.strides()[dimension]);
            rank_++; 
            dimension++;
        } 
    }  
    
    [[nodiscard]] constexpr auto type() const -> Type const& {
        return type_;
    } 

    [[nodiscard]] constexpr auto rank() const -> rank_type {
        return rank_;
    } 

    [[nodiscard]] constexpr auto shape() const -> Shape const& {
        return shape_;
    }

    [[nodiscard]] constexpr auto strides() const -> Strides const& {
        return strides_;
    }  

    [[nodiscard]] constexpr auto offset() const -> index_type {
        return offset_;
    } 

private:    
    Type       type_;    
    Shape      shape_;
    Strides    strides_;
    size_type  size_;   
    rank_type  rank_;  
    index_type offset_;
};

}

#endif