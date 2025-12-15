#include <gtest/gtest.h>

#include <cmath>
#include <vector>

#include "data_stats.cpp"

constexpr double EPSILON = 1e-6;

TEST(DataStatsTest, EmptyVector) {
    std::vector<int> empty_vec;
    DataStats stats = CalculateDataStats(empty_vec);

    EXPECT_DOUBLE_EQ(stats.avg, 0.0);
    EXPECT_DOUBLE_EQ(stats.sd, 0.0);
}

TEST(DataStatsTest, SingleElement) {
    std::vector<int> vec = {42};
    DataStats stats = CalculateDataStats(vec);

    EXPECT_DOUBLE_EQ(stats.avg, 42.0);
    EXPECT_DOUBLE_EQ(stats.sd, 0.0);
}

TEST(DataStatsTest, TwoElements) {
    std::vector<int> vec = {10, 20};
    DataStats stats = CalculateDataStats(vec);

    EXPECT_DOUBLE_EQ(stats.avg, 15.0);
    EXPECT_DOUBLE_EQ(stats.sd, 5.0);
}

TEST(DataStatsTest, AllSameElements) {
    std::vector<int> vec = {7, 7, 7, 7, 7};
    DataStats stats = CalculateDataStats(vec);

    EXPECT_DOUBLE_EQ(stats.avg, 7.0);
    EXPECT_DOUBLE_EQ(stats.sd, 0.0);
}

TEST(DataStatsTest, PositiveNumbers) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    DataStats stats = CalculateDataStats(vec);

    EXPECT_DOUBLE_EQ(stats.avg, 3.0);
    EXPECT_NEAR(stats.sd, std::sqrt(2.0), EPSILON);
}

TEST(DataStatsTest, NegativeNumbers) {
    std::vector<int> vec = {-5, -4, -3, -2, -1};
    DataStats stats = CalculateDataStats(vec);

    EXPECT_DOUBLE_EQ(stats.avg, -3.0);
    EXPECT_NEAR(stats.sd, std::sqrt(2.0), EPSILON);
}

TEST(DataStatsTest, MixedPositiveNegative) {
    std::vector<int> vec = {-2, -1, 0, 1, 2};
    DataStats stats = CalculateDataStats(vec);

    EXPECT_DOUBLE_EQ(stats.avg, 0.0);
    EXPECT_NEAR(stats.sd, std::sqrt(2.0), EPSILON);
}

TEST(DataStatsTest, ConstCorrectness) {
    const std::vector<int> vec = {-2, -1, 0, 1, 2};
    DataStats stats = CalculateDataStats(vec);

    EXPECT_DOUBLE_EQ(stats.avg, 0.0);
    EXPECT_NEAR(stats.sd, std::sqrt(2.0), EPSILON);
}

TEST(DataStatsTest, LargeNumbers) {
    std::vector<int> vec = {50000, 60000, 70000};
    DataStats stats = CalculateDataStats(vec);

    EXPECT_DOUBLE_EQ(stats.avg, 60000.0);
    EXPECT_NEAR(stats.sd, std::sqrt(200000000.0 / 3.0), EPSILON);
}