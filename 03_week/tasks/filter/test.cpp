#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>
#include <vector>

#include "filter.cpp"


bool IsEven(int x) {
    return x % 2 == 0;
}

bool IsOdd(int x) {
    return x % 2;
}

bool IsPositive(int x) {
    return x > 0;
}

bool AlwaysFalse(int) {
    return false;
}

TEST(FilterTest, EmptyVector) {
    std::vector<int> empty_vec;
    Filter(empty_vec, IsEven);
    EXPECT_TRUE(empty_vec.empty());
}

TEST(FilterTest, AllElementsFalse) {
    std::vector<int> vec = {1, -3, 5, -7, 9};
    Filter(vec, IsEven);
    EXPECT_TRUE(vec.empty());
}

TEST(FilterTest, NullptrPredicate) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    size_t expected_size = vec.size();
    EXPECT_NO_THROW(Filter(vec, nullptr));
    EXPECT_EQ(vec.size(), expected_size);
}

TEST(FilterTest, SingleElementTrue) {
    std::vector<int> vec = {18};
    Filter(vec, IsEven);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 18);
}

TEST(FilterTest, SingleElementFalse) {
    std::vector<int> vec = {17};
    Filter(vec, IsEven);
    EXPECT_TRUE(vec.empty());
}

TEST(FilterTest, AllElementsPass) {
    std::vector<int> vec = {2, 4, 6, 8, 10};
    Filter(vec, IsEven);
    std::vector<int> expected = {2, 4, 6, 8, 10};
    EXPECT_EQ(vec.size(), expected.size());
    EXPECT_EQ(vec, expected);
}

TEST(FilterTest, MixedElements) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Filter(vec, IsEven);
    std::vector<int> expected = {2, 4, 6, 8, 10};
    EXPECT_EQ(vec.size(), expected.size());
    EXPECT_EQ(vec, expected);
}

TEST(FilterTest, NotSortedElements) {
    std::vector<int> vec = {10, 2, 3, 4, 5, 7, 6, 8, 9, 1};
    Filter(vec, IsEven);
    std::vector<int> expected = {10, 2, 4, 6, 8};
    EXPECT_EQ(vec, expected);
}

TEST(FilterTest, NotRealocate) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto capacity = vec.capacity();
    auto ptr_before = vec.data();
    Filter(vec, IsEven);
    EXPECT_EQ(vec.data(), ptr_before);
    EXPECT_EQ(vec.capacity(), capacity);
}

TEST(FilterTest, AllFalsePredicate) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Filter(vec, AlwaysFalse);
    EXPECT_TRUE(vec.empty());
}

TEST(FilterTest, LargeVector) {
    const size_t SIZE = 1'000'000;
    std::vector<int> vec(SIZE);
    for (size_t i = 0; i < SIZE; ++i) {
        vec[i] = static_cast<int>(i);
    }

    Filter(vec, IsEven);

    EXPECT_EQ(vec.size(), SIZE / 2);

    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], static_cast<int>(i * 2));
        EXPECT_TRUE(IsEven(vec[i]));
    }
}

TEST(FilterTest, ConsecutiveCalls) {
    std::vector<int> vec = {1, -2, 3, 4, 5, 6, 7, -8, 9, 10};

    Filter(vec, IsEven);
    Filter(vec, IsEven);
    std::vector<int> expected = {-2, 4, 6, -8, 10};
    EXPECT_EQ(vec, expected);

    Filter(vec, IsPositive);
    expected = {4, 6, 10};
    EXPECT_EQ(vec, expected);
}

TEST(FilterTest, BigRandomDataMultipleSeeds) {
    const size_t NUM_TESTS = 10;
    const size_t VECTOR_SIZE = 1'000'000;
    const int MIN_VALUE = -1'000'000;
    const int MAX_VALUE = 1'000'000;

    std::random_device rd;
    std::mt19937 seed_gen(rd());
    std::uniform_int_distribution<unsigned> seed_dist(0, 100000);

    double erase_duration = 0;
    double filter_duration = 0;
    for (size_t test_idx = 0; test_idx < NUM_TESTS; ++test_idx) {
        unsigned int seed = seed_dist(seed_gen);
        std::mt19937 gen(seed);
        std::uniform_int_distribution<int> value_dist(MIN_VALUE, MAX_VALUE);

        std::vector<int> test(VECTOR_SIZE);
        for (size_t i = 0; i < VECTOR_SIZE; ++i) {
            test[i] = value_dist(gen);
        }

        auto expected = test;
        auto start = std::chrono::high_resolution_clock::now();
        std::erase_if(expected, IsOdd);
        auto end = std::chrono::high_resolution_clock::now();
        erase_duration += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        Filter(test, IsEven);
        end = std::chrono::high_resolution_clock::now();
        filter_duration += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        ASSERT_EQ(test.size(), expected.size())
            << "Test #" << test_idx << " with seed " << seed
            << ": size mismatch";
        EXPECT_EQ(test, expected)
            << "Test #" << test_idx << " with seed " << seed
            << ": content mismatch";
    }

    EXPECT_LE(filter_duration, 1.2 * erase_duration)
        << "Function too slow: "
        <<"filter_duration = " << filter_duration << " ms, erase_duration = " << erase_duration << " ms\n";
}