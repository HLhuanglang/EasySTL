#ifndef __BASIC_STRING_H
#define __BASIC_STRING_H

#include <cstddef>
#include <iostream>
#include <string.h>

#include "allocator.h"

namespace stl {

template <class CharType>
struct char_traits {
    typedef CharType char_type;

    static size_t length(const char_type* str)
    {
        size_t len = 0;
        for (; *str != char_type(0); ++str)
            ++len;
        return len;
    }

    static int compare(const char_type* s1, const char_type* s2, size_t n)
    {
        for (; n != 0; --n, ++s1, ++s2) {
            if (*s1 < *s2)
                return -1;
            if (*s2 < *s1)
                return 1;
        }
        return 0;
    }

    static char_type* copy(char_type* dst, const char_type* src, size_t n)
    {
        MYSTL_DEBUG(src + n <= dst || dst + n <= src);
        char_type* r = dst;
        for (; n != 0; --n, ++dst, ++src)
            *dst = *src;
        return r;
    }

    static char_type* move(char_type* dst, const char_type* src, size_t n)
    {
        char_type* r = dst;
        if (dst < src) {
            for (; n != 0; --n, ++dst, ++src)
                *dst = *src;
        } else if (src < dst) {
            dst += n;
            src += n;
            for (; n != 0; --n)
                *--dst = *--src;
        }
        return r;
    }

    static char_type* fill(char_type* dst, char_type ch, size_t count)
    {
        char_type* r = dst;
        for (; count > 0; --count, ++dst)
            *dst = ch;
        return r;
    }
};

// Partialized. char_traits<char>
template <>
struct char_traits<char> {
    typedef char char_type;

    static size_t length(const char_type* str) noexcept
    {
        return strlen(str);
    }

    static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept
    {
        return std::memcmp(s1, s2, n);
    }

    static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept
    {
        return static_cast<char_type*>(std::memcpy(dst, src, n));
    }

    static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept
    {
        return static_cast<char_type*>(std::memmove(dst, src, n));
    }

    static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept
    {
        return static_cast<char_type*>(std::memset(dst, ch, count));
    }
};

// Partialized. char_traits<wchar_t>
template <>
struct char_traits<wchar_t> {
    typedef wchar_t char_type;

    static size_t length(const char_type* str) noexcept
    {
        return std::wcslen(str);
    }

    static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept
    {
        return std::wmemcmp(s1, s2, n);
    }

    static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept
    {
        return static_cast<char_type*>(std::wmemcpy(dst, src, n));
    }

    static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept
    {
        return static_cast<char_type*>(std::wmemmove(dst, src, n));
    }

    static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept
    {
        return static_cast<char_type*>(std::wmemset(dst, ch, count));
    }
};

// Partialized. char_traits<char16_t>
template <>
struct char_traits<char16_t> {
    typedef char16_t char_type;

    static size_t length(const char_type* str) noexcept
    {
        size_t len = 0;
        for (; *str != char_type(0); ++str)
            ++len;
        return len;
    }

    static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept
    {
        for (; n != 0; --n, ++s1, ++s2) {
            if (*s1 < *s2)
                return -1;
            if (*s2 < *s1)
                return 1;
        }
        return 0;
    }

    static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept
    {
        char_type* r = dst;
        for (; n != 0; --n, ++dst, ++src)
            *dst = *src;
        return r;
    }

    static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept
    {
        char_type* r = dst;
        if (dst < src) {
            for (; n != 0; --n, ++dst, ++src)
                *dst = *src;
        } else if (src < dst) {
            dst += n;
            src += n;
            for (; n != 0; --n)
                *--dst = *--src;
        }
        return r;
    }

    static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept
    {
        char_type* r = dst;
        for (; count > 0; --count, ++dst)
            *dst = ch;
        return r;
    }
};

template <class CharType, class CharTraits = stl::char_traits<CharType>>
class basic_string {
public:
    typedef CharTraits traits_type;
    typedef CharTraits char_traits;

    typedef stl::allocator<CharType> allocator_type;
    typedef stl::allocator<CharType> data_allocator;

    typedef typename allocator_type::value_type value_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef stl::reverse_iterator<iterator> reverse_iterator;
    typedef stl::reverse_iterator<const_iterator> const_reverse_iterator;

    allocator_type get_allocator() { return allocator_type(); }

    static_assert(std::is_pod<CharType>::value, "Character type of basic_string must be a POD");
    static_assert(std::is_same<CharType, typename traits_type::char_type>::value,
                  "CharType must be same as traits_type::char_type");

public:
    // 末尾位置的值，例:
    // if (str.find('a') != string::npos) { /* do something */ }
    static constexpr size_type npos = static_cast<size_type>(-1);

private:
    iterator buffer_; // 储存字符串的起始位置
    size_type size_;  // 大小
    size_type cap_;   // 容量
};

} // namespace stl
#endif