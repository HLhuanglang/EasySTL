/*
* https://github.com/llvm/llvm-project/blob/main/libcxx/include/vector
* https://cplusplus.com/reference/vector/vector/
*/
#ifndef __VECTOR_H
#define __VECTOR_H

#include "allocator.h"

#include <memory> //allocator_traits
#include <iterator>

namespace stl {
template <typename T>
class vector {
public:
    using value_type             = T;
    using allocator_type         = stl::allocator<T>;
    using reference              = value_type &;
    using const_reference        = const value_type &;
    using size_type              = typename std::allocator_traits<allocator_type>::size_type;
    using difference_type        = typename std::allocator_traits<allocator_type>::difference_type;
    using pointer                = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer          = typename std::allocator_traits<allocator_type>::const_pointer;
    using iterator               = value_type *;
    using const_iterator         = const value_type *;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static_assert((std::is_same<typename allocator_type::value_type, value_type>::value), "Allocator::value_type must be same type as value_type");

private:
    iterator begin_;
    iterator end_;
    iterator end_of_storage_;

public:
    vector();
    vector(size_type n, const value_type val);

    /*
		如果不加任何判断,当T是int类型时候：
		stl::vector<int> v(10,1);
		会走到这个逻辑里面来
		*/
    template <class iter_t, typename std::enable_if<!std::is_integral<iter_t>::value>::type>
    vector(iter_t first, iter_t last);

    ~vector();
};

template <typename T>
vector<T>::vector()
{
    begin_ = end_   = allocator_type::allocate(16);
    end_of_storage_ = begin_ + 16;
}

template <typename T>
vector<T>::vector(size_type n, const value_type val)
{
    //1,申请空间
    begin_ = end_   = allocator_type::allocate(n);
    end_of_storage_ = begin_ + n;
    //2,根据容器元素类型进行创建
    //--pod类型可以直接通过指针指向赋值
    //--类类型需要调用构造函数
    if (std::is_pod<T>::value) {
        iterator tmp = begin_;
        for (int i = 0; i < n; i++) {
            *tmp = val;
            tmp++;
        }
        end_ = tmp;
    } else {
        iterator tmp = begin_;
        for (; n > 0; --n, ++tmp) {
            allocator_type::construct(&*tmp, val);
        }
        end_ = tmp;
    }
}

template <typename T>
template <class iter_t, typename std::enable_if<!std::is_integral<iter_t>::value>::type>
vector<T>::vector(iter_t first, iter_t last)
{
}

template <typename T>
vector<T>::~vector()
{
    allocator_type::destroy(begin_, end_);
    allocator_type::deallocate(begin_, end_of_storage_ - begin_);
    begin_ = end_ = end_of_storage_ = nullptr;
}
} // namespace stl
#endif // !__VECTOR_H
