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

    }//namespace
}//namespace