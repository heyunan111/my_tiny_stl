//
// Created by hyn on 2023/2/13.
//
#pragma once

#include <cstring>
#include "utility.h"
#include "iterator.h"

namespace hyn {
    namespace stl {
        //max
        template<typename T>
        const T &max(const T &a, const T &b) {
            return a < b ? b : a;
        }

        template<class T, class Comp>
        const T &max(const T &a, const T &b, Comp comp) {
            return comp(a, b) ? b : a;
        }

        //min
        template<class T>
        const T &min(const T &a, const T &b) {
            return a > b ? b : a;
        }

        template<class T, class Comp>
        const T &min(const T &a, const T &b, Comp comp) {
            return comp(b, a) ? b : a;
        }

        //copy
        //input_iterator
        template<class Input, class Output>
        Output unchecked_copy_category(Input first, Input last, Output res, hyn::stl::input_iterator_tag) {
            for (; first != last; ++first, ++res) {
                *res = *first;
            }
            return res;
        }

        //random_access_iterator
        template<class Input, class Output>
        Output unchecked_copy_category(Input first, Input last, Output res, hyn::stl::random_access_iterator_tag) {
            for (auto n = last - first; n > 0; --n, ++first, ++res) {
                *res = *first;
            }
            return res;
        }

        //unchecked_copy
        template<class Input, class Output>
        Output unchecked_copy(Input first, Input last, Output res) {
            return unchecked_copy_category(first, last, hyn::stl::iterator_category(first));
        }
    }//namespace
}//namespace