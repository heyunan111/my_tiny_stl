//
// Created by hyn on 2023/2/11.
//

#ifndef MY_TINY_STL_UTILITY_H
#define MY_TINY_STL_UTILITY_H

#include <cstddef>
#include "type_traits.h"


namespace hyn {
    namespace stl {

        //move
        template<typename T>
        typename std::remove_reference<T>::type &&move(T &&t) noexcept {
            return static_cast<typename std::remove_reference<T>::type &&>(t);
        }

        //forward完美转发
        template<class T>
        T &&forward(typename std::remove_reference<T>::type &t) noexcept {
            return static_cast<T &&>(t);
        }

        template<class T>
        T &&forward(typename std::remove_reference<T>::type &&t) noexcept {
            static_assert(!std::is_lvalue_reference<T>::value,
                          "std::forward must not be used to convert an rvalue to an lvalue");
            return static_cast<T &&>(t);
        }

        //swap
        template<typename T>
        void swap(T &a, T &b) {
            T tmp = move(a);
            a = move(b);
            b = move(tmp);
        }

        template<class T1, class T2>
        void iter_swap(T1 a, T2 b) {
            swap(*a, *b);
        }

        template<class T1, class T2>
        T2 swap_range(T1 begin, T1 end, T2 T2begin) {
            for (; begin != end; ++begin, (void) ++T2begin) {
                //其中（void）确保使用内置逗号运算符 - 以防万一用户定义的重载执行了意外操作
                iter_swap(begin, T2begin);
            }
            return T2begin;
        }

        template<typename T, size_t N>
        void swap(T (&a)[N], T(&b)[N]) {
            swap_range(a, a + N, b);
        }

        //pair----------------------------------------------------------------
        template<class Ty1, class Ty2>
        struct pair {
            typedef Ty1 first_type;
            typedef Ty2 second_type;

            first_type first;
            second_type second;


        };
    }
}


#endif //MY_TINY_STL_UTILITY_H
