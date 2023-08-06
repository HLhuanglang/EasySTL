#ifndef __ALLOCATOR_H
#define __ALLOCATOR_H

#include <cstddef> //for ptrdiff_t
#include <iterator>

#include <type_traits>

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
    static T *allocate();
    static T *allocate(size_type n);

    static void deallocate(T *ptr);
    static void deallocate(T *ptr, size_type n);

    static void construct(T *ptr);
    static void construct(T *ptr, const T &value);
    static void construct(T *ptr, T &&value);
    template <class... Args>
    static void construct(T *ptr, Args &&...args);

    static void destroy(T *ptr);
    static void destroy(T *first, T *last);
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
    // new ((void *)ptr) T();
    nostd::construct(ptr);
}

template <class T>
void allocator<T>::construct(T *ptr, const T &value) {
    // new ((void *)ptr) T(value);
    nostd::construct(ptr, value);
}

template <class T>
void allocator<T>::construct(T *ptr, T &&value) {
    // new ((void *)ptr) T(std::move(value));
    nostd::construct(ptr, std::move(value));
}

template <class T>
template <class... Args>
void allocator<T>::construct(T *ptr, Args &&...args) {
    //::new ((void *)ptr) T(std::forward<Args>(args)...);
    nostd::construct(ptr, std::forward<Args>(args)...);
}

template <class T>
void allocator<T>::destroy(T *ptr) {
    nostd::destroy(ptr);
}

template <class T>
void allocator<T>::destroy(T *first, T *last) {
    nostd::destroy(first, last); // 如果destory不封装一层,而是直接在该文件内实现,就会出现stl::allocator<T>::destory(&*ptr) 这种场景,模板参数会其冲突
}
} // namespace nostd

#endif // !__ALLOCATOR_H
