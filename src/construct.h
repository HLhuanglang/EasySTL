#ifndef __CONSTRUCT_H
#define __CONSTRUCT_H

#include <new>	//for placement new

template<typename T>
void construct(T *p) {
	new((void *)p) T();
}

template<typename T, typename V>
void construct(T *ptr, const T &val) {
	new((void *)ptr)	T(val);
}

template<typename T, typename...Args>
void construct(T *ptr, Args&&...args) {
	new((void *)ptr) T(std::forward<Args>(args)...);
}

template<typename T>
void _destory(T *ptr, std::true_type) {}

template<typename T>
void _destory(T *ptr, std::false_type) {
	if (ptr != nullptr) {
		ptr->~T();	//编译时多态,类型T必须有析构函数
	}
}

template<typename T>
void destory(T *ptr) {
	_destory(ptr, std::is_trivially_destructible<T>());
}

#endif // !__CONSTRUCT_H
