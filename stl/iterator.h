//
// Created by hyn on 2023/2/12.
//

#ifndef MY_TINY_STL_ITERATOR_H
#define MY_TINY_STL_ITERATOR_H

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
            static int has_category(...);

            template<typename U>
            static char has_category(typename U::iterator_category * = 0);

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
    }
}

#endif //MY_TINY_STL_ITERATOR_H
