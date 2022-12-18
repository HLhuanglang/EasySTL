#include "algorithm.h"

#include <vector>
#include <algorithm>
#include <functional>

struct is_3_multiples {
    bool operator()(int i)
    {
        if (0 == i % 3) {
            return true;
        } else {
            return false;
        }
    }
};

bool _any_of_test()
{
    std::vector<int> tmp(10, 2);
    //�ж�tmp�ǲ��Ƕ���2�ı���
    auto ret_stl = stl::all_of(tmp.begin(), tmp.end(), [](int i) {
        return !(i % 2);
    });
    auto ret_std = std::all_of(tmp.begin(), tmp.end(), [](int i) {
        return !(i % 2);
    });

    //�ж�tmp�ǲ��Ƕ���3�ı���
    auto ret_2 = stl::all_of(tmp.begin(), tmp.end(), is_3_multiples());

    return true;
}