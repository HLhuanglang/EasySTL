/*
min	Return the smallest (function template)
max	Return the largest (function template)
minmax	Return smallest and largest elements (function template)
min_element	Return smallest element in range (function template)
max_element	Return largest element in range (function template)
minmax_element	Return smallest and largest elements in range (function template)
 */
#ifndef __EASYSTL_MIN_MAX_H
#define __EASYSTL_MIN_MAX_H

namespace nostd {

template <typename T>
const T &min(const T &a, const T &b) {
    return !(b < a) ? a : b;
}

template <typename T, typename Compare>
const T &min(const T &a, const T &b, Compare cmp) {
    return !cmp(a < b) ? a : b;
}

} // namespace nostd

#endif // !__EASYSTL_MIN_MAX_H
