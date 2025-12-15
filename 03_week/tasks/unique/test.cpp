#include <gtest/gtest.h>

#include <vector>
#include <random>
#include <algorithm>

#include "unique.cpp"

TEST(UniqueTest, EmptyVector) {
    std::vector<int> empty;
    auto result = Unique(empty);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.capacity(), result.size());
}

TEST(UniqueTest, SingleElement) {
    std::vector<int> vec = {42};
    auto result = Unique(vec);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 42);
}

TEST(UniqueTest, AllSameElements) {
    std::vector<int> vec = {1, 1, 1, 1, 1};
    auto result = Unique(vec);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 1);
}

TEST(UniqueTest, AlreadyUniqueSorted) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto result = Unique(vec);
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result, vec);
}

TEST(UniqueTest, SimpleDuplicates) {
    std::vector<int> vec = {1, 2, 2, 3, 3, 3};
    auto result = Unique(vec);
    std::vector<int> expected = {1, 2, 3};
    EXPECT_EQ(result, expected);
}

TEST(UniqueTest, MultipleDuplicates) {
    std::vector<int> vec = {1, 1, 2, 2, 2, 3, 3, 4, 5, 5, 5, 5};
    auto result = Unique(vec);
    std::vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(result, expected);
}

TEST(UniqueTest, NegativeNumbers) {
    std::vector<int> vec = {-5, -5, -3, -3, -3, 0, 0, 2, 2, 2, 2};
    auto result = Unique(vec);
    std::vector<int> expected = {-5, -3, 0, 2};
    EXPECT_EQ(result, expected);
}

TEST(UniqueTest, ZeroAndDuplicates) {
    std::vector<int> vec = {0, 0, 0, 0};
    auto result = Unique(vec);
    std::vector<int> expected = {0};
    EXPECT_EQ(result, expected);
}

TEST(UniqueTest, RandomSortedData) {
    std::mt19937 gen(18);
    std::uniform_int_distribution<int> dist(-1000, 1000);

    const size_t N = 1'000'000;
    std::vector<int> vec(N);

    for (size_t i = 0; i < N; ++i) {
        vec[i] = dist(gen);
    }
    std::sort(vec.begin(), vec.end());
    std::vector<int> expected = vec;
    auto last = std::unique(expected.begin(), expected.end());
    expected.erase(last, expected.end());

    auto result = Unique(vec);

    EXPECT_EQ(result.size(), expected.size());
    EXPECT_EQ(result.size(), result.capacity());
    EXPECT_EQ(result, expected);
}

TEST(UniqueTest, ConstCorrectness) {
    const std::vector<int> vec = {1, 2, 2, 3, 3, 3};
    auto result = Unique(vec);
    std::vector<int> expected = {1, 2, 3};
    EXPECT_EQ(result, expected);
}