#include "algorithm.h"
#include "unit_test.h"

struct is_3_multiples {
	bool operator()(int i) {
		if (0 == i % 3) {
			return true;
		} else {
			return false;
		}
	}
};

TEST(any_of) {
	std::vector<int> tmp(10, 2);
	//判断tmp是不是都是2的倍数
	auto ret_stl = stl::all_of(tmp.begin(), tmp.end(), [](int i) {
		return !(i % 2);
	});
	auto ret_std = stl::all_of(tmp.begin(), tmp.end(), [](int i) {
		return !(i % 2);
	});

	EXPECT_EQ(ret_stl, ret_std);

	//判断tmp是不是都是3的倍数
	auto ret_2 = stl::all_of(tmp.begin(), tmp.end(), is_3_multiples());
	EXPECT_FALSE(ret_2);
}