#ifndef __CONSTRUCT_H
#define __CONSTRUCT_H

#include <type_traits>
#include <utility>

#include "iterator.h"

namespace nostd {

//-=========================
// 构造 placement new
template <typename T>
void construct(T *p) {
    new ((void *)p) T();
}

template <typename T, typename V>
void construct(T *ptr, const T &val) {
    new ((void *)ptr) T(val);
}

template <typename T, typename... Args>
void construct(T *ptr, Args &&...args) {
    new ((void *)ptr) T(std::forward<Args>(args)...);
}
//-=========================

//-=========================
// 析构
template <typename T>
void _destroy(T *ptr, std::true_type) {
    // trivial 无需析构
}

template <typename T>
void _destroy(T *ptr, std::false_type) {
    if (ptr != nullptr) {
        ptr->~T();  // 编译时多态,类型T必须有析构函数
    }
}

template <typename T>
void destroy(T *ptr) {
    _destroy(ptr, std::is_trivially_destructible<T>());
}
//-=========================

//-=========================
// 范围析构
template <typename T>
void __destroy_category(T first, T last, std::false_type) {
    for (; first != last; ++first) {
        destroy(&*first);
    }
}

template <typename T>
void __destroy_category(T first, T last, std::true_type) {
}

template <typename T>
void destroy(T first, T last) {
    __destroy_category(first, last, std::is_trivially_destructible<typename nostd::iterator_traits<T>::value_type>());
}
//-=========================

}  // namespace nostd

#endif  // !__CONSTRUCT_H
