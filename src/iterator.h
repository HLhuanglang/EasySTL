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

#include <cstddef> //ptrdiff_t定义
#include <iostream>

namespace nostd {

//-=========================tag
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

//-=========================base iterartor
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
    Iterator current; //与之对应的正向迭代器

 public:
    using iterator_category = iterator_category_t<Iterator>;
    using value_type = value_type_t<Iterator>;
    using difference_type = difference_type_t<Iterator>;
    using pointer = pointer_t<Iterator>;
    using reference = reference_t<Iterator>;

    using iterator_type = Iterator; //正向迭代器
    using self = reverse_iterator;  //反向迭代器

 public:
    reverse_iterator() {}
    explicit reverse_iterator(iterator_type value)
        : current(value) {}

    explicit reverse_iterator(const self &value)
        : current(value.current) {}

    iterator_type base() const { return current; }
    reference operator*() const {
        Iterator temp = current;
        return *--temp; //对逆向迭代器的取值等价于对应的正向迭代器后退一个单位取值
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

// insert_iterator
template <typename Container>
class insert_iterator {
 protected:
    Container *container; //底层容器
    typename Container::iterator iter;

 public:
    using iterator_category = output_iterator_tag;
    using value_tyep = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

 public:
    insert_iterator(Container &value, typename Container::iterator i)
        : container(&value), iter(i) {}

    insert_iterator &operator=(const typename Container::value_type &value) {
        iter = container->insert(iter, value); //调用insert
        ++iter;                                //保证insert_iterator永远与目标贴合
        return *this;
    }

    // Does nothing. Returns a reference to the object.
    insert_iterator &operator*() { return *this; }
    insert_iterator &operator++() { return *this; }
    insert_iterator &operator++(int) { return *this; }
};

// back_insert_iterator
template <typename Container>
class back_insert_iterator {
 protected:
    Container *container; //底层容器

 public:
    using iterator_category = output_iterator_tag;
    using value_tyep = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

 public:
    explicit back_insert_iterator(Container &value)
        : container(&value) {}
    back_insert_iterator &operator=(
        const typename Container::value_type &value) {
        container->push_back(value); //本质上是调用了push_back
        return *this;
    }

    // Does nothing. Returns a reference to the object.
    back_insert_iterator &operator*() { return *this; }
    back_insert_iterator &operator++() { return *this; }
    back_insert_iterator operator++(int) { return *this; }
};

// front_insert_iterator无法用于vector，因为后者不具备push_front
template <typename Container>
class front_insert_iterator {
 protected:
    Container *container; //底层容器

 public:
    using iterator_category = output_iterator_tag;
    using value_tyep = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

 public:
    explicit front_insert_iterator(Container &value)
        : container(&value) {}

    front_insert_iterator &operator=(
        const typename Container::value_type &value) {
        container->push_front(value);
        return *this;
    }

    //以下三个接口对back_insert_iterator无用，关闭功能
    front_insert_iterator &operator*() { return *this; }
    front_insert_iterator &operator++() { return *this; }
    front_insert_iterator operator++(int) { return *this; }
};

// stream:input_stream,output_stream

template <typename T, typename Distance = ptrdiff_t>
class istream_iterator {
 protected:
    std::istream *stream;
    T value;
    bool end_marker;
    void read() {
        end_marker = (*stream) ? true : false;
        if (end_marker)
            *stream >> value;
        //完成输入后，stream状态可能发生了改变，再次判定
        end_marker = (*stream) ? true : false;
    }

 public:
    using iterator_category = input_iterator_tag;
    using value_tyep = T;
    using difference_type = Distance;
    using pointer = const T *; //由于身为input_iterator，采用const较为保险
    using reference = const T &;

    istream_iterator()
        : stream(&std::cin), end_marker(false) {}
    explicit istream_iterator(std::istream &s)
        : stream(&s) {
        read();
    }

    reference operator*() const { return value; }
    pointer operator->() const { return &(operator*()); }

    istream_iterator &operator++() {
        read();
        return *this;
    }

    istream_iterator operator++(int) {
        istream_iterator temp = *this;
        read();
        return temp;
    }
};

template <typename T>
class ostream_iterator {
 protected:
    std::ostream *stream;
    const char *interval; //输出间隔符

 public:
    using iterator_category = output_iterator_tag;
    using value_tyep = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

    ostream_iterator()
        : stream(&std::cout), interval(nullptr) {}
    ostream_iterator(std::ostream &s, const char *c)
        : stream(&s), interval(c) {}

    ostream_iterator &operator=(const T &value) {
        *stream << value;
        if (interval)
            *stream << interval;
        return *this;
    }

    ostream_iterator &operator*() { return *this; }
    ostream_iterator &operator++() { return *this; }
    ostream_iterator operator++(int) { return *this; }
};

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

// back_inserter
template <typename Container>
inline back_insert_iterator<Container> back_inserter(Container &x) {
    return back_insert_iterator<Container>(x);
}

// front_inserter
template <typename Container>
inline front_insert_iterator<Container> front_inserter(Container &x) {
    return front_insert_iterator<Container>(x);
}

// inserter
template <typename Container, typename Iterator>
inline insert_iterator<Container> inserter(Container &x, Iterator i) {
    return insert_iterator<Container>(x, i);
}

// move_iterator
// TODO

} // namespace nostd

#endif
