#ifndef __ALGORITHM_H
#define __ALGORITHM_H

#include <iterator>
#include <utility>

// ref：https://zh.cppreference.com/w/cpp/algorithm

namespace nostd {
//-------Non-modifying sequence operations-------//

///@brief whether all elements in range satisfy condition
///@param first,last: input iterators defining the range to examine
///@param pred: unary predicate function that accepts an element in the range as argument
///@return true if pred return true for `all` the elements in the range[first,last).
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

///@brief whether any element in range satisfy condition
///@param first,last input iterators defining the range to examine
///@param pred unary predicate function that accepts an element in the range as argument
///@return true if pred return true for `any` of the elements in the range[first,last).
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

///@brief whether none element in range satisfy condition
///@param first,last input iterators defining the range to examine
///@param pred unary predicate function that accepts an element in the range as argument
///@return true if pred return true for `none` of the elements in the range[first,last).
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

///@brief applies function to each of the elements in the range
///@param first,last input iterators defining the range to examine
///@param fn unary function that accepts an element in the range as argument
///@return fn
///@note if you want to modify the elements in the range, use reference as argument in fn
template <typename InputIterator, typename Function>
Function for_each(InputIterator first, InputIterator last, Function fn) {
    while (first != last) {
        fn(*first);
        ++first;
    }
    return fn;
}

///@brief find the first element in the range that equals to val
///@param first,last input iterators defining the range to examine
///@param val value to compare the elements to
///@return returns an iterator to the first element in the range[first,last) that compares equal to val.
///@note  uses `operator==` to compare the individual elements to val.
/// if T is a class, you shuold achieve `operator==`, and mark as const,beacuse val is const.
template <typename InputIterator, typename T>
InputIterator find(InputIterator first, InputIterator last, const T& val) {
    while (first != last) {
        if (val == *first) {
            return first;
        }
        ++first;
    }
    return last;
}

///@brief find the first element in the range that satisfies pred()
///@param first,last input iterators defining the range to examine
///@param pred unary predicate function that accepts an element in the range as argument
///@return returns an iterator to the first element in the range[first,last) for which pred return `true`
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

///@brief find the first element in the range that not satisfies pred()
///@param first,last input iterators defining the range to examine
///@param pred unary predicate function that accepts an element in the range as argument
///@return returns an iterator to the first element in the range[first,last) for which pred return `false`
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
    // TODO
}

template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
                          ForwardIterator2 first2, ForwardIterator2 last2,
                          BinaryPredicate pred) {
    // TODO
}

template <typename ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
    // TODO
}

template <typename ForwardIterator, typename BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last,
                              BinaryPredicate pred) {
    // TODO
}

template <typename InputIterator, typename T>
typename std::iterator_traits<InputIterator>::difference_type cout(InputIterator first,
                                                                   InputIterator last,
                                                                   const T& val) {
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

template <class ForwardIterator1, class ForwardIterator2>
bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2) {
    // TODO
}

template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate pred) {
    // TODO
}

template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2) {
    // TODO
}

template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred) {
    // TODO
}

template <class ForwardIterator, class Size, class T>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Size count, const T& val) {
    // TODO
}

template <class ForwardIterator, class Size, class T, class BinaryPredicate>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Size count, const T& val, BinaryPredicate pred) {
    // TODO
}

//-------Modifying sequence operations-------//
// copy
template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
    while (first != last) {
        *result = *first;
        ++first;
        ++result;
    }
    return result;
}

// copy_n
template <class InputIterator, class Size, class OutputIterator>
OutputIterator copy_n(InputIterator first, Size n, OutputIterator result) {
    for (Size i = 0; i < n; ++i) {
        *result = *first;
        ++first;
        ++result;
    }
    return result;
}

// copy_if
template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator result, UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            *result = *first;
            ++result;
        }
        ++first;
    }
    return result;
}

// copy_backward
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result) {
    while (last != first) {
        --last;
        --result;
        *result = *last;
    }
    return result;
}

// move
template <class InputIterator, class OutputIterator>
OutputIterator move(InputIterator first, InputIterator last, OutputIterator result) {
    while (first != last) {
        *result = std::move(*first);
        ++first;
        ++result;
    }
    return result;
}

// move_backward
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 move_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result) {
    while (last != first) {
        --last;
        --result;
        *result = std::move(*last);
    }
    return result;
}

// swap
template <class ForwardIterator1, class ForwardIterator2>
void swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2) {
    while (first1 != last1) {
        iter_swap(first1, first2);
        ++first1;
        ++first2;
    }
}

// iter_swap
template <class ForwardIterator1, class ForwardIterator2>
void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
    std::iter_swap(a, b);
}

// transform
template <class InputIterator, class OutputIterator, class UnaryOperation>
OutputIterator transform(InputIterator first, InputIterator last, OutputIterator result, UnaryOperation op) {
    while (first != last) {
        *result = op(*first);
        ++first;
        ++result;
    }
    return result;
}

// replace
template <class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value) {
    while (first != last) {
        if (*first == old_value) {
            *first = new_value;
        }
        ++first;
    }
}

// replace_if
template <class ForwardIterator, class UnaryPredicate, class T>
void replace_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred, const T& new_value) {
    while (first != last) {
        if (pred(*first)) {
            *first = new_value;
        }
        ++first;
    }
}

// replace_copy
template <class InputIterator, class OutputIterator, class T>
OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator result, const T& old_value, const T& new_value) {
    while (first != last) {
        if (*first == old_value) {
            *result = new_value;
        } else {
            *result = *first;
        }
        ++first;
        ++result;
    }
    return result;
}

// replace_copy_if
template <class InputIterator, class OutputIterator, class UnaryPredicate, class T>
OutputIterator replace_copy_if(InputIterator first, InputIterator last, OutputIterator result, UnaryPredicate pred, const T& new_value) {
    while (first != last) {
        if (pred(*first)) {
            *result = new_value;
        } else {
            *result = *first;
        }
        ++first;
        ++result;
    }
    return result;
}

// fill
template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value) {
    while (first != last) {
        *first = value;
        ++first;
    }
}

// fill_n
template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
    for (Size i = 0; i < n; ++i) {
        *first = value;
        ++first;
    }
    return first;
}

// generate
template <class ForwardIterator, class Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen) {
    while (first != last) {
        *first = gen();
        ++first;
    }
}

// generate_n
template <class OutputIterator, class Size, class Generator>
OutputIterator generate_n(OutputIterator first, Size n, Generator gen) {
    for (Size i = 0; i < n; ++i) {
        *first = gen();
        ++first;
    }
    return first;
}

// remove
template <class ForwardIterator, class T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value) {
    ForwardIterator result = first;
    while (first != last) {
        if (!(*first == value)) {
            *result = std::move(*first);
            ++result;
        }
        ++first;
    }
    return result;
}

// remove_if
template <class ForwardIterator, class UnaryPredicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    ForwardIterator result = first;
    while (first != last) {
        if (!pred(*first)) {
            *result = std::move(*first);
            ++result;
        }
        ++first;
    }
    return result;
}

// remove_copy
template <class InputIterator, class OutputIterator, class T>
OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value) {
    while (first != last) {
        if (!(*first == value)) {
            *result = *first;
            ++result;
        }
        ++first;
    }
    return result;
}

// remove_copy_if
template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, UnaryPredicate pred) {
    while (first != last) {
        if (!pred(*first)) {
            *result = *first;
            ++result;
        }
        ++first;
    }
    return result;
}

// unique
template <class ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last) {
    if (first == last) {
        return last;
    }
    ForwardIterator result = first;
    ++first;
    while (first != last) {
        if (!(*result == *first)) {
            ++result;
            *result = std::move(*first);
        }
        ++first;
    }
    return ++result;
}

// unique_copy
template <class InputIterator, class OutputIterator>
OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator result) {
    if (first == last) {
        return result;
    }
    *result = *first;
    ++result;
    while (++first != last) {
        if (!(*result == *first)) {
            *result = *first;
            ++result;
        }
    }
    return result;
}

template <class BidirectionalIterator>
void reverse(BidirectionalIterator first, BidirectionalIterator last) {
    // TODO
}

template <class BidirectionalIterator, class OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result) {
    // TODO
}

// rotate
// rotate_copy
// rando_shuffle
// shuffle

//------------Partitions------------//
// TODO
// is_partitioned
// partition
// stable_partition
// partition_copy
// partition_point

//------------Sorting operations------------//
// TODO
// sort
// stable_sort
// partial_sort
// partial_sort_copy
// is_sorted
// is_sorted_until
// nth_element

// ----------Binary search (operating on partitioned/sorted ranges)----------//
// lower_bound
template <class ForwardIterator, class T>
ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value) {
    while (first != last) {
        ForwardIterator mid = std::next(first, std::distance(first, last) / 2);
        if (*mid < value) {
            first = std::next(mid);
        } else {
            last = mid;
        }
    }
    return first;
}

// upper_bound
template <class ForwardIterator, class T>
ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value) {
    while (first != last) {
        ForwardIterator mid = std::next(first, std::distance(first, last) / 2);
        if (value < *mid) {
            last = mid;
        } else {
            first = std::next(mid);
        }
    }
    return first;
}

// equal_range
template <class ForwardIterator, class T>
std::pair<ForwardIterator, ForwardIterator> equal_range(ForwardIterator first, ForwardIterator last, const T& value) {
    ForwardIterator lower = lower_bound(first, last, value);
    ForwardIterator upper = upper_bound(first, last, value);
    return std::make_pair(lower, upper);
}

// binary_search
template <class ForwardIterator, class T>
bool binary_search(ForwardIterator first, ForwardIterator last, const T& value) {
    ForwardIterator it = lower_bound(first, last, value);
    return (it != last && !(value < *it));
}

//-------------Merge (operating on sorted ranges)-------------//
// merge
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2, InputIterator2 last2,
                     OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            *result = *first1;
            ++first1;
        } else {
            *result = *first2;
            ++first2;
        }
        ++result;
    }
    return std::copy(first1, last1, std::copy(first2, last2, result));
}

// inplace_merge
template <class BidirectionalIterator>
void inplace_merge(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last) {
    // TODO
}

// includes
template <class InputIterator1, class InputIterator2>
bool includes(InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, InputIterator2 last2) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            ++first1;
        } else if (*first2 < *first1) {
            return false;
        } else {
            ++first1;
            ++first2;
        }
    }
    return first2 == last2;
}

// set_union
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            *result = *first1;
            ++first1;
        } else if (*first2 < *first1) {
            *result = *first2;
            ++first2;
        } else {
            *result = *first1;
            ++first1;
            ++first2;
        }
        ++result;
    }
    return std::copy(first1, last1, std::copy(first2, last2, result));
}

// set_intersection
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2,
                                OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            ++first1;
        } else if (*first2 < *first1) {
            ++first2;
        } else {
            *result = *first1;
            ++first1;
            ++first2;
            ++result;
        }
    }
    return result;
}

// set_difference
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
                              InputIterator2 first2, InputIterator2 last2,
                              OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            *result = *first1;
            ++first1;
            ++result;
        } else if (*first2 < *first1) {
            ++first2;
        } else {
            ++first1;
            ++first2;
        }
    }
    return std::copy(first1, last1, result);
}

// set_symmetric_difference
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
                                        InputIterator2 first2, InputIterator2 last2,
                                        OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            *result = *first1;
            ++first1;
            ++result;
        } else if (*first2 < *first1) {
            *result = *first2;
            ++first2;
            ++result;
        } else {
            ++first1;
            ++first2;
        }
    }
    return std::copy(first1, last1, std::copy(first2, last2, result));
}

//-----------Heap operations-----------//
// push_heap
template <class RandomAccessIterator>
void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
    typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
    difference_type len = std::distance(first, last);
    difference_type hole = len - 1;
    difference_type parent = (hole - 1) / 2;
    while (hole > 0 && *(first + hole) > *(first + parent)) {
        iter_swap(first + hole, first + parent);
        hole = parent;
        parent = (hole - 1) / 2;
    }
}

// pop_heap
template <class RandomAccessIterator>
void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
    typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
    difference_type len = std::distance(first, last);
    iter_swap(first, first + len - 1);
    difference_type hole = 0;
    difference_type child = 2 * hole + 1;
    while (child < len - 1) {
        if (child + 1 < len - 1 && *(first + child) < *(first + child + 1)) {
            ++child;
        }
        if (*(first + hole) < *(first + child)) {
            iter_swap(first + hole, first + child);
            hole = child;
            child = 2 * hole + 1;
        } else {
            break;
        }
    }
}

// make_heap
template <class RandomAccessIterator>
void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
    typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
    difference_type len = std::distance(first, last);
    for (difference_type i = len / 2 - 1; i >= 0; --i) {
        difference_type hole = i;
        difference_type child = 2 * hole + 1;
        while (child < len) {
            if (child + 1 < len && *(first + child) < *(first + child + 1)) {
                ++child;
            }
            if (*(first + hole) < *(first + child)) {
                iter_swap(first + hole, first + child);
                hole = child;
                child = 2 * hole + 1;
            } else {
                break;
            }
        }
    }
}

// sort_heap
template <class RandomAccessIterator>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
    while (first != last) {
        pop_heap(first, last);
        --last;
    }
}

// is_heap
template <class RandomAccessIterator>
bool is_heap(RandomAccessIterator first, RandomAccessIterator last) {
    typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
    difference_type len = std::distance(first, last);
    for (difference_type i = 1; i < len; ++i) {
        if (*(first + i) > *(first + (i - 1) / 2)) {
            return false;
        }
    }
    return true;
}

// is_heap_until
template <class RandomAccessIterator>
RandomAccessIterator is_heap_until(RandomAccessIterator first, RandomAccessIterator last) {
    typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
    difference_type len = std::distance(first, last);
    for (difference_type i = 1; i < len; ++i) {
        if (*(first + i) > *(first + (i - 1) / 2)) {
            return first + i;
        }
    }
    return last;
}

//-----------Min/max operations-----------//
template <typename T>
const T& min(const T& a, const T& b) {
    return !(b < a) ? a : b;
}

template <typename T, typename Compare>
const T& min(const T& a, const T& b, Compare cmp) {
    return !cmp(a < b) ? a : b;
}

// min_element
template <class ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last) {
    if (first == last) {
        return last;
    }
    ForwardIterator smallest = first;
    ++first;
    while (first != last) {
        if (*first < *smallest) {
            smallest = first;
        }
        ++first;
    }
    return smallest;
}

// max_element
template <class ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last) {
    if (first == last) {
        return last;
    }
    ForwardIterator largest = first;
    ++first;
    while (first != last) {
        if (*largest < *first) {
            largest = first;
        }
        ++first;
    }
    return largest;
}

// minmax_element
template <class ForwardIterator>
std::pair<ForwardIterator, ForwardIterator> minmax_element(ForwardIterator first, ForwardIterator last) {
    if (first == last) {
        return std::make_pair(last, last);
    }
    ForwardIterator smallest = first;
    ForwardIterator largest = first;
    ++first;
    while (first != last) {
        if (*first < *smallest) {
            smallest = first;
        }
        if (*largest < *first) {
            largest = first;
        }
        ++first;
    }
    return std::make_pair(smallest, largest);
}

//-----------other operations-----------//
// lexicographical_compare
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            return true;
        }
        if (*first2 < *first1) {
            return false;
        }
        ++first1;
        ++first2;
    }
    return (first1 == last1) && (first2 != last2);
}

// next_permutation
template <class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last) {
    if (first == last) {
        return false;
    }
    BidirectionalIterator i = last;
    if (first == --i) {
        return false;
    }
    while (true) {
        BidirectionalIterator i1, i2;
        i1 = i;
        if (*--i < *i1) {
            i2 = last;
            while (!(*i < *--i2)) {
            }
            iter_swap(i, i2);
            reverse(i1, last);
            return true;
        }
        if (i == first) {
            reverse(first, last);
            return false;
        }
    }
}

// prev_permutation
template <class BidirectionalIterator>
bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last) {
    if (first == last) {
        return false;
    }
    BidirectionalIterator i = last;
    if (first == --i) {
        return false;
    }
    while (true) {
        BidirectionalIterator i1, i2;
        i1 = i;
        if (*i < *--i1) {
            i2 = last;
            while (!(*--i2 < *i)) {
            }
            iter_swap(i, i2);
            reverse(i1, last);
            return true;
        }
        if (i == first) {
            reverse(first, last);
            return false;
        }
    }
}
}  // namespace nostd

#endif  // !__ALGORITHM_H