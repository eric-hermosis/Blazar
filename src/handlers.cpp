#include <blazar/handlers.hpp>
#include <blazar/operations.hpp>
#include <blazar/functions.hpp> 

namespace blazar {

using operations::Negation;
using operations::Addition;
using operations::Division;
using operations::Subtraction;
using operations::Multiplication; 
using operations::Exponentiation;

using functions::Log;
using functions::Exp;
using functions::Sqrt;
using functions::Rsqrt;
using functions::Abs;
using functions::Sin;
using functions::Cos;
using functions::Tan;
using functions::Sinh;
using functions::Cosh;
using functions::Tanh;

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

template<>
auto Handlers::get(Log, Environment const& environment, Type const& type) -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Exp, Environment const& environment, Type const& type) -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Sqrt, Environment const& environment, Type const& type) -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Rsqrt, Environment const& environment, Type const& type) -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Abs, Environment const& environment, Type const& type) -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Sin, Environment const& environment, Type const& type) -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Cos, Environment const& environment, Type const& type) -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Tan, Environment const& environment, Type const& type) -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Sinh, Environment const& environment, Type const& type) -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Cosh, Environment const& environment, Type const& type) -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Tanh, Environment const& environment, Type const& type) -> Handler {
    return Handler{};
}

}