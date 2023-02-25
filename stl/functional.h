//
// Created by hyn on 2023/2/20.
//
#pragma once

#include <cstddef>

namespace hyn {
    namespace stl {
        template<class Arg, class Result>
        struct unarg_function {
            typedef Arg argument_type;
            typedef Result result_type;
        };

        template<class Arg1, class Arg2, class Result>
        struct binary_function {
            typedef Arg1 first_argument_type;
            typedef Arg2 second_argument_type;
            typedef Result result_type;
        };

        template<class T>
        struct plus : public binary_function<T, T, T> {
            T operator()(const T &x, const T &y) const {
                return x + y;
            }
        };

        template<class T>
        struct minus : public binary_function<T, T, T> {
            T operator()(const T &x, const T &y) const {
                return x - y;
            }
        };

        template<class T>
        struct multiplies : public binary_function<T, T, T> {
            T operator()(const T &x, const T &y) const { return x * y; }
        };


        template<class T>
        struct divides : public binary_function<T, T, T> {
            T operator()(const T &x, const T &y) const { return x / y; }
        };

        template<class T>
        struct modulus : public binary_function<T, T, T> {
            T operator()(const T &x, const T &y) const { return x % y; }
        };

        template<class T>
        struct negate : public unarg_function<T, T> {
            T operator()(const T &x) const { return -x; }
        };

        //加法证同元素
        template<class T>
        T identity_element(plus<T>) {
            return T(0);
        }

        //乘法的证同元素
        template<class T>
        T identity_element(multiplies<T>) {
            return T(1);
        }

        template<class T>
        struct equal_to : public binary_function<T, T, bool> {
            bool operator()(const T &x, const T &y) const {
                return x == y;
            }
        };

        template<class T>
        struct not_equal_to : public binary_function<T, T, bool> {
            bool operator()(const T &x, const T &y) {
                return x != y;
            }
        };

        template<class T>
        struct greater : public binary_function<T, T, bool> {
            bool operator()(const T &x, const T &y) {
                return x > y;
            }
        };

        template<class T>
        struct less : public binary_function<T, T, bool> {
            bool operator()(const T &x, const T &y) {
                return x < y;
            }
        };

        template<class T>
        struct greater_equal : public binary_function<T, T, bool> {
            bool operator()(const T &x, const T &y) {
                return x >= y;
            }
        };

        template<class T>
        struct less_equal : public binary_function<T, T, bool> {
            bool operator()(const T &x, const T &y) {
                return x <= y;
            }
        };


        template<class T>
        struct logical_and : public binary_function<T, T, bool> {
            bool operator()(const T &x, const T &y) const { return x && y; }
        };


        template<class T>
        struct logical_or : public binary_function<T, T, bool> {
            bool operator()(const T &x, const T &y) const { return x || y; }
        };


        template<class T>
        struct logical_not : public unarg_function<T, bool> {
            bool operator()(const T &x) const { return !x; }
        };


        template<class T>
        struct identity : public unarg_function<T, bool> {
            const T &operator()(const T &x) const { return x; }
        };


        template<class Pair>
        struct select_first : public unarg_function<Pair, typename Pair::first_type> {
            const typename Pair::first_type &operator()(const Pair &x) const {
                return x.first;
            }
        };

        template<class Pair>
        struct select_second : public unarg_function<Pair, typename Pair::second_type> {
            const typename Pair::second_type &operator()(const Pair &x) const {
                return x.second;
            }
        };

        template<class Arg1, class Arg2>
        struct project_first : public binary_function<Arg1, Arg2, Arg1> {
            Arg1 operator()(const Arg1 &x, const Arg2 &) const { return x; }
        };

        template<class Arg1, class Arg2>
        struct project_second : public binary_function<Arg1, Arg2, Arg1> {
            Arg2 operator()(const Arg1 &, const Arg2 &y) const { return y; }
        };

        /**************************************************************************************************************************/

    }//namespace
}//namespace