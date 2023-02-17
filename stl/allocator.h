//
// Created by hyn on 2023/2/12.
//
#pragma once

#include "construct.h"
#include "utility.h"


namespace hyn {
    namespace stl {
        template<class T>
        class allocator {
        public:
            typedef T value_type;
            typedef T *pointer;
            typedef const T *const_pointer;
            typedef T &reference;
            typedef const T &const_reference;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;

            static T *allocate() {
                return static_cast<T *>(::operator new(sizeof(T)));
            }

            static T *allocate(size_type n) {
                if (n == 0)
                    return nullptr;
                return static_cast<T *>(::operator new(sizeof(T) * n));
            }

            static void deallocate(T *ptr) {
                if (ptr == nullptr)
                    return;
                ::operator delete(ptr);
            }

            static void deallocate(T *ptr, size_t) {
                if (ptr == nullptr)
                    return;
                ::operator delete(ptr);
            }

            static void construct(T *ptr) {
                hyn::stl::construct(ptr);
            }

            static void construct(T *ptr, const T &value) {
                hyn::stl::construct(ptr, value);
            }

            static void construct(T *ptr, const T &&value) {
                hyn::stl::construct(ptr, hyn::stl::move(value));
            }

            template<class ...Args>
            static void construct(T *ptr, Args &&...args) {
                hyn::stl::construct(ptr, args...);
            }

            static void destroy(T *ptr) {
                hyn::stl::destroy(ptr);
            }

            static void destroy(T *first, T *last) {
                hyn::stl::destroy(first, last);
            }
        };

    }//namespace
}//namespace

