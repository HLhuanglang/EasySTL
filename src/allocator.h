#ifndef __ALLOCATOR_H
#define __ALLOCATOR_H

#include "construct.h"

#include <cstddef> //for ptrdiff_t
#include <type_traits>
#include <iterator>

namespace stl {
template <class T>
class allocator {
public:
    typedef T value_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

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
T *allocator<T>::allocate()
{
    return static_cast<T *>(::operator new(sizeof(T)));
}

template <class T>
T *allocator<T>::allocate(size_type n)
{
    if (n == 0)
        return nullptr;
    return static_cast<T *>(::operator new(n * sizeof(T)));
}

template <class T>
void allocator<T>::deallocate(T *ptr)
{
    if (ptr == nullptr)
        return;
    ::operator delete(ptr);
}

template <class T>
void allocator<T>::deallocate(T *ptr, size_type /*size*/)
{
    if (ptr == nullptr)
        return;
    ::operator delete(ptr);
}

template <class T>
void allocator<T>::construct(T *ptr)
{
    new ((void *)ptr) T();
    //stl::construct(ptr);
}

template <class T>
void allocator<T>::construct(T *ptr, const T &value)
{
    new ((void *)ptr) T(value);
    //stl::construct(ptr,value);
}

template <class T>
void allocator<T>::construct(T *ptr, T &&value)
{
    new ((void *)ptr) T(std::move(value));
    //stl::construct(ptr,std::move(value));
}

template <class T>
template <class... Args>
void allocator<T>::construct(T *ptr, Args &&...args)
{
    ::new ((void *)ptr) T(std::forward<Args>(args)...);
    //stl::construct(ptr,std::forward<Args>(args)...);
}

template <class T>
void allocator<T>::destroy(T *ptr)
{
    stl::destroy(ptr);
}

template <class T>
void allocator<T>::destroy(T *first, T *last)
{
    stl::destroy(first, last); //如果destory不封装一层,而是直接在该文件内实现,就会出现stl::allocator<T>::destory(&*ptr) 这种场景,模板参数会其冲突.
}
} // namespace stl

#endif // !__ALLOCATOR_H
