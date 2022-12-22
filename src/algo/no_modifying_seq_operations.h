#pragma once

#include <type_traits>
#include <iterator>
#include <utility>

namespace stl {
//return true if pred return true for `all` the elements in the range[first,last).
template <typename input_iterator, typename unary_predicate>
bool all_of(input_iterator first, input_iterator last, unary_predicate pred)
{
    while (first != last) {
        if (!pred(*first)) {
            return false;
        }
        ++first;
    }
    return true;
}

//return true if pred return true for `any` of the elements in the range[first,last).
template <typename input_iterator, typename unary_predicate>
bool any_of(input_iterator first, input_iterator last, unary_predicate pred)
{
    while (first != last) {
        if (pred(*first)) {
            return true;
        }
        ++first;
    }
    return false;
}

//return true if pred return false for `all` of the elements in the range[first,last).
template <typename input_iterator, typename unary_predicate>
bool none_of(input_iterator first, input_iterator last, unary_predicate pred)
{
    while (first != last) {
        if (pred(*first)) {
            return false;
        }
        ++first;
    }
    return true;
}

//applies fn to each of the elements in the range[first,last).
template <typename input_iterator, typename function>
function for_each(input_iterator first, input_iterator last, function fn)
{
    while (first != last) {
        fn(*first);
        ++first;
    }
    return fn;
}

//returns an iterator to the first element in the range[first,last) that compares equal
//to val. The function uses `operator==` to compare the individual elements to val.
template <typename input_iterator, typename T>
input_iterator find(input_iterator first, input_iterator last, const T &val)
{
    while (first != last) {
        if (val == *first) return first;
        ++first;
    }
    return last;
}

//returns an iterator to the first element in the range[first,last) for which pred return `true`
template <typename input_iterator, typename unary_predicate>
input_iterator find_if(input_iterator first, input_iterator last, unary_predicate pred)
{
    while (first != last) {
        if (pred(*first)) return first;
        ++first;
    }
    return last;
}

//returns an iterator to the first element in the range[first,last) for which pred return `false`
template <typename input_iterator, typename unary_predicate>
input_iterator find_if_not(input_iterator first, input_iterator last, unary_predicate pred)
{
    while (first != last) {
        if (!pred(*first)) return first;
        ++first;
    }
    return last;
}

template <typename forward_iterator1, typename forward_iterator2>
forward_iterator1 find_end(forward_iterator1 first1, forward_iterator1 last1,
                           forward_iterator2 first2, forward_iterator2 last2)
{
}

template <typename forward_iterator1, typename forward_iterator2, typename binary_predicate>
forward_iterator1 find_end(forward_iterator1 first1, forward_iterator1 last1,
                           forward_iterator2 first2, forward_iterator2 last2,
                           binary_predicate pred)
{
}

template <typename forward_iterator>
forward_iterator adjacent_find(forward_iterator first, forward_iterator last)
{
}

template <typename forward_iterator, typename binary_predicate>
forward_iterator adjacent_find(forward_iterator first, forward_iterator last,
                               binary_predicate pred)
{
}

template <typename input_iterator, typename T>
typename std::iterator_traits<input_iterator>::difference_type cout(input_iterator first,
                                                                    input_iterator last,
                                                                    const T &val)
{
    typename std::iterator_traits<input_iterator>::difference_type cnt = 0;
    while (first != last) {
        if (val == *first) ++cnt;
        ++first;
    }
    return cnt;
}

template <typename input_iterator, typename unary_predicate>
typename std::iterator_traits<input_iterator>::difference_type cout(input_iterator first,
                                                                    input_iterator last,
                                                                    unary_predicate pred)
{
    typename std::iterator_traits<input_iterator>::difference_type cnt = 0;
    while (first != last) {
        if (pred(*first)) ++cnt;
        ++first;
    }
    return cnt;
}

template <typename input_iterator1, typename input_iterator2>
std::pair<input_iterator1, input_iterator2> mismatch(input_iterator1 first1, input_iterator1 last1,
                                                     input_iterator2 first2)
{
}

template <typename input_iterator1, typename input_iterator2, typename binary_predicate>
std::pair<input_iterator1, input_iterator2> mismatch(input_iterator1 first1, input_iterator1 last1,
                                                     input_iterator2 first2, binary_predicate pred)
{
}

template <typename input_iterator1, typename input_iterator2>
bool equal(input_iterator1 first1, input_iterator1 last1,
           input_iterator2 first2)
{
    while (first1 != last1) {
        if (!(*first1 == *first2)) {
            return false;
        }
        ++first1;
        ++first2;
    }
    return true;
}

template <typename input_iterator1, typename input_iterator2, typename binary_predicate>
bool equal(input_iterator1 first1, input_iterator1 last1,
           input_iterator2 first2, binary_predicate pred)
{
    while (first1 != last1) {
        if (!pred(first1, first2)) {
            return false;
        }
        ++first1;
        ++first2;
    }
    return true;
}

template <typename forward_iterator1, typename forward_iterator2>
bool is_permutation(forward_iterator1 first1, forward_iterator1 last1,
                    forward_iterator2 first2, forward_iterator2 last2)
{
}

template <typename forward_iterator1, typename forward_iterator2, typename binary_predicate>
bool is_permutation(forward_iterator1 first1, forward_iterator1 last1,
                    forward_iterator2 first2, forward_iterator2 last2,
                    binary_predicate pred)
{
}

template <typename forward_iterator1, typename forward_iterator2>
forward_iterator1 search(forward_iterator1 first1, forward_iterator1 last1,
                         forward_iterator2 first2, forward_iterator2 last2)
{
}

template <typename forward_iterator1, typename forward_iterator2, typename binary_predicate>
forward_iterator1 search(forward_iterator1 first1, forward_iterator1 last1,
                         forward_iterator2 first2, forward_iterator2 last2,
                         binary_predicate pred)
{
}
} // namespace stl