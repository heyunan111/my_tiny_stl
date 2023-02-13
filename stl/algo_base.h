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


    }//namespace
}//namespace