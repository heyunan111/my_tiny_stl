//
// Created by hyn on 2023/2/13.
//
#pragma once


#include <new>
#include "utility.h"
#include "iterator.h"

namespace hyn {
    namespace stl {

        template<class T>
        void construct(T *ptr) {
            new((void *) ptr) T();
        }

        template<class T1, class T2>
        void construct(T1 *ptr, const T2 &value) {
            new((void *) ptr) T1(value);
        }

        template<class T, class...Args>
        void construct(T *ptr, Args &&...args) {
            new((void *) ptr)T(hyn::stl::forward<Args>(args)...);
        }

        /***************************************************************************************************************************/

        template<class T>
        void destroy_one(T *, std::true_type) {}

        template<class T>
        void destroy_one(T *ptr, std::false_type) {
            if (ptr != nullptr)
                ptr->~T();
        }

        template<class T>
        void destroy(T *ptr) {
            destroy_one(ptr, std::is_trivially_default_constructible<T>{});
        }

        template<class Iter>
        void destroy_category(Iter, Iter, std::true_type) {}

        template<class Iter>
        void destroy_category(Iter first, Iter last, std::false_type) {
            for (; first != last; ++first)
                destroy(&*first);
        }

        template<class Iter>
        void destroy(Iter first, Iter last) {
            destroy_category(first, last, std::is_trivially_default_constructible<Iter>{});
        }

    }//namespace
}//namespace

