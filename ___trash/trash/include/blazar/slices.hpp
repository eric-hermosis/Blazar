#ifndef SLICES_HPP_0x45524943 
#define SLICES_HPP_0x45524943 

#include <blazar/concepts.hpp>
#include <blazar/exceptions.hpp>
#include <blazar/indexing.hpp>
#include <blazar/types.hpp>
#include <blazar/shape.hpp>
#include <blazar/strides.hpp>

namespace blazar {
 
template<class Source, class ... Indexes>
class Slice {
public:       
    Source source;
    std::tuple<Indexes...> indexes;    

    constexpr Slice(Source const& source, Indexes... indexes) 
    :   source(source) 
    ,   type_(source.type())
    ,   rank_(0)
    ,   offset_(0)
    {
        auto dimension = 0;  
        template for (auto const& argument: std::make_tuple(indexes...)) {
            using Argument = std::decay_t<decltype(argument)>; 
            if constexpr (std::is_same_v<Index, indexing::Range>) { 
                auto range = indexing::normalize(argument, source.shape()[dimension]);
                auto size = range.stop - range.start; 
                shape_.append(size);
                strides_.append(source.strides()[dimension]); 
                offset_ += range.start * source.strides()[dimension] * dsizeof(dtype_); 
                rank_++; 
                dimension++;
            } 
            
            else if constexpr (std::is_integral_v<Index>) { 
                auto index = indexing::normalize(argument, source.shape()[dimension]);
                offset_ += index * source.strides()[dimension] * dsizeof(dtype_);
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

    template<Integral Index>
    constexpr auto operator[](Index index) const { 
        return Slice<Source, Indexes..., Index>(this->source, std::tuple_cat(indexes, std::make_tuple(index)));
    } 
    
    constexpr auto operator[](indexing::Range range) const {    
        return Slice<Source, Indexes..., indexing::Range>(this->source, std::tuple_cat(indexes, std::make_tuple(range)));
    }  
    
    constexpr auto dtype() const -> Type const& {
        return dtype_;
    } 

    constexpr auto rank() const -> rank_type {
        return shape_.rank();
    } 

    constexpr auto shape() const -> Shape const& {
        return shape_;
    }

    constexpr auto strides() const -> Strides const& {
        return strides_;
    }  

    constexpr auto offset() const -> index_type {
        return offset_ + source_.offset();
    } 

private:    
    Type      type_;    
    Shape     shape_;
    Strides   strides_;
    size_type size_;   
    rank_type rank_;  
};

}

#endif