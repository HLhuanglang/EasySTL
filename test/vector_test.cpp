#include "vector.h"

class test {
public:
    explicit test(int a)
        : t_(a)
    {}
    virtual void func() {}
    ~test() {}

private:
    int t_;
};

void _vector_test()
{
    stl::vector<test> v1;
    stl::vector<test> v2(10, test(1));
    stl::vector<int> v3;
    stl::vector<int> v4(10, 1);
}