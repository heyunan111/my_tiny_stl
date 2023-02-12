//
// Created by hyn on 2023/2/12.
//

#ifndef MY_TINY_STL_ALLOCATOR_H
#define MY_TINY_STL_ALLOCATOR_H

#include "alloc.h"

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
                return static_cast<T *>(alloc::allocate(sizeof(T)));
            }

            static T *allocate(size_t n) {
                if (n == 0)
                    return 0;
                return static_cast<T *>(alloc::allocate(sizeof(T) * n));
            }

            static void deallocate(T *ptr) {
                alloc::deallocate(static_cast<void *>(ptr), sizeof(T));
            }

            static void deallocate(T *ptr, size_t n) {
                if (n == 0)
                    return;
                alloc::deallocate(static_cast<void *>(ptr), sizeof(T) * n);
            }


            static void construct(T *ptr) {
                new(ptr)T();
            }

            static void construct(T *ptr, const T &value) {
                new(ptr)T(value);
            }

            static void destroy(T *ptr) {
                ptr->~T();
            }

            static void destroy(T *a, T *b) {
                for (; a != b; ++a) {
                    a->~T();
                }
            }
        };
    }
}//namespace
#endif //MY_TINY_STL_ALLOCATOR_H
