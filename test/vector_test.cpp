#include "container/vector.h"

#include <gtest/gtest.h>

#include <vector>

using namespace nostd;

TEST(VectorTest, DefaultConstructor) {
    nostd::vector<int> v;
    EXPECT_EQ(v.size(), 0);

    nostd::vector<int> v1(10);
    EXPECT_EQ(v1.size(), 10);

    std::vector<int> stdv(10, 1);
    nostd::vector<int> nostdv(10, 1);
    EXPECT_TRUE(nostdv == stdv);

    std::vector<int> stdv2(stdv.begin(), stdv.end());
    nostd::vector<int> nostdv2(nostdv.begin(), nostdv.end());
    EXPECT_TRUE(nostdv2 == stdv2);

    nostd::vector<int> nostdv3(nostdv2);
    EXPECT_TRUE(nostdv3 == nostdv2);

    nostd::vector<int> nostdv4(nostdv3, nostdv3.get_allocator());
    EXPECT_EQ(nostdv4, nostdv3);
}