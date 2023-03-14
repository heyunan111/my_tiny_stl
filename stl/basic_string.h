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
        template<typename CharT, class Traits = hyn::stl::char_traits<CharT>>
        class basic_string {

        public:
            typedef Traits traits_type;
            typedef Traits char_traits;

            typedef hyn::stl::allocator<CharT> allocator_type;
            typedef hyn::stl::allocator<CharT> data_allocator;

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

            static_assert(std::is_pod<CharT>::value, "Character type of basic_string must be a POD");
            static_assert(std::is_same<CharT, typename traits_type::char_type>::value,
                          "CharType must be same as traits_type::char_type");

        public:
            //末尾位置的值
            static constexpr size_type npos = static_cast<size_type>(-1);

        private:
            iterator buffer_; //存储字符串的起始位置
            size_type size_;//大小
            size_type cap_;//容量

        public:

            /*******************************************************************************************/
            //iterator
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

            const_reverse_iterator rbegin() const noexcept {
                return const_reverse_iterator(end());
            }

            reverse_iterator rend() noexcept {
                return reverse_iterator(begin());
            }

            const_reverse_iterator rend() const noexcept {
                return const_reverse_iterator(begin());
            }

            const_iterator cbegin() const noexcept {
                return begin();
            }

            const_iterator cend() const noexcept {
                return end();
            }

            const_reverse_iterator crbegin() const noexcept {
                return rbegin();
            }

            const_reverse_iterator crend() const noexcept {
                return rend();
            }

            /********************************************************************************************************/
            //容器

            bool empty() const noexcept {
                return size_ == 0;
            }

            size_type size() const noexcept {
                return size_;
            }

            size_type length() const noexcept {
                return size_;
            }

            size_type capacity() const noexcept {
                return cap_;
            }

            size_type max_size() const noexcept {
                return static_cast<size_type>(-1);
            }

            void reserve(size_type n);

            void shrink_to_fit();

            /****************************************************************************************************/
            //访问

            reference operator[](size_type n) {
                DEBUG(n <= size_);
                if (n == size_)
                    *(buffer_ + n) = value_type();
                return *(buffer_ + n);
            }

            const_reference operator[](size_type n) const {
                MYSTL_DEBUG(n <= size_);
                if (n == size_)
                    *(buffer_ + n) = value_type();
                return *(buffer_ + n);
            }

            reference at(size_type n) {
                THROW_OUT_OF_RANGE_IF(n >= size_, "basic_string<Char, Traits>::at()""subscript out of range");
                return (*this)[n];
            }

            const_reference at(size_type n) const {
                THROW_OUT_OF_RANGE_IF(n >= size_, "basic_string<Char, Traits>::at()""subscript out of range");
                return (*this)[n];
            }

            reference front() {
                DEBUG(!empty());
                return *begin();
            }

            const_reference front() const {
                DEBUG(!empty());
                return *begin();
            }

            reference back() {
                DEBUG(!empty());
                return *(end() - 1);
            }

            const_reference back() const {
                DEBUG(!empty());
                return *(end() - 1);
            }

            const_pointer data() const noexcept { return to_raw_pointer(); }

            const_pointer c_str() const noexcept { return to_raw_pointer(); }


            /****************************************************************************************************/
            //添加删除

            iterator insert(const_iterator pos, value_type ch);

            iterator insert(const_iterator pos, size_type count, value_type ch);

            template<typename Iter>
            iterator insert(const_iterator pos, Iter first, Iter last);

            basic_string &append(size_type count, value_type ch);

            basic_string &append(const basic_string &str, size_type pos, size_type count);

            basic_string &append(const_pointer s, size_type count);

            basic_string &append(const basic_string &str) {
                return append(str, 0, str.size_);
            }

            basic_string &append(const basic_string &str, size_type pos) {
                return append(str, pos, str.size_ - pos);
            }

            basic_string &append(const_pointer s) {
                return append(s, char_traits::length(s));
            }

            template<typename Iter, typename std::enable_if<hyn::stl::is_input_iterator<Iter>::value, int>::type = 0>
            basic_string &append(Iter first, Iter last) {
                return append_range(first, last);
            }

            iterator erase(const_iterator pos);

            iterator erase(const_iterator first, const_iterator last);

            void resize(size_type count, value_type n);

            void resize(size_type count) {
                resize(count, value_type());
            }

            void clear() noexcept {
                size_ = 0;
            }

            /********************************************************************************************************/
            //compare

            int compare(const basic_string &other) const;

            int compare(size_type pos1, size_type count1, const basic_string &other) const;

            int compare(size_type pos1, size_type count1, const basic_string &other, size_type pos2,
                        size_type count2 = npos) const;

            int compare(const_pointer s) const;

            int compare(size_type pos1, size_type count1, const_pointer s) const;

            int compare(size_type pos1, size_type count1, const_pointer s, size_type count2) const;

            /******************************************************************************************************/
            //substr
            basic_string substr(size_type index, size_type count = npos) {
                count = hyn::stl::min(count, size_ - index);
                return basic_string(buffer_ + index, buffer_ + index + count);
            }

            /******************************************************************************************************/
            //replace
























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

        template<typename CharT, class Traits>
        int basic_string<CharT, Traits>::compare(basic_string::size_type pos1, basic_string::size_type count1,
                                                 basic_string::const_pointer s, basic_string::size_type count2) const {
            return compare_cstr(buffer_ + pos1, hyn::stl::min(count1, size_ - pos1), s, count2);
        }

        template<typename CharT, class Traits>
        int basic_string<CharT, Traits>::compare(basic_string::size_type pos1, basic_string::size_type count1,
                                                 basic_string::const_pointer s) const {
            return compare_cstr(buffer_ + pos1, hyn::stl::min(size_ - pos1, count1), s, char_traits::length(s));
        }

        template<typename CharT, class Traits>
        int basic_string<CharT, Traits>::compare(basic_string::const_pointer s) const {
            return compare_cstr(buffer_, size_, s, char_traits::length(s));
        }

        template<typename CharT, class Traits>
        int basic_string<CharT, Traits>::compare(basic_string::size_type pos1, basic_string::size_type count1,
                                                 const basic_string &other, basic_string::size_type pos2,
                                                 basic_string::size_type count2) const {
            return compare_cstr(buffer_ + pos1, hyn::stl::min(count1, size_ - pos1), other.buffer_,
                                hyn::stl::min(count2, other.size_ - pos2));
        }

        template<typename CharT, class Traits>
        int basic_string<CharT, Traits>::compare(basic_string::size_type pos1, basic_string::size_type count1,
                                                 const basic_string &other) const {
            return compare_cstr(buffer_ + pos1, hyn::stl::min(count1, size_ - pos1), other.buffer_, other.size_);
        }

        template<typename CharT, class Traits>
        int basic_string<CharT, Traits>::compare(const basic_string &other) const {
            return compare_cstr(buffer_, size_, other.buffer_, other.size_);
        }

        template<typename CharT, class Traits>
        void basic_string<CharT, Traits>::resize(basic_string::size_type count, value_type n) {
            if (count < size_)
                erase(buffer_ + count, buffer_ + size_);
            else
                append(count - size_, n);
        }

        template<typename CharT, class Traits>
        typename basic_string<CharT, Traits>::iterator
        basic_string<CharT, Traits>::erase(basic_string::const_iterator first, basic_string::const_iterator last) {
            if (first == begin() && last == end()) {
                clear();
                return end();
            }
            const size_type n = end() - last;
            auto r = const_cast<iterator>(first);
            char_traits::move(r, last, n);
            size_ -= (last - first);
            return r;
        }

        template<typename CharT, class Traits>
        typename basic_string<CharT, Traits>::iterator
        basic_string<CharT, Traits>::erase(basic_string::const_iterator pos) {
            DEBUG(pos != end());
            auto r = const_cast<iterator>(pos);
            char_traits::move(r, pos + 1, end() - pos - 1);
            --size_;
            return r;
        }

        template<typename CharT, class Traits>
        basic_string<CharT, Traits> &
        basic_string<CharT, Traits>::append(basic_string::const_pointer s, basic_string::size_type count) {
            THROW_LENGTH_ERROR_IF(size_ > max_size() - count,
                                  "basic_string<Char, Tratis>'s size too big");
            if (cap_ - size_ < count)
                reallocate(count);
            char_traits::copy(buffer_ + size_, s, count);
            size_ += count;
            return *this;
        }

        template<typename CharT, class Traits>
        basic_string<CharT, Traits> &
        basic_string<CharT, Traits>::append(const basic_string &str, basic_string::size_type pos,
                                            basic_string::size_type count) {
            THROW_LENGTH_ERROR_IF(size_ > max_size() - count,
                                  "basic_string<Char, Tratis>'s size too big");
            if (count == 0)
                return *this;
            if (cap_ - size_ < count)
                reallocate(count);
            char_traits::copy(buffer_ + size_, str.buffer_ + pos, count);
            size_ += count;
            return *this;
        }

        template<typename CharT, class Traits>
        basic_string<CharT, Traits> &basic_string<CharT, Traits>::append(basic_string::size_type count, value_type ch) {
            THROW_LENGTH_ERROR_IF(size_ > max_size() - count, "basic_string<Char, Tratis>'s size too big");
            if (cap_ - size_ < count) {
                reallocate(count);
            }
            char_traits::fill(buffer_ + size_, ch, count);
            size_ += count;
            return *this;
        }

        template<typename CharT, class Traits>
        template<typename Iter>
        typename basic_string<CharT, Traits>::iterator
        basic_string<CharT, Traits>::insert(basic_string::const_iterator pos, Iter first, Iter last) {
            auto r = const_cast<iterator>(pos);
            const size_type len = hyn::stl::distance(first, last);
            if (len == 0)
                return r;
            if (cap_ - size_ < len)
                return reallocate_and_copy(r, first, last);
            if (pos == end()) {
                hyn::stl::uninitialized_copy(first, last, end());
                size_ += len;
                return r;
            }
            char_traits::move(r + len, r, len);
            hyn::stl::uninitialized_copy(first, last, r);
            size_ == len;
            return r;
        }

        template<typename CharT, class Traits>
        typename basic_string<CharT, Traits>::iterator
        basic_string<CharT, Traits>::insert(basic_string::const_iterator pos, basic_string::size_type count,
                                            value_type ch) {
            auto r = const_cast<iterator>(pos);
            if (count == 0)
                return r;
            if (cap_ - count < count)
                return reallocate_and_fill(r, count, ch);
            if (pos == end()) {
                char_traits::fill(end(), ch, count);
                size_ += count;
                return r;
            }
            char_traits::move(end(), ch, count);
            char_traits::fill(r, ch, count);
            size_ += count;
            return r;
        }

        template<typename CharT, class Traits>
        typename basic_string<CharT, Traits>::iterator
        basic_string<CharT, Traits>::insert(basic_string::const_iterator pos, value_type ch) {
            auto r = const_cast<iterator>(pos);
            if (size_ == cap_) {
                return reallocate_and_fill(r, 1, ch);
            }
            char_traits::move(r + 1, r, end() - r);
        }


        template<typename CharT, class Traits>
        void basic_string<CharT, Traits>::reserve(basic_string::size_type n) {
            if (cap_ < n) {
                THROW_LENGHT_ERROR_IF(n > max_size(),
                                      "n can not larger than max_size()""in basic_string<Char,Traits>::reserve(n)");
                auto new_buffer = data_allocator::allocate(n);
                char_traits::move(new_buffer, buffer_, size_);
                buffer_ = new_buffer;
                cap_ = n;
            }
        }

        template<typename CharT, class Traits>
        void basic_string<CharT, Traits>::shrink_to_fit() {
            if (size_ != cap_) {
                reinsert(size_);
            }
        }


    }//namespace
}//namespace