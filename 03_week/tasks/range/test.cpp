#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

#include "range.cpp"

TEST(RangeTest, SimpleIncreasing) {
    EXPECT_EQ(Range(1, 6, 1), std::vector<int>({1, 2, 3, 4, 5}));
    EXPECT_EQ(Range(1, 7, 2), std::vector<int>({1, 3, 5}));
    EXPECT_EQ(Range(-20, 10, 10), std::vector<int>({-20, -10, 0}));
}

TEST(RangeTest, SimpleDecreasing) {
    EXPECT_EQ(Range(6, 1, -1), std::vector<int>({6, 5, 4, 3, 2}));
    EXPECT_EQ(Range(7, 1, -2), std::vector<int>({7, 5, 3}));
    EXPECT_EQ(Range(20, 18, -3), std::vector<int>({20}));
    EXPECT_EQ(Range(-20, -24, -3), std::vector<int>({-20, -23}));
}

TEST(RangeTest, EmptyRanges) {
    EXPECT_TRUE(Range(0, 0, 2).empty());
    EXPECT_TRUE(Range(7, 7, 1).empty());
    EXPECT_TRUE(Range(20, 20, -2).empty());
    EXPECT_TRUE(Range(-5, -5, -2).empty());
    EXPECT_TRUE(Range(-7, -7, 1).empty());
}

TEST(RangeTest, InvalidParameters) {
    EXPECT_TRUE(Range(1, 7, -1).empty());
    EXPECT_TRUE(Range(3, 7, 0).empty());
    EXPECT_TRUE(Range(2, -2, 2).empty());
    EXPECT_TRUE(Range(3, -7, 0).empty());
    EXPECT_TRUE(Range(-2, -3, 2).empty());
}

TEST(RangeTest, SingleElement) {
    EXPECT_EQ(Range(7, 8, 1), std::vector<int>({7}));
    EXPECT_EQ(Range(7, 8, 2), std::vector<int>({7}));
    EXPECT_EQ(Range(7, 8, 100), std::vector<int>({7}));

    EXPECT_EQ(Range(5, 4, -1), std::vector<int>({5}));
    EXPECT_EQ(Range(5, 4, -2), std::vector<int>({5}));
    EXPECT_EQ(Range(5, 4, -100), std::vector<int>({5}));

    EXPECT_EQ(Range(-7, 8, 100), std::vector<int>({-7}));
    EXPECT_EQ(Range(-7, -8, -100), std::vector<int>({-7}));
}

TEST(RangeTest, NegativeNumbers) {
    EXPECT_EQ(Range(-5, 0, 1), std::vector<int>({-5, -4, -3, -2, -1}));
    EXPECT_EQ(Range(-5, 5, 2), std::vector<int>({-5, -3, -1, 1, 3}));
    EXPECT_EQ(Range(0, -5, -1), std::vector<int>({0, -1, -2, -3, -4}));
    EXPECT_EQ(Range(0, -10, -3), std::vector<int>({0, -3, -6, -9}));
}

TEST(RangeTest, LargeStep) {
    EXPECT_EQ(Range(0, 100, 33), std::vector<int>({0, 33, 66, 99}));
    EXPECT_EQ(Range(100, 0, -33), std::vector<int>({100, 67, 34, 1}));
}

TEST(RangeTest, DefaultStep) {
    EXPECT_EQ(Range(0, 5), std::vector<int>({0, 1, 2, 3, 4}));
    EXPECT_EQ(Range(-2, 3), std::vector<int>({-2, -1, 0, 1, 2}));
    EXPECT_TRUE(Range(5, 5).empty());
    EXPECT_TRUE(Range(5, 3).empty());
}

TEST(RangeTest, CapacityMatchesSize) {
    auto result = Range(0, 100, 3);
    EXPECT_EQ(result.capacity(), result.size());
}

TEST(RangePerformanceTest, LargeRange) {
    const int from = -1'000'000;
    const int to = 1'000'000;

    auto result_asc = Range(from, to);
    EXPECT_EQ(result_asc.size(), to - from);
    EXPECT_EQ(result_asc.front(), from);
    EXPECT_EQ(result_asc.back(), to - 1);

    for (size_t i = 0; i < result_asc.size(); ++i) {
        EXPECT_EQ(result_asc[i], from + static_cast<int>(i));
    }

    auto result_desc = Range(to - 1, from - 1, -1);
    EXPECT_EQ(result_desc.size(), to - from);
    EXPECT_EQ(result_desc.front(), to - 1);
    EXPECT_EQ(result_desc.back(), from);

    for (size_t i = 0; i < result_asc.size(); ++i) {
        EXPECT_EQ(result_desc[i], to - 1 - static_cast<int>(i));
    }

    EXPECT_GE(result_asc.capacity(), result_asc.size());
    EXPECT_GE(result_desc.capacity(), result_desc.size());
}