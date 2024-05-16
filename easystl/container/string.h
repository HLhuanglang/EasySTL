#ifndef __BASIC_STRING_H
#define __BASIC_STRING_H

#include <cstddef>
#include <cstring>

#include "base/allocator.h"
#include "base/iterator.h"

namespace nostd {
// 字符特性基类模板
template <class CharType, class IntType>
class CharTraitsBase {
 public:
    typedef CharType char_type;  // 字符类型
    typedef IntType int_type;    // int类型
 public:
    // 字符赋值
    static void assign(char_type &c1, const char_type &c2) { c1 = c2; }

    // 字符比较
    static bool eq(const CharType &c1, const CharType &c2) {
        return c1 == c2;
    }

    // 字符大小比较
    static bool lt(const CharType &c1, const CharType &c2) {
        return c1 < c2;
    }

    // 字串比较
    static int compare(const CharType *s1, const CharType *s2, size_t n) {
        for (size_t i = 0; i < n; ++i)
            if (!eq(s1[i], s2[i]))
                return s1[i] < s2[i] ? -1 : 1;
        return 0;
    }

    // 字串长度
    static size_t length(const CharType *s) {
        const CharType __nullchar = CharType();  // char()就是'\0'
        size_t i;
        for (i = 0; !eq(s[i], __nullchar); ++i) {
        }
        return i;
    }

    // 在串中查找字符
    static const CharType *find(const CharType *s, size_t n, const CharType &c) {
        for (; n > 0; ++s, --n)
            if (eq(*s, c))
                return s;
        return 0;
    }

    // 字符串移到另一字符串
    static CharType *move(CharType *s1, const CharType *s2, size_t n) {
        memmove(s1, s2, n * sizeof(CharType));
        return s1;
    }

    // 拷贝一字符串到另字符串
    static CharType *copy(CharType *s1, const CharType *s2, size_t n) {
        memcpy(s1, s2, n * sizeof(CharType));
        return s1;
    }

    // 字符串赋值
    static CharType *assign(CharType *s, size_t n, CharType c) {
        for (size_t i = 0; i < n; ++i)
            s[i] = c;
        return s;
    }

    // 判断是否为结束符
    static int_type not_eof(const int_type &c) {
        return !eq_int_type(c, eof()) ? c : 0;
    }

    // int到char类型的转换
    static char_type to_char_type(const int_type &c) {
        return static_cast<char_type>(c);
    }

    // char到int类型的转换
    static int_type to_int_type(const char_type &c) {
        return static_cast<int_type>(c);
    }

    // 判断俩int类型是否相等
    static bool eq_int_type(const int_type &c1, const int_type &c2) {
        return c1 == c2;
    }

    // 返回结束整型值
    static int_type eof() {
        return static_cast<int_type>(-1);
    }
};

template <class _CharT>
class CharTraits : public CharTraitsBase<_CharT, _CharT> {};

// Specialization for char.
// char字符类型模板偏特化
template <>
class CharTraits<char> : public CharTraitsBase<char, int> {
 public:
    // int类型到char类型的转换
    static char_type to_char_type(const int_type &c) {
        return static_cast<char_type>(static_cast<unsigned char>(c));
    }

    // char到int类型的转换
    static int_type to_int_type(const char_type &c) {
        return static_cast<unsigned char>(c);
    }

    // 比较两个字符串
    static int compare(const char *s1, const char *s2, size_t n) {
        return memcmp(s1, s2, n);
    }

    // 字符串的长度
    static size_t length(const char *s) { return strlen(s); }

    // 字符赋值
    static void assign(char &c1, const char &c2) { c1 = c2; }

    // 字串赋值
    static char *assign(char *s, size_t n, char c) {
        memset(s, c, n);
        return s;
    }
};

template <class CharType, class CharTraits = nostd::CharTraits<CharType>>
class basic_string {
 public:
    using traits_type = CharTraits;
    using char_traits = CharTraits;

    using allocator_type = nostd::allocator<CharType>;
    using data_allocator = nostd::allocator<CharType>;

    using value_type = typename allocator_type::value_type;
    using pointer = typename allocator_type::pointer;
    using const_pointer = typename allocator_type::const_pointer;
    using reference = typename allocator_type::reference;
    using const_reference = typename allocator_type::const_reference;
    using size_type = typename allocator_type::size_type;
    using difference_type = typename allocator_type::difference_type;

    using iterator = value_type *;
    using const_iterator = const value_type *;
    using reverse_iterator = nostd::reverse_iterator<iterator>;
    using const_reverse_iterator = nostd::reverse_iterator<const_iterator>;

    allocator_type get_allocator() { return allocator_type(); }

    static_assert(std::is_pod<CharType>::value, "Character type of basic_string must be a POD");
    static_assert(std::is_same<CharType, typename traits_type::char_type>::value,
                  "CharType must be same as traits_type::char_type");

 public:
    // 末尾位置的值，例:
    // if (str.find('a') != string::npos) { /* do something */ }
    static constexpr size_type npos = static_cast<size_type>(-1);

 private:
    iterator m_buffer;  // 储存字符串的起始位置
    size_type m_size;   // 大小
    size_type m_cap;    // 容量
};

using string = basic_string<char>;

}  // namespace nostd
#endif
