#pragma once

#include <iterator>
#include <utility>

#include <type_traits>

namespace nostd {
// return true if pred return true for `all` the elements in the range[first,last).
template <typename InputIterator, typename UnaryPredicate>
bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
    while (first != last) {
        if (!pred(*first)) {
            return false;
        }
        ++first;
    }
    return true;
}

// return true if pred return true for `any` of the elements in the range[first,last).
template <typename InputIterator, typename UnaryPredicate>
bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            return true;
        }
        ++first;
    }
    return false;
}

// return true if pred return false for `all` of the elements in the range[first,last).
template <typename InputIterator, typename UnaryPredicate>
bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            return false;
        }
        ++first;
    }
    return true;
}

// applies fn to each of the elements in the range[first,last).
template <typename InputIterator, typename Function>
Function for_each(InputIterator first, InputIterator last, Function fn) {
    while (first != last) {
        fn(*first);
        ++first;
    }
    return fn;
}

// returns an iterator to the first element in the range[first,last) that compares equal
// to val. The function uses `operator==` to compare the individual elements to val.
template <typename InputIterator, typename T>
InputIterator find(InputIterator first, InputIterator last, const T &val) {
    while (first != last) {
        if (val == *first) {
            return first;
        }
        ++first;
    }
    return last;
}

// returns an iterator to the first element in the range[first,last) for which pred return `true`
template <typename InputIterator, typename UnaryPredicate>
InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            return first;
        }
        ++first;
    }
    return last;
}

// returns an iterator to the first element in the range[first,last) for which pred return `false`
template <typename InputIterator, typename UnaryPredicate>
InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred) {
    while (first != last) {
        if (!pred(*first)) {
            return first;
        }
        ++first;
    }
    return last;
}

template <typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
                          ForwardIterator2 first2, ForwardIterator2 last2) {
}

template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
                          ForwardIterator2 first2, ForwardIterator2 last2,
                          BinaryPredicate pred) {
}

template <typename ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
}

template <typename ForwardIterator, typename BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last,
                              BinaryPredicate pred) {
}

template <typename InputIterator, typename T>
typename std::iterator_traits<InputIterator>::difference_type cout(InputIterator first,
                                                                   InputIterator last,
                                                                   const T &val) {
    typename std::iterator_traits<InputIterator>::difference_type cnt = 0;
    while (first != last) {
        if (val == *first) {
            ++cnt;
        }
        ++first;
    }
    return cnt;
}

template <typename InputIterator, typename UnaryPredicate>
typename std::iterator_traits<InputIterator>::difference_type cout(InputIterator first,
                                                                   InputIterator last,
                                                                   UnaryPredicate pred) {
    typename std::iterator_traits<InputIterator>::difference_type cnt = 0;
    while (first != last) {
        if (pred(*first)) {
            ++cnt;
        }
        ++first;
    }
    return cnt;
}

template <typename InputIterator1, typename InputIterator2>
std::pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1,
                                                   InputIterator2 first2) {
}

template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
std::pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1,
                                                   InputIterator2 first2, BinaryPredicate pred) {
}

template <typename InputIterator1, typename InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1,
           InputIterator2 first2) {
    while (first1 != last1) {
        if (!(*first1 == *first2)) {
            return false;
        }
        ++first1;
        ++first2;
    }
    return true;
}

template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1,
           InputIterator2 first2, BinaryPredicate pred) {
    while (first1 != last1) {
        if (!pred(first1, first2)) {
            return false;
        }
        ++first1;
        ++first2;
    }
    return true;
}

template <typename ForwardIterator1, typename ForwardIterator2>
bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1,
                    ForwardIterator2 first2, ForwardIterator2 last2) {
}

template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1,
                    ForwardIterator2 first2, ForwardIterator2 last2,
                    BinaryPredicate pred) {
}

template <typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
                        ForwardIterator2 first2, ForwardIterator2 last2) {
}

template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
                        ForwardIterator2 first2, ForwardIterator2 last2,
                        BinaryPredicate pred) {
}
} // namespace nostd