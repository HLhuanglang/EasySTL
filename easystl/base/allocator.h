#ifndef __ALLOCATOR_H
#define __ALLOCATOR_H

#include <cstddef>  //for ptrdiff_t

#include "construct.h"

namespace nostd {
template <class T>
class allocator {
 public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

 public:
    // 使用operator new来申请内存
    static T *allocate();             //-申请1个元素大小的空间
    static T *allocate(size_type n);  //-申请N个元素大小的空间

    // 使用placement new，在指定地址调用T的构造函数
    static void construct(T *ptr);
    static void construct(T *ptr, const T &value);
    static void construct(T *ptr, T &&value);
    template <class... Args>
    static void construct(T *ptr, Args &&...args);

    // 显式调用T的析构函数
    static void destroy(T *ptr);
    static void destroy(T *first, T *last);

    // 使用operator delete来申请内存
    static void deallocate(T *ptr);
    static void deallocate(T *ptr, size_type n);
};

template <class T>
T *allocator<T>::allocate() {
    return static_cast<T *>(::operator new(sizeof(T)));
}

template <class T>
T *allocator<T>::allocate(size_type n) {
    if (n == 0) {
        return nullptr;
    }
    return static_cast<T *>(::operator new(n * sizeof(T)));
}

template <class T>
void allocator<T>::deallocate(T *ptr) {
    if (ptr == nullptr) {
        return;
    }
    ::operator delete(ptr);
}

template <class T>
void allocator<T>::deallocate(T *ptr, size_type /*size*/) {
    if (ptr == nullptr) {
        return;
    }
    ::operator delete(ptr);
}

template <class T>
void allocator<T>::construct(T *ptr) {
    nostd::construct(ptr);
}

template <class T>
void allocator<T>::construct(T *ptr, const T &value) {
    nostd::construct(ptr, value);
}

template <class T>
void allocator<T>::construct(T *ptr, T &&value) {
    nostd::construct(ptr, std::move(value));
}

template <class T>
template <class... Args>
void allocator<T>::construct(T *ptr, Args &&...args) {
    nostd::construct(ptr, std::forward<Args>(args)...);
}

template <class T>
void allocator<T>::destroy(T *ptr) {
    nostd::destroy(ptr);
}

template <class T>
void allocator<T>::destroy(T *first, T *last) {
    // 此时first的类型是T*, 当调用nostd::destroy时,nostd::destroy的模板类型就变成T*了
    nostd::destroy(first, last);
}
}  // namespace nostd

#endif  // !__ALLOCATOR_H
