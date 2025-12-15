#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>
#include <utility>

#include "minmax.cpp"


TEST(MinMaxTest, EmptyVector) {
    std::vector<int> empty_vec;
    auto [min_it, max_it] = MinMax(empty_vec);

    EXPECT_EQ(min_it, empty_vec.end());
    EXPECT_EQ(max_it, empty_vec.end());
}

TEST(MinMaxTest, SingleElement) {
    std::vector<int> vec = {42};
    auto [min_it, max_it] = MinMax(vec);

    EXPECT_EQ(min_it, vec.begin());
    EXPECT_EQ(max_it, vec.begin());
    EXPECT_EQ(*min_it, 42);
    EXPECT_EQ(*max_it, 42);
}

TEST(MinMaxTest, AllEqualElements) {
    std::vector<int> vec = {5, 5, 5, 5, 5};
    auto [min_it, max_it] = MinMax(vec);

    EXPECT_NE(min_it, vec.begin());
    EXPECT_NE(max_it, vec.end() - 1);
    EXPECT_EQ(*min_it, 5);
    EXPECT_EQ(*max_it, 5);
}

TEST(MinMaxTest, BeginMinEndMax) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto [min_it, max_it] = MinMax(vec);

    EXPECT_EQ(min_it, vec.begin());
    EXPECT_EQ(max_it, vec.end() - 1);
    EXPECT_EQ(*min_it, 1);
    EXPECT_EQ(*max_it, 5);

}

TEST(MinMaxTest, BeginMaxEndMin) {
    std::vector<int> vec = {5, 4, 3, 2, 1};
    auto [min_it, max_it] = MinMax(vec);

    EXPECT_EQ(min_it, vec.end() - 1);
    EXPECT_EQ(max_it, vec.begin());
    EXPECT_EQ(*min_it, 1);
    EXPECT_EQ(*max_it, 5);
}

TEST(MinMaxTest, MinAndMaxInMiddle) {
    std::vector<int> vec = {5, 3, 2, 1, 5, 4, 2, 1};
    auto [min_it, max_it] = MinMax(vec);

    EXPECT_EQ(min_it, vec.begin() + 3);
    EXPECT_EQ(max_it, vec.begin() + 4);
    EXPECT_EQ(*min_it, 1);
    EXPECT_EQ(*max_it, 5);
}

TEST(MinMaxTest, NegativeNumbers) {
    std::vector<int> vec = {-5, -10, -3, -1, -8};
    auto [min_it, max_it] = MinMax(vec);

    EXPECT_EQ(min_it, vec.begin() + 1);
    EXPECT_EQ(max_it, vec.begin() + 3);
    EXPECT_EQ(*min_it, -10);
    EXPECT_EQ(*max_it, -1);
}

TEST(MinMaxTest, MixedPositiveNegative) {
    std::vector<int> vec = {-5, 10, -3, 0, 8, -20};
    auto [min_it, max_it] = MinMax(vec);

    EXPECT_EQ(min_it, vec.end() - 1);
    EXPECT_EQ(max_it, vec.begin() + 1);
    EXPECT_EQ(*min_it, -20);
    EXPECT_EQ(*max_it, 10);
}

TEST(MinMaxTest, LargeVector) {
    std::vector<int> vec(1000);

    int value = -vec.size() / 2;
    for (size_t i = 0; i < vec.size(); ++i, ++value) {
        vec[i] = value;
    }

    vec[500] = -vec.size();
    vec[750] = vec.size();

    auto [min_it, max_it] = MinMax(vec);

    EXPECT_EQ(min_it, vec.begin() + 500);
    EXPECT_EQ(max_it, vec.begin() + 750);
    EXPECT_EQ(*min_it, -vec.size());
    EXPECT_EQ(*max_it, vec.size());
}

TEST(MinMaxTest, ConstCorrectness) {
    const std::vector<int> vec = {1, 9};
    auto [min_it, max_it] = MinMax(vec);

    EXPECT_EQ(*min_it, 1);
    EXPECT_EQ(*max_it, 9);
}

TEST(MinMaxTest, PerformanceCheck) {
    const double THRESHOLD = 0.3;
    const size_t SIZE = 1'000'000u;
    std::vector<int> large_vec(SIZE);
    std::iota(large_vec.begin(), large_vec.end(), 0);
    std::shuffle(large_vec.begin(), large_vec.end(), std::mt19937{18});

    auto start = std::chrono::high_resolution_clock::now();
    auto [min_it, max_it] = MinMax(large_vec);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    start = std::chrono::high_resolution_clock::now();
    auto [min_it_std, max_it_std] = std::minmax_element(large_vec.begin(), large_vec.end());
    end = std::chrono::high_resolution_clock::now();
    auto duration_std = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    EXPECT_LE(std::abs(duration_std.count() - duration.count()) * 1.0, duration_std.count() * THRESHOLD) <<
        "Your function is very slowly";
    EXPECT_EQ(*min_it, *min_it_std);
    EXPECT_EQ(*max_it, *max_it_std);
}