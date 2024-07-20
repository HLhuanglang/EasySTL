#ifndef __BASIC_STRING_H
#define __BASIC_STRING_H

#include <cstddef>
#include <cstdint>
#include <cstdio>  // For EOF.
#include <cstring>
#include <cwchar>
#include <ios>

#include "base/allocator.h"
#include "base/iterator.h"

namespace nostd {

// https://github.com/dwdwdw/stl/blob/master/llvm/include/string

template <class CharType, class IntType>
class char_traits_base {
 public:
    using char_type = CharType;       // char_type:The template parameter (charT)
    using int_type = IntType;         // int_type: Integral type that can represent all charT values, as well as eof()
    using off_type = std::streamoff;  // off_type: A type that behaves like streamoff
    using pos_type = std::streampos;  // pos_type: A type that behaves like streampos
    using state_type = mbstate_t;     // state_type: Multibyte transformation state type, such as mbstate_t
 public:
    // 字符比较
    static bool eq(const char_type &c1, const char_type &c2) noexcept {
        return c1 == c2;
    }

    // 字符大小比较
    static bool lt(const char_type &c1, const char_type &c2) noexcept {
        return c1 < c2;
    }

    // 字串长度
    static size_t length(const char_type *s) noexcept {
        const char_type __nullchar = char_type(0);  // char()就是'\0'
        size_t len;
        for (; !eq(*s, __nullchar); ++s) {
            ++len;
        }
        return len;
    }

    // 字符赋值
    static void assign(char_type &c1, const char_type &c2) noexcept { c1 = c2; }
    // 字符串赋值
    static char_type *assign(char_type *s, size_t n, char_type c) noexcept {
        for (size_t i = 0; i < n; ++i)
            s[i] = c;
        return s;
    }

    // 字串比较
    static int compare(const char_type *s1, const char_type *s2, size_t n) noexcept {
        for (size_t i = 0; i < n; ++i)
            if (!eq(s1[i], s2[i]))
                return s1[i] < s2[i] ? -1 : 1;
        return 0;
    }

    // 在串中查找字符
    static const char_type *find(const char_type *s, size_t n, const char_type &c) noexcept {
        for (; n > 0; ++s, --n)
            if (eq(*s, c))
                return s;
        return 0;
    }

    // 字符串移到另一字符串
    static char_type *move(char_type *__s1, const char_type *__s2, size_t __n) noexcept {
        char_type *__r = __s1;
        if (__s1 < __s2) {
            for (; __n; --__n, ++__s1, ++__s2)
                assign(*__s1, *__s2);
        } else if (__s2 < __s1) {
            // 防止内存重叠导致覆盖
            __s1 += __n;
            __s2 += __n;
            for (; __n; --__n)
                assign(*--__s1, *--__s2);
        }
        return __r;
    }

    // 拷贝一字符串到另字符串
    static char_type *copy(char_type *__s1, const char_type *__s2, size_t __n) noexcept {
        static_assert(__s2 < __s1 || __s2 >= __s1 + __n, "char_traits::copy overlapped range");
        char_type *__r = __s1;
        for (; __n; --__n, ++__s1, ++__s2)
            assign(*__s1, *__s2);
        return __r;
    }

    // 返回结束整型值
    static int_type eof() noexcept {
        return int_type(EOF);
    }

    // 判断是否为结束符
    static int_type not_eof(int_type c) noexcept {
        return eq_int_type(c, eof()) ? ~eof() : c;
    }

    // int到char类型的转换
    static char_type to_char_type(int_type c) noexcept {
        return static_cast<char_type>(c);
    }

    // char到int类型的转换
    static int_type to_int_type(char_type c) noexcept {
        return static_cast<int_type>(c);
    }

    // 判断俩int类型是否相等
    static bool eq_int_type(int_type c1, int_type c2) noexcept {
        return c1 == c2;
    }
};

// 灵活性：可以实现对不同的字符类型定制化字符特征
template <class _CharT>
class char_traits : public char_traits_base<_CharT, int> {};

// Specialization for char.
template <>
class char_traits<char> : public char_traits_base<char, int> {
 public:
    static char_type to_char_type(const int_type &c) {
        return static_cast<char_type>(static_cast<unsigned char>(c));
    }
    static int_type to_int_type(const char_type &c) {
        return static_cast<unsigned char>(c);
    }
    static int compare(const char *s1, const char *s2, size_t n) {
        return memcmp(s1, s2, n);
    }
    static size_t length(const char *s) { return strlen(s); }
    static void assign(char &c1, const char &c2) { c1 = c2; }
    static char *assign(char *s, size_t n, char c) {
        memset(s, c, n);
        return s;
    }
};

// Specialization for wchar_t.
template <>
class char_traits<wchar_t> : public char_traits_base<wchar_t, wint_t> {
 public:
    static wchar_t to_char_type(const int_type &c) { return static_cast<wchar_t>(c); }
    static int_type to_int_type(const wchar_t &c) { return static_cast<int_type>(c); }
    static int compare(const wchar_t *s1, const wchar_t *s2, size_t n) {
        return wmemcmp(s1, s2, n);
    }
    static size_t length(const wchar_t *s) { return wcslen(s); }
    static void assign(wchar_t &c1, const wchar_t &c2) { c1 = c2; }
    static wchar_t *assign(wchar_t *s, size_t n, wchar_t c) {
        wmemset(s, c, n);
        return s;
    }
};

// Specialization for char16_t.
template <>
class char_traits<char16_t> : public char_traits_base<char16_t, uint_least16_t> {
 public:
    using pos_type = std::u16streampos;
};

// Specialization for char32_t.
template <>
class char_traits<char32_t> : public char_traits_base<char, uint_least32_t> {
 public:
    using pos_type = std::u32streampos;
};

template <class charT, class traits = nostd::char_traits<charT>, class Alloc = nostd::allocator<charT>>
class basic_string {
 public:
    using traits_type = traits;
    using allocator_type = Alloc;
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

    static_assert(std::is_pod<charT>::value, "Character type of basic_string must be a POD");
    static_assert(std::is_same<charT, typename traits_type::char_type>::value,
                  "charT must be same as traits_type::charT");

 public:
    explicit basic_string(const allocator_type &alloc = allocator_type());
    basic_string(const basic_string &str);
    basic_string(const basic_string &str, const allocator_type &alloc);
    basic_string(const basic_string &str, size_type pos, size_type len = npos, const allocator_type &alloc = allocator_type());
    basic_string(const charT *s, const allocator_type &alloc = allocator_type());
    basic_string(const charT *s, size_type n, const allocator_type &alloc = allocator_type());
    basic_string(size_type n, charT c, const allocator_type &alloc = allocator_type());
    template <class InputIterator>
    basic_string(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
    basic_string(std::initializer_list<charT> il, const allocator_type &alloc = allocator_type());
    basic_string(basic_string &&str) noexcept;
    basic_string(basic_string &&str, const allocator_type &alloc);

    ~basic_string();

    basic_string &operator=(const basic_string &str);
    basic_string &operator=(const charT *s);
    basic_string &operator=(charT c);
    basic_string &operator=(std::initializer_list<charT> il);
    basic_string &operator=(basic_string &&str) noexcept;

 public:
    // 末尾位置的值，例:
    // if (str.find('a') != string::npos) { /* do something */ }
    static constexpr size_type npos = static_cast<size_type>(-1);

 private:
    iterator m_buffer;  // 储存字符串的起始位置
    size_type m_size;   // 大小
    size_type m_cap;    // 容量
};

template <class charT, class traits, class Alloc>
basic_string<charT, traits, Alloc>::basic_string(const allocator_type &alloc)
    : m_buffer(nullptr), m_size(0), m_cap(0) {}

using string = basic_string<char>;
using wstring = basic_string<wchar_t>;
using u16string = basic_string<char16_t>;
using u32string = basic_string<char32_t>;

}  // namespace nostd
#endif
