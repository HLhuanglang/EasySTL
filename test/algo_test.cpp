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
	//�ж�tmp�ǲ��Ƕ���2�ı���
	auto ret_stl = stl::all_of(tmp.begin(), tmp.end(), [](int i) {
		return !(i % 2);
	});
	auto ret_std = stl::all_of(tmp.begin(), tmp.end(), [](int i) {
		return !(i % 2);
	});

	EXPECT_EQ(ret_stl, ret_std);

	//�ж�tmp�ǲ��Ƕ���3�ı���
	auto ret_2 = stl::all_of(tmp.begin(), tmp.end(), is_3_multiples());
	EXPECT_FALSE(ret_2);
}