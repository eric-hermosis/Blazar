#include <gtest/gtest.h>
#include <blazar/variables.hpp>
#include <blazar/expressions/operations.hpp> 

using namespace blazar;

TEST(OperationsTest, ConstexprUnaryShapePropagation) {
    constexpr Variable a(float32, {2,3});
    constexpr auto b = -a;
    static_assert(b.rank() == 2);
    static_assert(b.size() == 6);
    static_assert(b.shape()[0] == 2);
    static_assert(b.shape()[1] == 3);
}

TEST(OperationsTest, ConstexprBinarySameShape) {
    constexpr Variable a(float32, {2, 3});
    constexpr Variable b(float32, {2, 3});

    constexpr auto c = a + b;
    static_assert(c.rank() == 2);
    static_assert(c.size() == 6);
    static_assert(c.shape()[0] == 2);
    static_assert(c.shape()[1] == 3);
}

TEST(OperationsTest, ConstexprBroadcastTrailing) {
    constexpr Variable a(float32, Shape(3, 4));
    constexpr Variable b(float32, Shape(4));

    constexpr auto c = a + b;

    static_assert(c.rank() == 2);
    static_assert(c.shape()[0] == 3);
    static_assert(c.shape()[1] == 4);
    static_assert(c.size() == 12);
}

TEST(OperationsTest, ConstexprBroadcastLeading) {
    constexpr Variable a(float32, Shape(4));
    constexpr Variable b(float32, Shape(3, 4));

    constexpr auto c = a + b;

    static_assert(c.rank() == 2);
    static_assert(c.shape()[0] == 3);
    static_assert(c.shape()[1] == 4);
}

TEST(OperationsTest, ConstexprBroadcastBothSides) {
    constexpr Variable a(float32, Shape(1, 4));
    constexpr Variable b(float32, Shape(3, 1));

    constexpr auto c = a + b;

    static_assert(c.rank() == 2);
    static_assert(c.shape()[0] == 3);
    static_assert(c.shape()[1] == 4);
}

TEST(OperationsTest, ConstexprBroadcastHigherRank) {
    constexpr Variable a(float32, Shape(2, 1, 4));
    constexpr Variable b(float32, Shape(3, 4));

    constexpr auto c = a + b;

    static_assert(c.rank() == 3);
    static_assert(c.shape()[0] == 2);
    static_assert(c.shape()[1] == 3);
    static_assert(c.shape()[2] == 4);
}

TEST(OperationsTest, ConstexprBroadcastScalar) {
    constexpr Variable a(float32, Shape(2, 3));
    constexpr Variable b(float32); // scalar

    constexpr auto c = a + b;

    static_assert(c.rank() == 2);
    static_assert(c.shape()[0] == 2);
    static_assert(c.shape()[1] == 3);
    static_assert(c.size() == 6);
}
TEST(OperationsTest, ConstexprBroadcastScalarScalar) {
    constexpr Variable a(float32);
    constexpr Variable b(float32);

    constexpr auto c = a + b;

    static_assert(c.rank() == 0);
    static_assert(c.size() == 1);
}