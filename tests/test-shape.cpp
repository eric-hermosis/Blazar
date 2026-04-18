#include <gtest/gtest.h>
#include <blazar/shape.hpp> 

using namespace blazar;

TEST(ShapeTest, ConstexprConstruction) {
    constexpr Shape s(1, 2, 3);
    static_assert(s.size() == 3);
    static_assert(s[0] == 1);
    static_assert(s[1] == 2);
    static_assert(s[2] == 3);
    static_assert(s[-1] == 3);
    static_assert(s[-2] == 2);
    static_assert(s[-3] == 1);
}

TEST(ShapeTest, ConstexprEquality) {
    constexpr Shape a(1, 2, 3);
    constexpr Shape b(1, 2, 3);
    constexpr Shape c(1, 2, 4);

    static_assert(a == b);
    static_assert(!(a == c));
}

TEST(ShapeTest, ConstexprInitializerList) {
    constexpr Shape s{4, 5, 6};

    static_assert(s.size() == 3);
    static_assert(s[0] == 4);
    static_assert(s[1] == 5);
    static_assert(s[2] == 6);
}
 
TEST(ShapeTest, IterableConstructor) {
    std::vector<int> v = {2, 4, 6};

    Shape s(v);

    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s[0], 2);
    EXPECT_EQ(s[1], 4);
    EXPECT_EQ(s[2], 6);
}

TEST(ShapeTest, IteratorConstructor) {
    std::array<int, 3> arr = {7, 8, 9};

    Shape s(arr.begin(), arr.end());

    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s[0], 7);
    EXPECT_EQ(s[1], 8);
    EXPECT_EQ(s[2], 9);
}

TEST(ShapeTest, NegativeIndexing) {
    Shape s(10, 20, 30);

    EXPECT_EQ(s[-1], 30);
    EXPECT_EQ(s[-2], 20);
    EXPECT_EQ(s[-3], 10);
}

TEST(ShapeTest, Append) {
    Shape s(1, 2);

    s.append(3);
    s.append(4);

    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(s[2], 3);
    EXPECT_EQ(s[3], 4);
}

TEST(ShapeTest, Resize) {
    Shape s(1, 2, 3, 4);

    s.resize(2);

    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s[0], 1);
    EXPECT_EQ(s[1], 2);
}
 
TEST(ShapeTest, FrontBack) {
    Shape s(5, 6, 7);

    EXPECT_EQ(s.front(), 5);
    EXPECT_EQ(s.back(), 7);
}

TEST(ShapeTest, Equality) {
    Shape a(1, 2, 3);
    Shape b(1, 2, 3);
    Shape c(3, 2, 1);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
} 

TEST(ShapeTest, AppendExceedsLimitThrows) {
    Shape s(1,2,3,4,5,6,7,8);

    EXPECT_THROW(s.append(9), Exception);
}

TEST(ShapeTest, InvalidNegativeDimensionThrows) {
    EXPECT_THROW(
        Shape(1, -5, 3),
        Exception
    );
}

TEST(ShapeTest, AppendInvalidDimensionThrows) {
    Shape s(1, 2, 3);

    EXPECT_THROW(s.append(-5), Exception);
}


TEST(ShapeTest, DynamicDimensionAllowed) {
    Shape s(1, -1, 3);

    EXPECT_EQ(s[1], -1);
}

TEST(ShapeTest, AddressAccess) {
    Shape s(3, 4, 5);

    auto ptr = s.address();

    EXPECT_EQ(ptr[0], 3);
    EXPECT_EQ(ptr[1], 4);
    EXPECT_EQ(ptr[2], 5);
}
 

TEST(ShapeTest, Iteration) {
    Shape s(1, 2, 3);

    int expected = 1;
    for (auto v : s) {
        EXPECT_EQ(v, expected++);
    }
}