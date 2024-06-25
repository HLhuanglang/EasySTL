#include <gtest/gtest.h>

#include <vector>

#include "algo/algorithm.h"

TEST(AlgorithmTest, all_of) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(nostd::all_of(v.begin(), v.end(), [](int i) {
        return i > 0;
    }));
    EXPECT_FALSE(nostd::all_of(v.begin(), v.end(), [](int i) {
        return i > 1;
    }));
}

TEST(AlgorithmTest, any_of) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(nostd::any_of(v.begin(), v.end(), [](int i) {
        return i == 3;
    }));
    EXPECT_FALSE(nostd::any_of(v.begin(), v.end(), [](int i) {
        return i == 6;
    }));
}

TEST(AlgorithmTest, none_of) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_TRUE(nostd::none_of(v.begin(), v.end(), [](int i) {
        return i == 6;
    }));
    EXPECT_FALSE(nostd::none_of(v.begin(), v.end(), [](int i) {
        return i == 3;
    }));
}

TEST(AlgorithmTest, for_each) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    nostd::for_each(v.begin(), v.end(), [](int &i) {
        i *= 2;
    });
    std::vector<int> expected = {2, 4, 6, 8, 10};
    EXPECT_EQ(v, expected);
}

TEST(AlgorithmTest, find) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = nostd::find(v.begin(), v.end(), 3);
    if (it != v.end()) {
        EXPECT_EQ(*it, 3);
    } else {
        FAIL();
    }

    class AT {
     public:
        AT(int i) : m_i(i) {}
        bool operator==(const AT &rhs) const {
            return m_i == rhs.m_i;
        }

     private:
        int m_i;
    };
    std::vector<AT> v2 = {AT(1), AT(2), AT(3), AT(4), AT(5)};
    auto it2 = nostd::find(v2.begin(), v2.end(), AT(3));
    if (it2 != v2.end()) {
        EXPECT_EQ(*it2 == AT(3), true);
    } else {
        FAIL();
    }
}