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
}//namespace



#endif //MY_TINY_STL_ALLOC_H
