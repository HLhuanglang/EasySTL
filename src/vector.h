/*
* https://github.com/llvm/llvm-project/blob/main/libcxx/include/vector
* https://cplusplus.com/reference/vector/vector/
*/
#ifndef __VECTOR_H
#define __VECTOR_H

#include "allocator.h"
#include "algorithm.h"
#include "iterator.h"

#include <algorithm>
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
    using reverse_iterator       = stl::reverse_iterator<iterator>;
    using const_reverse_iterator = stl::reverse_iterator<const_iterator>;

    static_assert((std::is_same<typename allocator_type::value_type, value_type>::value), "Allocator::value_type must be same type as value_type");

private:
    iterator begin_;
    iterator end_;
    iterator end_of_storage_;

private: //-内部使用函數
    void fill();

public: //-=========constructor、destructor、operator
    vector();
    explicit vector(size_type n);
    vector(size_type n, const value_type val);
    //拷贝构造
    vector(const vector &other);
    //移动构造
    vector(vector &&other) noexcept;
    /*
		如果不加任何判断,当T是int类型时候：
		stl::vector<int> v(10,1);
		会走到这个逻辑里面来
	*/
    template <typename iter_t, typename std::enable_if<!std::is_integral<iter_t>::value>::type>
    vector(iter_t first, iter_t last);

    //析构
    ~vector();

    //拷贝赋值运算符
    vector &operator=(const vector &v);
    //移动赋值运算符
    vector &operator=(vector &&) noexcept;

public: //-=========iterators
    iterator begin() noexcept { return begin_; }
    const_iterator begin() const noexcept { return begin_; }
    iterator end() noexcept { return end_; }
    const_iterator end() const noexcept { return end_; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end_); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end_); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin_); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin_); }
    const_iterator cbegin() const noexcept { return const_iterator(begin_); }
    const_iterator cend() const noexcept { return const_iterator(end_); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end_); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin_); }

public: //-=========Capacity
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    void resize(size_type n);
    void resize(size_type n, const value_type &val);
    size_type capacity() const noexcept;
    bool empty() const noexcept;
    void reserve(size_type n);
    void shrink_to_fit();

public: //-=========Element access
    reference operator[](size_type n);
    const_reference operator[](size_type n) const;
    reference at(size_type n);
    const_reference at(size_type n) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    value_type *data() noexcept;
    const value_type *data() const noexcept;

public: //-=========Modifiers
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type &val);
    void assign(std::initializer_list<value_type> il);

    void push_back(const value_type &val);
    void push_back(value_type &&val);
    void pop_back();

    iterator insert(const_iterator position, const value_type &val);
    iterator insert(const_iterator position, size_type n, const value_type &val);
    template <typename InputIterator>
    iterator insert(const_iterator position, InputIterator first, InputIterator last);
    iterator insert(const_iterator position, value_type &&val);
    iterator insert(const_iterator position, std::initializer_list<value_type> il);

    iterator erase(const_iterator position);
    iterator erase(const_iterator first, const_iterator last);

    void swap(vector &x);
    void clear() noexcept;

    template <typename... Args>
    iterator emplace(const_iterator position, Args &&...args);
    template <typename... Args>
    void emplace_back(Args &&...args);

public: //-=========Allocator
    allocator_type get_allocator() const noexcept;
};

//-=============Non-member function overloads
template <typename T>
bool operator==(const stl::vector<T> &lhs, const vector<T> &rhs)
{
    //fixme：use stl::equal
    return (lhs.size() == rhs.size() && stl::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <typename T>
bool operator!=(const stl::vector<T> &lhs, const vector<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const stl::vector<T> &lhs, const vector<T> &rhs)
{
    //fixme：use stl::lexicographical_compare
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator<=(const stl::vector<T> &lhs, const vector<T> &rhs)
{
    return !(lhs < rhs);
}

template <typename T>
bool operator>(const stl::vector<T> &lhs, const vector<T> &rhs)
{
    return rhs < lhs;
}

template <typename T>
bool operator>=(const stl::vector<T> &lhs, const vector<T> &rhs)
{
    return !(lhs < rhs);
}

template <class T>
void swap(vector<T> &x, vector<T> &y)
{
    x.swap(y);
}

//-

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
template <typename iter_t, typename std::enable_if<!std::is_integral<iter_t>::value>::type>
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
