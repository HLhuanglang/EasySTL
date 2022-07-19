# 算法合集

STL中提供了七十多种算法，加上重载版本，大约有100多个不同的函数模板。因为不同的算法需要的迭代器能力不一样，下图是迭代器具备的能力。

![image-20220711235435392](https://hl1998-1255562705.cos.ap-shanghai.myqcloud.com/Img/image-20220711235435392.png)

## 不修改序列的操作

### all_of

算法功能：如果容器内所有元素都满足谓词条件，则返回true，当有一个不满足就返回false，后面的就判断了

算法声明：

```c++
template <class InputIterator, class UnaryPredicate>
  bool all_of (InputIterator first, InputIterator last, UnaryPredicate pred);
```

算法实现：

```c++
template <class InputIterator, class UnaryPredicate>
  bool all_of (InputIterator first, InputIterator last, UnaryPredicate pred){
  
  while(first != last){
  	if(!pred(*first)) return false;
  	++first;
  }
  return true;
}
```

算法使用：

```c++
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

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
	//判断tmp是不是都是2的倍数
	auto ret_1 = std::all_of(tmp.begin(), tmp.end(), [](int i) {
		return !(i % 2);
	});
	//判断tmp是不是都是3的倍数
	auto ret_2 = std::all_of(tmp.begin(), tmp.end(), is_3_multiples());
}
```

### any_of

如果容器内有一个元素满足谓词条件，就返回true。当谓词判断为false时会一直执行，知道容器里面元素遍历完。

### none_of

return ture if pred return false for all the elements in the range[first, last).

### for_each

算法功能：对容器内所有元素执行fn操作，完成后返回fn函数对象，使用了std::move。

算法声明：

```c++
template <class InputIterator, class Function>
   Function for_each (InputIterator first, InputIterator last, Function fn);
```

算法实现：

```c++
template<class InputIterator, class Function>
  Function for_each(InputIterator first, InputIterator last, Function fn)
{
  while (first!=last) {
    fn (*first);	//只要执行即可,不在乎返回值、成功与否..
    ++first;
  }
  return fn;      // or, since C++11: return move(fn);
}
```

算法使用：

```c++
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using test_t = struct _test {
	int idx = 0;
	void operator()(std::string i) {
		std::cout << i << std::endl;
	}
};

int main() {
	std::vector<std::string> tmp(10, "abc");
	std::for_each(tmp.begin(), tmp.end(), [](std::string &str) {
		str = "xxx";
	});

	std::for_each(tmp.begin(), tmp.end(), test_t());
}
```

### find

算法功能：找到容器中值为val的元素，返回迭代器。

算法声明：

```c++
template <class InputIterator, class T>
   InputIterator find (InputIterator first, InputIterator last, const T& val);
```

算法实现：

```c++
template <class InputIterator, class T>
   InputIterator find (InputIterator first, InputIterator last, const T& val){
    while(fisrt!=last){
        if(*first ==val) return first;	//自定义类时,就得重载==操作符。
        ++first;
    }
    return last;
}
```

算法使用：

```c++
class holo {
public:
	holo(int age, std::string name) :age_(age), name_(name) {}
	std::string get_name() {
		return name_;
	}
public:
	bool operator==(int age) {	//找到年纪比age小的人。
		if (this->age_ < age) {
			return true;
		} else {
			return false;
		}
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
```

### find_if

算法功能：找到容器中满足fn函数的第一个元素

算法声明：

```c++
template <class InputIterator, class UnaryPredicate>
   InputIterator find_if (InputIterator first, InputIterator last, UnaryPredicate pred);
```

算法实现：

```c++
template <class InputIterator, class UnaryPredicate>
   InputIterator find_if (InputIterator first, InputIterator last, UnaryPredicate pred){
   while(first != last){
       if(pred(*first)) return first;	//自定义类型时，只需要重载()操作符即可
       ++first;
   }
    return last;
}
```

算法使用：

```c++
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
```

### find_if_not

和find_if功能相反，找到容器中使得fn为false的元素。

### find_end

算法功能：相当于**找子集**的功能，在容器1中找到一段匹配容器2的元素，返回对应的位置

算法声明：

```c++
template <class ForwardIterator1, class ForwardIterator2>
   ForwardIterator1 find_end (ForwardIterator1 first1, ForwardIterator1 last1,
                              ForwardIterator2 first2, ForwardIterator2 last2);

template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
   ForwardIterator1 find_end (ForwardIterator1 first1, ForwardIterator1 last1,
                              ForwardIterator2 first2, ForwardIterator2 last2,
                              BinaryPredicate pred);
```

算法实现：

```c++
template<class ForwardIterator1, class ForwardIterator2>
  ForwardIterator1 find_end (ForwardIterator1 first1, ForwardIterator1 last1,
                             ForwardIterator2 first2, ForwardIterator2 last2)
{
  if (first2==last2) return last1;  // specified in C++11

  ForwardIterator1 ret = last1;

  while (first1!=last1)
  {
    ForwardIterator1 it1 = first1;
    ForwardIterator2 it2 = first2;
    while (*it1==*it2) {    // or: while (pred(*it1,*it2)) for version (2)
        ++it1; ++it2;
        if (it2==last2) { ret=first1; break; }
        if (it1==last1) return ret;
    }
    ++first1;
  }
  return ret;
}
```

算法使用：

```c++
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
```

### find_first_of

adjacent_find

count

count_if

mismatch

equal

is_permutation

search

serch_n