#include <gtest/gtest.h>

#include "algo/algorithm.h"

TEST(AlgorithmTest, TestAllOf) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(nostd::all_of(v.begin(), v.end(), [](int i) {
        return i > 0;
    }));
    EXPECT_FALSE(nostd::all_of(v.begin(), v.end(), [](int i) {
        return i > 1;
    }));
}

TEST(AlgorithmTest, TestAnyOf) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(nostd::any_of(v.begin(), v.end(), [](int i) {
        return i == 3;
    }));
    EXPECT_FALSE(nostd::any_of(v.begin(), v.end(), [](int i) {
        return i == 6;
    }));
}

TEST(AlgorithmTest, TestNoneOf) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(nostd::none_of(v.begin(), v.end(), [](int i) {
        return i == 6;
    }));
    EXPECT_FALSE(nostd::none_of(v.begin(), v.end(), [](int i) {
        return i == 3;
    }));
}

TEST(AlgorithmTest, TestForEach) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    nostd::for_each(v.begin(), v.end(), [](int &i) {
        i *= 2;
    });
    std::vector<int> expected = {2, 4, 6, 8, 10};
    EXPECT_EQ(v, expected);
}