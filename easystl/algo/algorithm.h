#ifndef __ALGORITHM_H
#define __ALGORITHM_H

#include <iterator>
#include <utility>

namespace nostd {

/*
lower_bound
upper_bound
equal_range
binary_search
*/
// TODO

/*
push_heap
pop_heap
make_heap
sort_heap
is_heap
is_heap_until
*/
// TODO

/*
merge
inplace_merge
includes
set_union
set_intersection
set_difference
set_symmetric_difference
*/
// TODO

/*
min	Return the smallest (function template)
max	Return the largest (function template)
minmax	Return smallest and largest elements (function template)
min_element	Return smallest element in range (function template)
max_element	Return largest element in range (function template)
minmax_element	Return smallest and largest elements in range (function template)
 */
// TODO

template <typename T>
const T &min(const T &a, const T &b) {
    return !(b < a) ? a : b;
}

template <typename T, typename Compare>
const T &min(const T &a, const T &b, Compare cmp) {
    return !cmp(a < b) ? a : b;
}

/*
copy
copy_n
copy_if
copy_backward
move
move_backward
swap
swap_ranges
iter_swap
transform
replace
replace_if
replace_copy
replace_copy_i
fill
fill_n
generate
generate_n
remove
remove_if
remove_copy
remove_copy_if
unique
unique_copy
reverse
reverse_copy
rotate
rotate_copy
random_shuffle
shuffle
*/
template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result);

template <class InputIterator, class Size, class OutputIterator>
OutputIterator copy_n(InputIterator first, Size n, OutputIterator result);

template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator result, UnaryPredicate pred);

template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result);

template <class InputIterator, class OutputIterator>
OutputIterator move(InputIterator first, InputIterator last, OutputIterator result);

template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 move_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result);

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

/*
lexicographical_compare	Lexicographical less-than comparison (function template)
next_permutation	Transform range to next permutation (function template)
prev_permutation	Transform range to previous permutation (function template)
*/
// TODO

/*
is_partitioned
partition
stable_partition
partition_copy
partition_point
*/
// TODO

/*
sort
stable_sort
partial_sort
partial_sort_copy
is_sorted
is_sorted_until
nth_element
 */
// TODO

}  // namespace nostd

#endif  // !__ALGORITHM_H
