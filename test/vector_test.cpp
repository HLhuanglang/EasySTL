#include "utest.h"

#include "vector.h"
#include <vector>

TEST(vector) {
    nostd::vector<int> v;
    EXCEPT_EQ(v.size(), 0);

    nostd::vector<int> v1(10);
    EXCEPT_EQ(v1.size(), 10);

    std::vector<int> stdv(10, 1);
    nostd::vector<int> nostdv(10, 1);
    EXCEPT_EQ(stdv, nostdv)
}