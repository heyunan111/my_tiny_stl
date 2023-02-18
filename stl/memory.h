//
// Created by hyn on 2023/2/18.
//
#pragma once

#include <cstddef>
#include <cstdlib>
#include <climits>
#include <limits>

#include "algo_base.h"
#include "allocator.h"
#include "construct.h"
#include "uninitialized.h"

namespace hyn {
    namespace stl {

        template<class T>
        constexpr T *address_of(T &value) noexcept {
            return &value;
        }

        template<class T>
        hyn::stl::pair<T *, ptrdiff_t> get_buffer_helper(ptrdiff_t len, T *) {
            if (len > static_cast<ptrdiff_t>(std::numeric_limits<int>::max() / sizeof(T)))
                len = std::numeric_limits<int>::max() / sizeof(T);
            while (len > 0) {
                T *temp = static_cast<T *>(malloc(static_cast<size_t>(len) * sizeof(T)));
                if (temp)
                    return hyn::stl::pair<T *, ptrdiff_t>(temp, len);
                len /= 2;
            }
            return hyn::stl::pair<T *, ptrdiff_t>(nullptr, 0);
        }

        template<class T>
        hyn::stl::pair<T *, ptrdiff_t> get_temporary_buffer(ptrdiff_t len) {
            return get_buffer_helper(len, static_cast<T *>(0));
        }

        template<class T>
        hyn::stl::pair<T *, ptrdiff_t> get_temporary_buffer(ptrdiff_t len, T *) {
            return get_buffer_helper(len, static_cast<T *>(0));
        }

        template<class T>
        void release_temporary_buffer(T *ptr) {
            free(ptr);
        }

        /*************************************************************************************************************************/
        //temporary_buffer 缓冲区的申请与释放

    }//namespace
}//namespace