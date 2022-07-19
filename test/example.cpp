#include <iostream>
#include <vector>
#include <algorithm>

using test_t = struct _test {
	int idx = 0;
	void operator()(const std::string &i) {
		std::cout << i << std::endl;
	}
};

void test_for_each() {
	std::vector<std::string> tmp(10, "abc");
	std::string_view sv("xxx");
	std::for_each(tmp.begin(), tmp.end(), [&](std::string &str) {
		str = sv;
	});

	std::for_each(tmp.begin(), tmp.end(), test_t());
}

struct is_3_multiples {
	bool operator()(int i) {
		if (0 != i % 3) {
			return false;
		} else {
			return true;
		}
	}
};

void test_all_of() {
	std::vector<int> tmp(10, 2);
	auto ret_1 = std::all_of(tmp.begin(), tmp.end(), [](int i) {
		return !(i % 2);
	});
	auto ret_2 = std::all_of(tmp.begin(), tmp.end(), is_3_multiples());
}

class holo {
public:
	holo(int age, std::string name) :age_(age), name_(name) {}
	std::string get_name() {
		return name_;
	}

	std::string get_name() const {
		return name_;
	}

	int get_age() {
		return age_;
	}
	int get_age() const {
		return age_;
	}
public:
	bool operator==(int age) {	//找到年纪比age小的人。
		if (this->age_ < age) {
			return true;
		} else {
			return false;
		}
	}

	bool operator==(const holo &rhs) {
		if (age_ < rhs.get_age() && name_ == rhs.get_name()) {
		}
		return false;
	}

private:
	int age_ = 0;
	std::string name_;
};

void test_find() {
	std::vector<holo> tmp(10, { 24,"holo_wo" });
	auto pos = std::find(tmp.begin(), tmp.end(), 25);
	if (pos != tmp.end()) {
		std::cout << (*pos).get_name() << std::endl;
	} else {
		std::cout << "don't find age less than 25 in tmp" << std::endl;
	}
}

struct is_4_multipies {
	bool operator()(int i) {
		return !(i % 4);
	}
};

void test_find_if() {
	std::vector<int> tmp(10, 1);
	auto pos = std::find_if(tmp.begin(), tmp.end(), [](int i) {
		return !(i % 2);
	});
	if (pos != tmp.end()) {
		std::cout << *pos << std::endl;
	} else {
		std::cout << "don't find!" << std::endl;
	}

	pos = std::find_if(tmp.begin(), tmp.end(), is_4_multipies());
	if (pos != tmp.end()) {
		std::cout << *pos << std::endl;
	} else {
		std::cout << "don't find!" << std::endl;
	}
}

void test_find_end() {
	std::vector<int> v1{ 1,2,3,4,5,5,4,3,2,3,4,9,8,7 };
	std::vector<int> v2{ 9,8,7 };
	auto pos = std::find_end(v1.begin(), v1.end(), v2.begin(), v2.end());
	if (pos != v1.end()) {
		std::cout << "find {9,8,7} at idx=" << std::distance(v1.begin(), pos);
	} else {
		std::cout << "don't find" << std::endl;
	}
}