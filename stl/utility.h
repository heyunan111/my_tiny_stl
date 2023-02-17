//
// Created by hyn on 2023/2/11.
//

#pragma once

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

            Ty1 first;
            Ty2 second;

            pair() = default;

            template<typename u, typename v>
            pair(const pair<u, v> &pr):first(pr.first), second(pr.second) {}

            pair(const first_type &a, const second_type &b) : first(a), second(b) {}

            pair &operator=(const pair &pr) {
                if (this != pr) {
                    first = pr.first;
                    second = pr.second;
                }
                return *this;
            }

            void swap(pair &pr) {
                hyn::stl::swap(first, pr.first);
                hyn::stl::swap(second, pr.second);
            }

        };

        template<typename T1, typename T2>
        bool operator==(const pair<T1, T2> &pr1, const pair<T1, T2> &pr2) {
            return pr1.first == pr2.first && pr1.second == pr2.second;
        }

        template<typename T1, typename T2>
        bool operator!=(const pair<T1, T2> &pr1, const pair<T1, T2> &pr2) {
            return !(pr1 == pr2);
        }

        template<typename T1, typename T2>
        bool operator>(const pair<T1, T2> &pr1, const pair<T1, T2> &pr2) {
            return pr1.first > pr2.first || ((pr1.first == pr2.first) && pr1.second > pr2.second);
        }

        template<typename T1, typename T2>
        bool operator>=(const pair<T1, T2> &pr1, const pair<T1, T2> &pr2) {
            /*pr1 >= pr2
             * !(pr1 < pr2)
             * !(pr2 > pr1)
             * */
            return !(pr2 > pr1);
        }

        template<typename T1, typename T2>
        bool operator<(const pair<T1, T2> &pr1, const pair<T1, T2> &pr2) {
            /*pr1 < pr2
             * pr2 > pr1
             * */
            return pr2 > pr1;
        }

        template<typename T1, typename T2>
        bool operator<=(const pair<T1, T2> &pr1, const pair<T1, T2> &pr2) {
            /*pr1 <= pr2
             * !(pr1 > pr2)
             * */
            return !(pr1 > pr2);
        }


        //make_pair
        template<typename T1, typename T2>
        pair<T1, T2> make_pair(const T1 &t1, const T2 &t2) {
            return pair<T1, T2>(t1, t2);
        }
    }
}
