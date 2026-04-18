#include <gtest/gtest.h>
#include <blazar/strides.hpp>
#include <blazar/shape.hpp>

using namespace blazar;

TEST(StridesTest, ConstexprConstruction) {
    constexpr Strides s(1, 2, 3);
    static_assert(s.size() == 3);
    static_assert(s[0] == 1);
    static_assert(s[1] == 2);
    static_assert(s[2] == 3);
    static_assert(s[-1] == 3);
    static_assert(s[-2] == 2);
    static_assert(s[-3] == 1);
}

TEST(StridesTest, ConstexprEquality) {
    constexpr Strides a(1, 2, 3);
    constexpr Strides b(1, 2, 3);
    constexpr Strides c(1, 2, 4);

    static_assert(a == b);
    static_assert(!(a == c));
}

TEST(StridesTest, ConstexprInitializerList) {
    constexpr Strides s{4, 5, 6};

    static_assert(s.size() == 3);
    static_assert(s[0] == 4);
    static_assert(s[1] == 5);
    static_assert(s[2] == 6);
}

TEST(StridesTest, IteratorConstructor) {
    std::array<int, 3> arr = {7, 8, 9};

    Strides s(arr.begin(), arr.end());

    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s[0], 7);
    EXPECT_EQ(s[1], 8);
    EXPECT_EQ(s[2], 9);
}

TEST(StridesTest, NegativeIndexing) {
    Strides s(10, 20, 30);

    EXPECT_EQ(s[-1], 30);
    EXPECT_EQ(s[-2], 20);
    EXPECT_EQ(s[-3], 10);
}

TEST(StridesTest, Append) {
    Strides s(1, 2);

    s.append(3);
    s.append(4);

    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(s[2], 3);
    EXPECT_EQ(s[3], 4);
}

TEST(StridesTest, Resize) {
    Strides s(1, 2, 3, 4);

    s.resize(2);

    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s[0], 1);
    EXPECT_EQ(s[1], 2);
}

TEST(StridesTest, FrontBack) {
    Strides s(5, 6, 7);

    EXPECT_EQ(s.front(), 5);
    EXPECT_EQ(s.back(), 7);
}

TEST(StridesTest, Equality) {
    Strides a(1, 2, 3);
    Strides b(1, 2, 3);
    Strides c(3, 2, 1);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(StridesTest, AppendExceedsLimitThrows) {
    Strides s(1,2,3,4,5,6,7,8);

    EXPECT_THROW(s.append(9), Exception);
}

TEST(StridesTest, InvalidNegativeDimensionThrows) {
    EXPECT_THROW(
        Strides(1, -5, 3),
        Exception
    );
}

TEST(StridesTest, AppendInvalidDimensionThrows) {
    Strides s(1, 2, 3);

    EXPECT_THROW(s.append(-5), Exception);
}

TEST(StridesTest, DynamicDimensionAllowed) {
    Strides s(1, -1, 3);

    EXPECT_EQ(s[1], -1);
}

TEST(StridesTest, AddressAccess) {
    Strides s(3, 4, 5);

    auto ptr = s.address();

    EXPECT_EQ(ptr[0], 3);
    EXPECT_EQ(ptr[1], 4);
    EXPECT_EQ(ptr[2], 5);
}

TEST(StridesTest, Iteration) {
    Strides s(1, 2, 3);

    int expected = 1;
    for (auto v : s) {
        EXPECT_EQ(v, expected++);
    }
}