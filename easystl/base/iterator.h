/*
    ref: https://cplusplus.com/reference/iterator

    //-=---------------------------
    //Category tags
    //-=---------------------------
    input_iterator_tag	        Input iterator category (class)
    output_iterator_tag	        Output iterator category (class)
    forward_iterator_tag	    Forward iterator category (class)
    bidirectional_iterator_tag	Bidirectional iterator category (class)
    random_access_iterator_tag	Random-access iterator category (class)

    //-=---------------------------
    //functions:
    //-=---------------------------
    advance	    Advance iterator (function template)
    distance	Return distance between iterators (function template)
    begin	    Iterator to beginning (function template)
    end	        Iterator to end (function template)
    prev	    Get iterator to previous element (function template)
    next	    Get iterator to next element (function template)

    back_inserter	    Construct back insert iterator (function template)
    front_inserter	    Constructs front insert iterator (function template)
    inserter	        Construct insert iterator (function template)
    make_move_iterator	Construct move iterator (function template)

    //-=---------------------------
    //class:
    //-=---------------------------
    iterartor
    iterator_traits

    reverse_iterator	    Reverse iterator (class template)
    move_iterator	        Move iterator (class template)
    back_insert_iterator	Back insert iterator (class template)
    front_insert_iterator	Front insert iterator (class template)
    insert_iterator	        Insert iterator (class template)
    istream_iterator	    Istream iterator (class template)
    ostream_iterator	    Ostream iterator (class template)
    istreambuf_iterator	    Input stream buffer iterator (class template)
    ostreambuf_iterator	    Output stream buffer iterator (class template)

*/
#ifndef __ITERATOR_H
#define __ITERATOR_H

#include <cstddef>  //ptrdiff_t定义

namespace nostd {

//-=========================tag
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

//-=========================iterartor
template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T *, typename Reference = T &>
struct iterator {
    using iterator_category = Category;
    using value_type = T;
    using difference_type = Distance;
    using pointer = Pointer;
    using reference = Reference;
};

//-=========================traits
template <typename Iterator>
struct iterator_traits {
    using iterator_category = typename Iterator::iterator_category;
    using value_type = typename Iterator::value_type;
    using difference_type = typename Iterator::difference_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;
};
template <typename T>
struct iterator_traits<T *> {
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using reference = T &;
};
template <typename T>
struct iterator_traits<const T *> {
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = const T *;
    using reference = const T &;
};

//-=========================some rename
template <typename Iterator>
using iterator_category_t = typename iterator_traits<Iterator>::iterator_category;

template <typename Iterator>
using value_type_t = typename iterator_traits<Iterator>::value_type;

template <typename Iterator>
using difference_type_t = typename iterator_traits<Iterator>::difference_type;

template <typename Iterator>
using pointer_t = typename iterator_traits<Iterator>::pointer;

template <typename Iterator>
using reference_t = typename iterator_traits<Iterator>::reference;

//-=========================class
// reserve_iterator
/*
    member functions:
    (constructor)	Constructs reverse_iterator object (public member function)
    base	    Return base iterator (public member function)
    operator*	Dereference iterator (public member function)
    operator+	Addition operator (public member function)
    operator++	Increment iterator position (public member function)
    operator+=	Advance iterator (public member function)
    operator-	Subtraction operator (public member function)
    operator--	Decrease iterator position (public member function)
    operator-=	Retrocede iterator (public member function)
    operator->	Dereference iterator (public member function)
    operator[]	Dereference iterator with offset (public member function)

    no-menber-functions:
    relational operators【==、!=、<、<=、>、>=】	Relational operators for reverse_iterator (function template)
    operator+	            Addition operator (function template)
    operator-	            Subtraction operator (function template)
*/
template <typename Iterator>
class reverse_iterator {
 protected:
    Iterator current;  // 与之对应的正向迭代器

 public:
    using iterator_category = iterator_category_t<Iterator>;
    using value_type = value_type_t<Iterator>;
    using difference_type = difference_type_t<Iterator>;
    using pointer = pointer_t<Iterator>;
    using reference = reference_t<Iterator>;
    using iterator_type = Iterator;  // 正向迭代器
    using self = reverse_iterator;   // 反向迭代器

 public:
    reverse_iterator() {}
    explicit reverse_iterator(iterator_type value)
        : current(value) {}

    explicit reverse_iterator(const self &value)
        : current(value.current) {}

    iterator_type base() const { return current; }

    reference operator*() const {
        Iterator temp = current;
        return *--temp;  // 对逆向迭代器的取值等价于对应的正向迭代器后退一个单位取值
    }

    pointer operator->() const { return &(operator*()); }

    self &operator++() {
        --current;
        return *this;
    }

    self operator++(int) {
        self temp = *this;
        --current;
        return temp;
    }

    self &operator--() {
        ++current;
        return *this;
    }

    self operator--(int) {
        self temp = *this;
        ++current;
        return temp;
    }

    self operator+(difference_type n) const { return self(current - n); }

    self &operator+=(difference_type n) const {
        current -= n;
        return *this;
    }

    self operator-(difference_type n) const { return self(current + n); }

    self &operator-=(difference_type n) const {
        current += n;
        return *this;
    }

    reference operator[](difference_type n) const { return *(*this + n); }
};

template <typename Iterator>
inline bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
    return lhs.base() == rhs.base();
}

template <typename Iterator>
inline bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
    return !(lhs == rhs);
}

template <typename Iterator>
inline bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
    return rhs.base() < lhs.base();
}

template <typename Iterator>
inline bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
    return rhs < lhs;
}

template <typename Iterator>
inline bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
    return !(rhs < lhs);
}

template <typename Iterator>
inline bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
    return !(lhs < rhs);
}

template <typename Iterator>
inline typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
    return rhs.base() - lhs.base();
}

template <typename Iterator>
inline reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &x) {
    return reverse_iterator<Iterator>(x.base() - n);
}

//-=========================functions
// distance
template <typename Input>
inline difference_type_t<Input> _distance(Input first, Input last, input_iterator_tag) {
    difference_type_t<Input> n = 0;
    while (first != last)
        ++first, ++n;
    return n;
}

template <typename Input>
inline difference_type_t<Input> _distance(Input first, Input last, random_access_iterator_tag) {
    return last - first;
}

template <typename Input>
inline difference_type_t<Input> distance(Input first, Input last) {
    return _distance(first, last, iterator_category_t<Input>());
}

// advance
template <typename Input, typename Distance>
inline void _advance(Input &i, Distance n, input_iterator_tag) {
    while (n--)
        ++i;
}

template <typename Input, typename Distance>
inline void _advance(Input &i, Distance n, bidirectional_iterator_tag) {
    if (n >= 0)
        while (n--)
            ++i;
    else
        while (n++)
            --i;
}

template <typename Input, typename Distance>
inline void _advance(Input &i, Distance n, random_access_iterator_tag) {
    i += n;
}

template <typename Input, typename Distance>
inline void advance(Input &i, Distance n) {
    _advance(i, n, iterator_category_t<Input>());
}

}  // namespace nostd

#endif
