//
// Created by hyn on 2023/2/12.
//

#ifndef MY_TINY_STL_ALLOC_H
#define MY_TINY_STL_ALLOC_H

#include <cstdlib>

namespace hyn {
    namespace stl {
        class alloc {
        private:
            enum EAlign {
                ALIGN = 8
            };//小型区块上调边界
            enum EMax_Bytes {
                MAXBYTES = 128
            };//小型区块上界
            enum ENFree_Lists {
                NFREELISTS = (MAXBYTES / ALIGN)
            };//free_list个数
            enum ENobjs {
                NOBJS = 20
            };// 每次增加的节点数

            union obj {
                union obj *next;
                char client[1];
            };

            static obj *free_list[NFREELISTS];

            static char *start_free;
            static char *end_free;
            static size_t heap_size;

            //上调为8的倍数
            static size_t round_up(size_t bytes) {
                return ((bytes + ALIGN - 1) & ~(ALIGN - 1));
            }

            //选择free_list
            static size_t free_list_index(size_t bytes) {
                return (bytes + ALIGN - 1) / (ALIGN - 1);
            }

            static void *refill(size_t n);

            static char *chunk_alloc(size_t size, size_t &nobjs);

        public:
            static void *allocate(size_t bytes);

            static void deallocate(void *ptr, size_t bytes);

            static void *reallocate(void *ptr, size_t told_size, size_t new_size);
        };

    }

    char *hyn::stl::alloc::start_free = nullptr;
    char *hyn::stl::alloc::end_free = nullptr;
    size_t hyn::stl::alloc::heap_size = 0;

    hyn::stl::alloc::obj *hyn::stl::alloc::alloc::free_list[NFREELISTS] = {
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, nullptr
    };

    void *hyn::stl::alloc::allocate(size_t bytes) {
        if (bytes > MAXBYTES) {
            return malloc(bytes);
        }
        size_t index = alloc::free_list_index(bytes);
        obj *list = free_list[index];
        if (list) {
            free_list[index] = list->next;
            return list;
        } else {
            return refill(round_up(bytes));
        }
    }

    void *stl::alloc::refill(size_t n) {
        return nullptr;
    }

    char *stl::alloc::chunk_alloc(size_t size, size_t &nobjs) {
        return nullptr;
    }

    void stl::alloc::deallocate(void *ptr, size_t bytes) {

    }

    void *stl::alloc::reallocate(void *ptr, size_t told_size, size_t new_size) {
        return nullptr;
    }

}//namespace



#endif //MY_TINY_STL_ALLOC_H
