#ifndef VIEWS_HPP_0x45524943
#define VIEWS_HPP_0x45524943
 
#include <blazar/types.hpp>
#include <blazar/layouts.hpp>
#include <blazar/expressions.hpp>

namespace blazar::expressions { 

struct Slice {};

template<class Source>
class View<Slice, Source> : public Expression<Slice, Source> {
public:  
    template<class ... Indexes>
    constexpr View(Source const& source, Indexes ... indexes) 
    :   Expression<Slice, Source>({}, source)
    {  
        auto dimension = 0;    
        auto offset = source.layout().offset();

        Shape shape;
        Strides strides;

        template for (auto const& argument: std::make_tuple(indexes...)) {
            using Argument = std::decay_t<decltype(argument)>; 

            if constexpr (std::is_same_v<Argument, range_type>) { 
                auto range = layouts::normalize(argument, source.layout().size(dimension));
                auto size = range.stop - range.start; 
                shape.append(size);
                strides.append(source.layout().stride(dimension)); 
                offset += range.start * source.layout().stride(dimension); 
                dimension++;
            } 
            
            else if constexpr (std::is_integral_v<Argument>) { 
                auto index = layouts::normalize(argument, source.layout().size(dimension));
                offset += index * source.layout().stride(dimension);
                dimension++;
            }

            else {         
                throw Exception("Invalid index type"); 
            }  
        }
 
        while (dimension < source.layout().rank()) {
            shape.append(source.layout().size(dimension));
            strides.append(source.layout().stride(dimension));
            dimension++;
        } 

        type_   = source.type();
        layout_ = Layout(shape, strides, offset);
    }


    [[nodiscard]] constexpr auto type() const -> Type const& {
        return type_;
    }

    [[nodiscard]] constexpr auto layout() const -> Layout const& {
        return layout_;
    }

private:
    Type type_;
    Layout layout_;
};

}

#endif