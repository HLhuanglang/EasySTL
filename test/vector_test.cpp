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
    EXCEPT_EQ(stdv, nostdv);

    std::vector<int> stdv2(stdv.begin(), stdv.end());
    nostd::vector<int> nostdv2(nostdv.begin(), nostdv.end());
    EXCEPT_EQ(stdv2, nostdv2);

    nostd::vector<int> nostdv3(nostdv2);
    EXCEPT_EQ(nostdv2, nostdv3);

    nostd::vector<int> nostdv4(nostdv3, nostdv3.get_allocator());
    EXCEPT_EQ(nostdv3, nostdv4);
}