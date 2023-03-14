//
// Created by hyn on 2023/3/14.
//

#pragma once

#include <iostream>
#include "iterator.h"
#include "memory.h"
#include "functional.h"
#include "exceptdef.h"

namespace hyn {
    namespace stl {


        template<class CharType>
        struct char_traits {
            typedef CharType char_type;

            static size_t length(const char_type *str) {
                size_t len = 0;
                for (; *str != char_type(0); ++str) {
                    ++len;
                }
                return len;
            }

            static int compare(const char_type *s1, const char_type *s2, size_t n) {
                for (; n != 0; --n, ++s1, ++s2) {
                    if (*s1 < *s2)
                        return -1;
                    if (*s2 < *s1)
                        return 1;
                }
                return 0;
            }

            static char_type *copy(char_type *dst, const char_type *src, size_t n) {
                DEBUG(src + n <= dst || dst + n <= src);
                char_type *r = dst;
                for (; n != 0; --n, ++dst, ++src) {
                    *dst = *src;
                }
                return r;
            }

            static char_type *move(char_type *dst, char_type *src, size_t n) {
                char_type *r = dst;
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

            static char_type *fill(char_type *dst, char_type ch, size_t count) {
                char_type *r = dst;
                for (; count > 0; --count, ++dst)
                    *dst = ch;
                return r;
            }
        };

        template<>
        struct char_traits<char> {
            typedef char char_type;

            static size_t length(const char_type *str) noexcept {
                return std::strlen(str);
            }

            static int compare(const char_type *s1, const char_type *s2, size_t n) noexcept {
                return std::memcmp(s1, s2, n);
            }

            static char_type *copy(char_type *dst, const char_type *src, size_t n) noexcept {
                DEBUG(src + n <= dst || dst + n <= src);
                return static_cast<char_type *>(std::memcpy(dst, src, n));
            }

            static char_type *move(char_type *dst, const char_type *src, size_t n) noexcept {
                return static_cast<char_type *>(std::memmove(dst, src, n));
            }

            static char_type *fill(char_type *dst, char_type ch, size_t count) noexcept {
                return static_cast<char_type *>(std::memset(dst, ch, count));
            }
        };

        template<>
        struct char_traits<wchar_t> {
            typedef wchar_t char_type;

            static size_t length(const char_type *str) noexcept {
                return std::wcslen(str);
            }

            static int compare(const char_type *s1, const char_type *s2, size_t n) noexcept {
                return std::wmemcmp(s1, s2, n);
            }

            static char_type *copy(char_type *dst, const char_type *src, size_t n) noexcept {
                DEBUG(src + n <= dst || dst + n <= src);
                return static_cast<char_type *>(std::wmemcpy(dst, src, n));
            }

            static char_type *move(char_type *dst, const char_type *src, size_t n) noexcept {
                return static_cast<char_type *>(std::wmemmove(dst, src, n));
            }

            static char_type *fill(char_type *dst, char_type ch, size_t count) noexcept {
                return static_cast<char_type *>(std::wmemset(dst, ch, count));
            }
        };

        template<>
        struct char_traits<char16_t> {
            typedef char16_t char_type;

            static size_t length(const char_type *str) noexcept {
                size_t len = 0;
                for (; *str != char_type(0); ++str)
                    ++len;
                return len;
            }

            static int compare(const char_type *s1, const char_type *s2, size_t n) noexcept {
                for (; n != 0; --n, ++s1, ++s2) {
                    if (*s1 < *s2)
                        return -1;
                    if (*s2 < *s1)
                        return 1;
                }
                return 0;
            }

            static char_type *copy(char_type *dst, const char_type *src, size_t n) noexcept {
                DEBUG(src + n <= dst || dst + n <= src);
                char_type *r = dst;
                for (; n != 0; --n, ++dst, ++src)
                    *dst = *src;
                return r;
            }

            static char_type *move(char_type *dst, const char_type *src, size_t n) noexcept {
                char_type *r = dst;
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

            static char_type *fill(char_type *dst, char_type ch, size_t count) noexcept {
                char_type *r = dst;
                for (; count > 0; --count, ++dst)
                    *dst = ch;
                return r;
            }
        };


        template<>
        struct char_traits<char32_t> {
            typedef char32_t char_type;

            static size_t length(const char_type *str) noexcept {
                size_t len = 0;
                for (; *str != char_type(0); ++str)
                    ++len;
                return len;
            }

            static int compare(const char_type *s1, const char_type *s2, size_t n) noexcept {
                for (; n != 0; --n, ++s1, ++s2) {
                    if (*s1 < *s2)
                        return -1;
                    if (*s2 < *s1)
                        return 1;
                }
                return 0;
            }

            static char_type *copy(char_type *dst, const char_type *src, size_t n) noexcept {
                DEBUG(src + n <= dst || dst + n <= src);
                char_type *r = dst;
                for (; n != 0; --n, ++dst, ++src)
                    *dst = *src;
                return r;
            }

            static char_type *move(char_type *dst, const char_type *src, size_t n) noexcept {
                char_type *r = dst;
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

            static char_type *fill(char_type *dst, char_type ch, size_t count) noexcept {
                char_type *r = dst;
                for (; count > 0; --count, ++dst)
                    *dst = ch;
                return r;
            }
        };

#define STRING_INIT_SIZE 32

        /**
    *  @class basic_string basic_string.h <string>
    *  @brief  Managing sequences of characters and character-like objects.
    *
    *  @ingroup strings
    *  @ingroup sequences
    *
    *  @tparam _CharT  Type of character
    *  @tparam _Traits  Traits for character type, defaults to char_traits<_CharT>.
    */
        template<typename _CharT, class _Traits = hyn::stl::char_traits<_CharT>>
        class basic_string {

        public:
            typedef _Traits traits_type;
            typedef _Traits char_traits;

            typedef hyn::stl::allocator<_CharT> allocator_type;
            typedef hyn::stl::allocator<_CharT> data_allocator;

            typedef typename allocator_type::value_type value_type;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::size_type size_type;
            typedef typename allocator_type::difference_type difference_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef typename allocator_type::const_reference const_reference;

            typedef value_type *iterator;
            typedef const value_type *const_iterator;
            typedef hyn::stl::reverse_iterator<iterator> reverse_iterator;
            typedef hyn::stl::reverse_iterator<const_iterator> const_reverse_iterator;

            allocator_type get_allocator() {
                return allocator_type();
            }

            static_assert(std::is_pod<_CharT>::value, "Character type of basic_string must be a POD");
            static_assert(std::is_same<_CharT, typename traits_type::char_type>::value,
                          "CharType must be same as traits_type::char_type");

        public:
            //末尾位置的值
            static constexpr size_type npos = static_cast<size_type>(-1);

        private:
            iterator buffer_; //存储字符串的起始位置
            size_type size_;//大小
            size_type cap_;//容量

        public:

            iterator begin() noexcept {
                return buffer_;
            }

            const_iterator begin() const noexcept {
                return buffer_;
            }

            iterator end() noexcept {
                return buffer_ + size_;
            }

            const_iterator end() const noexcept {
                return buffer_ + size_;
            }

            reverse_iterator rbegin() noexcept {
                return reverse_iterator(end());
            }

        private:

            //helper fun

            void try_init() noexcept;

            void fill_init(size_type n, value_type ch);

            template<typename Iter>
            void copy_init(Iter first, Iter last, hyn::stl::input_iterator_tag);

            template<typename Iter>
            void copy_init(Iter first, Iter last, hyn::stl::forward_iterator_tag);

            void init_from(const_pointer src, size_type pos, size_type n);

            void destroy_buffer();

            const_pointer to_raw_pointer() const;

            void reinsert(size_type size);

            template<typename Iter>
            basic_string &append_range(Iter first, Iter last);

            int compare_cstr(const_pointer s1, size_type n1, const_pointer s2, size_type n2) const;

            basic_string &replace_cstr(const_iterator first, size_type count1, const_pointer str, size_type count2);

            basic_string &replace_fill(const_iterator first, size_type count1, size_type count2, value_type ch);

            template<class Iter>
            basic_string &replace_copy(const_iterator first, const_iterator last, Iter first2, Iter last2);

            void reallocate(size_type need);

            iterator reallocate_and_fill(iterator pos, size_type n, value_type ch);

            iterator reallocate_and_copy(iterator pos, const_iterator first, const_iterator last);
        };

        /***********************************************/
        //try_init

        template<typename _CharT, typename _Trait>
        void basic_string<_CharT, _Trait>::try_init() noexcept {
            try {
                buffer_ = data_allocator::allocate(static_cast<size_type>(STRING_INIT_SIZE));
                size_ = 0;
                cap_ = 0;
            } catch (...) {
                buffer_ = nullptr;
                size_ = 0;
                cap_ = 0;
            }
        }

        template<typename _CharT, typename _Trait>
        void basic_string<_CharT, _Trait>::fill_init(size_type n, value_type ch) {
            const auto init_size = hyn::stl::max(static_cast<size_type>(STRING_INIT_SIZE), n + 1);
            buffer_ = data_allocator::allocate(init_size);
            char_traits::fill(buffer_, ch, n);
            size_ = n;
            cap_ = init_size;
        }

        /* template<typename _CharT, typename _Trait>
         template<class Iter>
         void basic_string<_CharT, _Trait>::copy_init(Iter first, Iter last, hyn::stl::input_iterator_tag) {

         }

         template<typename Iter>
         void copy_init(Iter first, Iter last, hyn::stl::forward_iterator_tag);

         void init_from(const_pointer src, size_type pos, size_type n);

         void destroy_buffer();*/

        /*const_pointer to_raw_pointer() const;

        void reinsert(size_type size);

        template<typename Iter>
        basic_string &append_range(Iter first, Iter last);

        int compare_cstr(const_pointer s1, size_type n1, const_pointer s2, size_type n2) const;

        basic_string &replace_cstr(const_iterator first, size_type count1, const_pointer str, size_type count2);

        basic_string &replace_fill(const_iterator first, size_type count1, size_type count2, value_type ch);

        template<class Iter>
        basic_string &replace_copy(const_iterator first, const_iterator last, Iter first2, Iter last2);

        void reallocate(size_type need);

        iterator reallocate_and_fill(iterator pos, size_type n, value_type ch);

        iterator reallocate_and_copy(iterator pos, const_iterator first, const_iterator last);*/
    }//namespace
}//namespace