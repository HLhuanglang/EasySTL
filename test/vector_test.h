#ifndef _EASYNET_VECTOR_TEST_H_
#define _EASYNET_VECTOR_TEST_H_

#include "vector.h"
#include <vector>

template <typename T>
bool operator==(const std::vector<T> &lhs, const nostd::vector<T> &rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (int i = 0; i < lhs.size(); i++) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator!=(const std::vector<T> &lhs, const nostd::vector<T> &rhs) {
    return !(lhs == rhs);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "std::vector{";
    for (int i = 0; i < v.size(); i++) {
        os << v[i];
        if (i != v.size() - 1) {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const nostd::vector<T> &v) {
    os << "nostd::vector{";
    for (int i = 0; i < v.size(); i++) {
        os << v[i];
        if (i != v.size() - 1) {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

#endif // !_EASYNET_VECTOR_TEST_H_
