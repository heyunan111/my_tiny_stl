//
// Created by hyn on 2023/2/12.
//
#pragma once

#include <cstddef>
#include "type_traits.h"

namespace hyn {
    namespace stl {
        struct input_iterator_tag {
        };//输入

        struct output_iterator_tag {
        };//输出

        struct forward_iterator_tag : public input_iterator_tag {
        };//向前

        struct bidirectional_iterator_tag : public forward_iterator_tag {
        };//双向

        struct random_access_iterator_tag : public bidirectional_iterator_tag {
        };//随机

        template<class Category, class T, class Pointer =T *, class Reference = T &, class Distance = ptrdiff_t>
        struct iterator {
            typedef Category iterator_category;
            typedef T value_type;
            typedef Pointer pointer;
            typedef Reference reference;
            typedef Distance difference_type;
        };

        //iterator_traits
        template<class T>
        struct has_iterator_category {
        private:
            template<typename U>
            static int has_category(...) {}

            template<typename U>
            static char has_category(typename U::iterator_category * = 0) {}

        public:
            static const bool value = sizeof(has_category<T>(0)) == sizeof(char);
        };//判断是否有category，若有匹配第二个，返回值类型char，value为true



        template<class Iter, bool>
        struct iterator_traits_implement {
        };

        template<class Iter>
        struct iterator_traits_implement<Iter, true> {
            typedef typename Iter::iterator_category iterator_category;
            typedef typename Iter::value_type value_type;
            typedef typename Iter::pointer pointer;
            typedef typename Iter::reference reference;
            typedef typename Iter::difference_type difference_type;
        };

        template<typename T, bool>
        struct iterator_traits_helper {
        };

        template<typename Iter>
        struct iterator_traits_helper<Iter, true>
                : public iterator_traits_implement<Iter,
                        std::is_convertible<typename Iter::iterator_category, input_iterator_tag>::value
                        || std::is_convertible<typename Iter::iterator_category, output_iterator_tag>::value> {
        };

        template<typename Iter>
        struct iterator_traits : public iterator_traits_helper<Iter, has_iterator_category<Iter>::value> {
            typedef typename Iter::iterator_category iterator_category;
            typedef typename Iter::value_type value_type;
            typedef typename Iter::pointer pointer;
            typedef typename Iter::reference reference;
            typedef typename Iter::difference_type difference_type;
        };
        template<class T>
        struct iterator_traits<T *> {
            typedef random_access_iterator_tag iterator_category;
            typedef T value_type;
            typedef T *pointer;
            typedef T &reference;
            typedef ptrdiff_t difference_type;
        };

        template<class T>
        struct iterator_traits<const T *> {
            typedef random_access_iterator_tag iterator_category;
            typedef T value_type;
            typedef const T *pointer;
            typedef const T &reference;
            typedef ptrdiff_t difference_type;
        };

        template<class T, class U, bool = has_iterator_category<iterator_traits<T>>::value>
        struct has_iterator_category_of
                : public m_bool_constant<std::is_convertible<typename iterator_traits<T>::iterator_category, U>::value> {
        };

        template<class T, class U>
        struct has_iterator_category_of<T, U, false> : public m_false_type {
        };
        template<class Iter>
        struct is_input_iterator : public has_iterator_category_of<Iter, input_iterator_tag> {
        };

        template<class Iter>
        struct is_output_iterator : public has_iterator_category_of<Iter, output_iterator_tag> {
        };

        template<class Iter>
        struct is_forward_iterator : public has_iterator_category_of<Iter, forward_iterator_tag> {
        };

        template<class Iter>
        struct is_bidirectional_iterator : public has_iterator_category_of<Iter, bidirectional_iterator_tag> {
        };

        template<class Iter>
        struct is_random_access_iterator : public has_iterator_category_of<Iter, random_access_iterator_tag> {
        };

        template<class T>
        struct is_iterator : public m_bool_constant<is_input_iterator<T>::value || is_output_iterator<T>::value> {
        };

        template<class Iter>
        typename iterator_traits<Iter>::iterator_category iterator_category(const Iter &) {
            typedef typename iterator_traits<Iter>::iterator_category category;
            return category();
        }

        template<class Iter>
        typename iterator_traits<Iter>::difference_type *distance_type(const Iter &) {
            return static_cast<typename iterator_traits<Iter>::difference_type>(0);
        }

        template<class Iter>
        typename iterator_traits<Iter>::value_type *value_type(const Iter &) {
            return static_cast<typename iterator_traits<Iter>::value_type>(0);
        }

        template<class inputIter>
        typename iterator_traits<inputIter>::difference_type
        distance_dispatch(inputIter first, inputIter second, input_iterator_tag) {
            typename iterator_traits<inputIter>::difference_type n = 0;
            while (first != second) {
                ++first;
                ++n;
            }
            return n;
        }

        template<class randomIter>
        typename iterator_traits<randomIter>::difference_type
        distance_dispatch(randomIter first, randomIter last, random_access_iterator_tag) {
            return last - first;
        }

        template<class inputIter>
        typename iterator_traits<inputIter>::difference_type
        distance(inputIter first, inputIter second) {
            return distance_dispatch(first, second, iterator_category(first));
        }

        /*                     迭代器前进n个距离                                        */

        template<class inputIter, class Distance>
        void advance_dispatch(inputIter &in, Distance n, input_iterator_tag) {
            while (--n) {
                ++in;
            }
        }

        template<class bidirectionalIter, class Distance>
        void advance_dispatch(bidirectionalIter &bid, Distance n, bidirectional_iterator_tag) {
            if (n >= 0) {
                while (--n)
                    ++bid;
            } else {
                while (++n)
                    --bid;
            }
        }

        template<class randIter, class Distance>
        void advance_dispatch(randIter &rand, Distance n, random_access_iterator_tag) {
            rand += n;
        }

        template<class Iter, class Distance>
        void advance(Iter &it, Distance n) {
            advance_dispatch(it, n, iterator_category(it));
        }
        /****************************************************************************************************************/
        //reverse_iterator反向迭代器

        template<class Iter>
        class reverse_iterator {
        private:
            Iter current;//对应的正向迭代器
        public:
            typedef typename Iter::iterator_category iterator_category;
            typedef typename Iter::value_type value_type;
            typedef typename Iter::pointer pointer;
            typedef typename Iter::reference reference;
            typedef typename Iter::difference_type difference_type;

            typedef Iter iterator_type;
            typedef reverse_iterator<Iter> self;

            //构造
            reverse_iterator() {}

            explicit reverse_iterator(iterator_type i) : current(i) {}

            reverse_iterator(const self &it) : current(it.current) {}

            iterator_type base() const {
                return current;
            }

            reference operator*() const {
                auto temp = current;
                return *--current;
            }

            reference operator->() const {
                return &(operator*());
            }

            self &operator++() {
                --current;
                return *this;
            }//前缀 eg:++i

            self operator++(int) {
                self temp = *this;
                --current;
                return temp;
            }//后缀 eg:i++

            self &operator--() {
                ++current;
                return *this;
            }//前缀 eg:--i

            self operator--(int) {
                self temp = *this;
                ++current;
                return temp;
            }//后缀 eg:i--

            self &operator+=(difference_type n) {
                current -= n;
                return *this;
            }

            self operator+(difference_type n) const {
                return (current - n);
            }

            self &operator-=(difference_type n) {
                current += n;
                return *this;
            }

            self operator-(difference_type n) const {
                return (current + n);
            }

            reference operator[](difference_type n) const {
                return *(*this + n);
            }
        };

        template<class T>
        typename reverse_iterator<T>::difference_type
        operator-(const reverse_iterator<T> &a, const reverse_iterator<T> &b) {
            return b.base() - a.base();
        }

        template<class T>
        bool operator==(const reverse_iterator<T> &a, const reverse_iterator<T> &b) {
            return a.base() == b.base();
        }

        template<class T>
        bool operator>(const reverse_iterator<T> &a, const reverse_iterator<T> &b) {
            return b.base() > a.base();
        }

        template<class T>
        bool operator<(const reverse_iterator<T> &a, const reverse_iterator<T> &b) {
            return b.base() < a.base();
        }

        template<class T>
        bool operator!=(const reverse_iterator<T> &a, const reverse_iterator<T> &b) {
            return !(a == b);
        }

        template<class T>
        bool operator>=(const reverse_iterator<T> &a, const reverse_iterator<T> &b) {
            return !(a < b);
        }

        template<class T>
        bool operator<=(const reverse_iterator<T> &a, const reverse_iterator<T> &b) {
            return !(a > b);
        }

    }//namespace
}//namespace
