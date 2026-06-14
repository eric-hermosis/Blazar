#include <blazar/handlers.hpp>
#include <blazar/operations.hpp>

namespace blazar {

using operations::Negation;
using operations::Addition;
using operations::Division;
using operations::Subtraction;
using operations::Multiplication; 
using operations::Exponentiation;

template<>
auto Handlers::get(Negation, Environment const& environment, Type const& type) -> Handler {
    return Handler{};
};

template<>
auto Handlers::get(Addition, Environment const& environment, Type const& first, Type const& second) -> Handler {
    return Handler{};
};

template<>
auto Handlers::get(Division, Environment const& environment, Type const& first, Type const& second) -> Handler {
    return Handler{};
};

template<>
auto Handlers::get(Subtraction, Environment const& environment, Type const& first, Type const& second) -> Handler {
    return Handler{};
};

template<>
auto Handlers::get(Multiplication, Environment const& environment, Type const& first, Type const& second) -> Handler {
    return Handler{};
};

template<>
auto Handlers::get(Exponentiation, Environment const& environment, Type const& first, Type const& second) -> Handler {
    return Handler{};
};

}