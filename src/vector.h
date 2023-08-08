/*
 * https://github.com/llvm/llvm-project/blob/main/libcxx/include/vector
 * https://cplusplus.com/reference/vector/vector/
 */
#ifndef __VECTOR_H
#define __VECTOR_H

#include <algorithm>
#include <iterator>
#include <memory>

#include <initializer_list>

#include "algorithm.h"
#include "allocator.h"
#include "iterator.h"

namespace nostd {

template <typename T, typename Alloc = nostd::allocator<T>>
class vector {
 public:
    using value_type = T;
    using allocator_type = Alloc;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = typename std::allocator_traits<allocator_type>::size_type;
    using difference_type = typename std::allocator_traits<allocator_type>::difference_type;
    using pointer = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;
    using iterator = value_type *;
    using const_iterator = const value_type *;
    using reverse_iterator = nostd::reverse_iterator<iterator>;
    using const_reverse_iterator = nostd::reverse_iterator<const_iterator>;

    static_assert((std::is_same<typename allocator_type::value_type, value_type>::value), "Allocator::value_type must be same type as value_type");

 private:
    iterator m_begin;
    iterator m_end;
    iterator m_end_of_storage;

 public: //-=========constructor、destructor、operator=
    // default (1)
    //     - explicit vector (const allocator_type& alloc = allocator_type());
    // fill (2)
    //     - explicit vector (size_type n);
    //     - vector (size_type n, const value_type& val,const allocator_type& alloc = allocator_type());
    // range (3)
    //     - template <class InputIterator>vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
    // copy (4)
    //     - vector (const vector& x);
    //     - vector (const vector& x, const allocator_type& alloc);
    // move (5)
    //     - vector (vector&& x);
    //     - vector (vector&& x, const allocator_type& alloc);
    // initializer list (6)
    //     - vector (initializer_list<value_type> il,       const allocator_type& alloc = allocator_type());
    //
    // copy (1)
    //     - vector& operator= (const vector& x);
    // move (2)
    //     - vector& operator= (vector&& x);
    // initializer list (3)
    //     - vector& operator= (initializer_list<value_type> il);

    explicit vector(const allocator_type &alloc = allocator_type()) {
        m_begin = allocator_type::allocate(16);
        m_end = m_begin;
        m_end_of_storage = m_begin + 16;
    }

    explicit vector(size_type n) {
        m_begin = allocator_type::allocate(n);
        m_end_of_storage = m_begin + n;
        m_end = std::uninitialized_fill_n(m_begin, n, value_type());
    }

    vector(size_type n, const value_type &val, const allocator_type &alloc = allocator_type()) {
        m_begin = allocator_type::allocate(n);
        m_end = m_begin + n;
        m_end_of_storage = m_begin + n;
        std::uninitialized_fill(m_begin, m_end, val);
    }

    //  如果不加任何判断,当T是int类型时候 nostd::vector<int> v(10,1) 会走到这个逻辑里面来
    template <typename iter_t, typename std::enable_if<!std::is_same<iter_t, int>::value>::type * = nullptr>
    vector(iter_t first, iter_t last, const allocator_type &alloc = allocator_type()) {
        static_assert(!std::is_same<iter_t, int>::value, "iter_t cannot be int type");
        size_type n = nostd::distance(first, last);
        m_begin = allocator_type::allocate(n);
        m_end_of_storage = m_begin + n;
        m_end = std::uninitialized_copy(first, last, m_begin);
    }

    vector(const vector &other) {
        m_begin = allocator_type::allocate(other.size());
        m_end_of_storage = m_begin + other.size();
        m_end = std::uninitialized_copy(other.begin(), other.end(), m_begin);
    }
    vector(const vector &other, const allocator_type &alloc) {
        m_begin = alloc.allocate(other.size());
        m_end_of_storage = m_begin + other.size();
        m_end = std::uninitialized_copy(other.begin(), other.end(), m_begin);
    }

    vector(vector &&other) noexcept {
        // todo
    }
    vector(vector &&other, const allocator_type &alloc) noexcept {
        // todo
    }

    vector(std::initializer_list<value_type> il, const allocator_type &alloc = allocator_type()) {
        // todo
    }

    vector &operator=(const vector &v) {
        // todo
    }

    vector &operator=(vector &&) noexcept {
        // todo
    }

    vector &operator=(std::initializer_list<value_type> il) {
        // todo
    }

    ~vector() {
        allocator_type::deallocate(m_begin, m_end_of_storage - m_begin);
    }

 public: // -=========iterators
    iterator begin() noexcept { return m_begin; }
    const_iterator begin() const noexcept { return m_begin; }
    iterator end() noexcept { return m_end; }
    const_iterator end() const noexcept { return m_end; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(m_end); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(m_end); }
    reverse_iterator rend() noexcept { return reverse_iterator(m_begin); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(m_begin); }
    const_iterator cbegin() const noexcept { return const_iterator(m_begin); }
    const_iterator cend() const noexcept { return const_iterator(m_end); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(m_end); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(m_begin); }

 public: //-=========Capacity
    size_type size() const noexcept {
        return m_end - m_begin;
    }
    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
    void resize(size_type n) {
        resize(n, value_type());
    }
    void resize(size_type n, const value_type &val) {
        if (n < size()) {
            m_end = m_begin + n;
        } else {
            insert(m_end, n - size(), val);
        }
    }
    size_type capacity() const noexcept {
        return m_end_of_storage - m_begin;
    }
    bool empty() const noexcept {
        return m_begin == m_end;
    }
    void reserve(size_type n) {
        if (n > capacity()) {
            iterator tmp = allocator_type::allocate(n);
            std::uninitialized_copy(m_begin, m_end, tmp);
            allocator_type::deallocate(m_begin, m_end_of_storage - m_begin);
            m_begin = tmp;
            m_end = m_begin + size();
            m_end_of_storage = m_begin + n;
        }
    }
    void shrink_to_fit() {
        if (size() < capacity()) {
            iterator tmp = allocator_type::allocate(size());
            std::uninitialized_copy(m_begin, m_end, tmp);
            allocator_type::deallocate(m_begin, m_end_of_storage - m_begin);
            m_begin = tmp;
            m_end = m_begin + size();
            m_end_of_storage = m_begin + size();
        }
    }

 public: //-=========Element access
    reference operator[](size_type n) {
        return *(m_begin + n);
    }
    const_reference operator[](size_type n) const {
        return *(m_begin + n);
    }
    reference at(size_type n) {
        if (n >= size()) {
            throw std::out_of_range("vector");
        }
        return *(m_begin + n);
    }
    const_reference at(size_type n) const {
        if (n >= size()) {
            throw std::out_of_range("vector");
        }
        return *(m_begin + n);
    }
    reference front() {
        return *m_begin;
    }
    const_reference front() const {
        return *m_begin;
    }
    reference back() {
        return *(m_end - 1);
    }
    const_reference back() const {
        return *(m_end - 1);
    }
    value_type *data() noexcept {
        return m_begin;
    }
    const value_type *data() const noexcept {
        return m_begin;
    }

 public: //-=========Modifiers
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last) {
        // todo
    }
    void assign(size_type n, const value_type &val) {
        // todo
    }
    void assign(std::initializer_list<value_type> il) {
        // todo
    }

    void push_back(const value_type &val) {
        if (m_end == m_end_of_storage) {
            reserve(size() * 2);
        }
        allocator_type::construct(m_end, val);
        m_end++;
    }
    void push_back(value_type &&val) {
        if (m_end == m_end_of_storage) {
            reserve(size() * 2);
        }
        allocator_type::construct(m_end, std::move(val));
        m_end++;
    }
    void pop_back() {
        allocator_type::destroy(m_end - 1);
        m_end--;
    }

    iterator insert(const_iterator position, const value_type &val) {
        // todo
    }
    iterator insert(const_iterator position, size_type n, const value_type &val) {
        // todo
    }
    template <typename InputIterator>
    iterator insert(const_iterator position, InputIterator first, InputIterator last) {
        // todo
    }
    iterator insert(const_iterator position, value_type &&val) {
        // todo
    }
    iterator insert(const_iterator position, std::initializer_list<value_type> il) {
        // todo
    }

    iterator erase(const_iterator position) {
        // todo
    }
    iterator erase(const_iterator first, const_iterator last) {
        // todo
    }

    void swap(vector &x) {
        std::swap(m_begin, x.m_begin);
        std::swap(m_end, x.m_end);
        std::swap(m_end_of_storage, x.m_end_of_storage);
    }
    void clear() noexcept {
        erase(begin(), end());
    }

    template <typename... Args>
    iterator emplace(const_iterator position, Args &&...args) {
        // todo
    }
    template <typename... Args>
    void emplace_back(Args &&...args) {
        // todo
    }

 public: //-=========Allocator
    allocator_type get_allocator() const noexcept {
        return allocator_type();
    }
};

//-=============Non-member function overloads
template <typename T>
bool operator==(const nostd::vector<T> &lhs, const vector<T> &rhs) {
    // fixme：use nostd::equal
    return (lhs.size() == rhs.size() && nostd::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <typename T>
bool operator!=(const nostd::vector<T> &lhs, const vector<T> &rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const nostd::vector<T> &lhs, const vector<T> &rhs) {
    // fixme：use nostd::lexicographical_compare
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator<=(const nostd::vector<T> &lhs, const vector<T> &rhs) {
    return !(lhs < rhs);
}

template <typename T>
bool operator>(const nostd::vector<T> &lhs, const vector<T> &rhs) {
    return rhs < lhs;
}

template <typename T>
bool operator>=(const nostd::vector<T> &lhs, const vector<T> &rhs) {
    return !(lhs < rhs);
}

template <class T>
void swap(vector<T> &x, vector<T> &y) {
    x.swap(y);
}

} // namespace nostd
#endif // !__VECTOR_H
