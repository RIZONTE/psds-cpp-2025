#include <gtest/gtest.h>

#include <vector>

#include "find_all.cpp"

bool IsEven(int x) {
    return x % 2 == 0;
}

bool IsPositive(int x) {
    return x > 0;
}

bool AlwaysFalse(int) {
    return false;
}

TEST(FindAllTest, EmptyVector) {
    std::vector<int> empty_vec;
    auto result = FindAll(empty_vec, IsEven);
    EXPECT_TRUE(result.empty());
}

TEST(FindAllTest, NullptrPredicate) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto result = FindAll(vec, nullptr);
    EXPECT_TRUE(result.empty());
}

TEST(FindAllTest, SingleElementTrue) {
    std::vector<int> vec = {18};
    auto result = FindAll(vec, IsEven);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 0);
}

TEST(FindAllTest, SingleElementFalse) {
    std::vector<int> vec = {17};
    auto result = FindAll(vec, IsEven);
    EXPECT_TRUE(result.empty());
}

TEST(FindAllTest, AllElementsPass) {
    std::vector<int> vec = {2, 4, 6, 8, 10};
    auto result = FindAll(vec, IsEven);

    EXPECT_EQ(result.size(), vec.size());
    std::vector<size_t> expected = {0, 1, 2, 3, 4};
    EXPECT_EQ(result, expected);
}

TEST(FindAllTest, AllElementsFalse) {
    std::vector<int> vec = {1, 3, 5, 7, 9};
    auto result = FindAll(vec, IsEven);
    EXPECT_TRUE(result.empty());
}

TEST(FindAllTest, MixedElements) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = FindAll(vec, IsEven);
    std::vector<size_t> expected = {1, 3, 5, 7, 9};
    EXPECT_EQ(result, expected);
}

TEST(FindAllTest, NotSortedElements) {
    std::vector<int> vec = {10, 2, 3, 4, 5, 7, 6, 8, 9, 1};
    auto result = FindAll(vec, IsEven);
    std::vector<size_t> expected = {0, 1, 3, 6, 7};
    EXPECT_EQ(result, expected);
}

TEST(FindAllTest, AllFalsePredicate) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto result = FindAll(vec, AlwaysFalse);
    EXPECT_TRUE(result.empty());
}

TEST(FindAllTest, LargeVector) {
    const size_t SIZE = 1'000'000;
    std::vector<int> vec(SIZE);
    for (size_t i = 0; i < SIZE; ++i) {
        vec[i] = static_cast<int>(i);
    }

    auto result = FindAll(vec, IsEven);

    EXPECT_EQ(result.size(), SIZE / 2);

    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], i * 2);
        EXPECT_TRUE(IsEven(vec[result[i]]));
    }
}

TEST(FindAllTest, CapacityOptimization) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto result = FindAll(vec, IsEven);
    EXPECT_EQ(result.capacity(), result.size());
}

TEST(FindAllTest, ConsecutiveCalls) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto result1 = FindAll(vec, IsEven);
    auto result2 = FindAll(vec, IsEven);
    EXPECT_EQ(result1, result2);

    auto result3 = FindAll(vec, IsPositive);
    EXPECT_EQ(result3.size(), 10);
}

TEST(FindAllTest, ConstCorrectness) {
    const std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = FindAll(vec, IsEven);
    std::vector<size_t> expected = {1, 3, 5, 7, 9};
    EXPECT_EQ(result, expected);
}