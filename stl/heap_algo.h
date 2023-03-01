//
// Created by hyn on 2023/2/28.
//
#pragma once

#include "iterator.h"

namespace hyn {
    namespace stl {
        //push_heap的功能是往‘堆’中插入一个数据。但是，它的默认前提是这个区间[first,last)已经满足堆结构，并且要插入的数据已经插入到堆的最后即区间的最后一个位置。
        //push_heap

        template<class RandomIter, class T, class Distance>
        void push_heap_aux(RandomIter first, Distance hole, Distance top, T value) {
            auto parent = (hole - 1) / 2;
            while (hole > top && *(hole + first) < value) {   //大顶堆
                *(hole + first) = *(parent + first);
                hole = parent;
                parent = (hole - 1) / 2;
            }
            *(hole + first) = value;
        }

        template<class RandomIter, class Distance>
        void push_heap_d(RandomIter first, RandomIter last, Distance *) {
            hyn::stl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1));
        }

        template<class RandomIter>
        void push_heap(RandomIter first, RandomIter last) {
            hyn::stl::push_heap_d(first, last, distance_type(first));
        }

        template<class RandomIter, class T, class Distance, class Compared>
        void push_heap_aux(RandomIter first, Distance hole, Distance top, T value, Compared comp) {
            auto parent = (hole - 1) / 2;
            while (hole > top && comp(*(hole + first), value)) {   //大顶堆
                *(hole + first) = *(parent + first);
                hole = parent;
                parent = (hole - 1) / 2;
            }
            *(hole + first) = value;
        }

        template<class RandomIter, class Distance, class Compared>
        void push_heap_d(RandomIter first, RandomIter last, Distance *, Compared comp) {
            hyn::stl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1), comp);
        }

        template<class RandomIter, class Compared>
        void push_heap(RandomIter first, RandomIter last, Compared comp) {
            hyn::stl::push_heap_d(first, last, distance_type(first), comp);
        }

        /*********************************************************************************************************************************************************************/
        //pop_heap

        template<class RandomIter, class Distance, class T>
        void adjust_heap(RandomIter first, Distance hole, Distance len, T value) {
            auto second_hole = 2 * (hole + 1);//hole的右节点
            auto top = hole;
            while (second_hole < len) {
                if (*(first + second_hole) < *(first + hole - 1))
                    second_hole--;
                *(first + hole) = *(first + second_hole);
                second_hole = 2 * (second_hole + 1);
            }
            if (second_hole == len) {
                *(first + hole) = *(first + second_hole - 1);
                hole = second_hole - 1;
            }
            *(first + hole) = value;
        }

        template<class RandomIter, class Distance, class T>
        void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, T value, Distance *) {
            *result = *first;
            hyn::stl::adjust_heap(first, static_cast<Distance>(0), last - first, value);
        }

        template<class RandomIter>
        void pop_heap(RandomIter first, RandomIter last) {
            hyn::stl::pop_heap_aux(first, last - 1, last - 1, *(last - 1), distance_type(first));
        }

        template<class RandomIter, class Distance, class T, class Comp>
        void adjust_heap(RandomIter first, Distance hole, Distance len, T value, Comp comp) {
            auto second_hole = 2 * (hole + 1);//hole的右节点
            auto top = hole;
            while (second_hole < len) {
                if (comp(*(first + second_hole), *(first + hole - 1)))
                    second_hole--;
                *(first + hole) = *(first + second_hole);
                second_hole = 2 * (second_hole + 1);
            }
            if (second_hole == len) {
                *(first + hole) = *(first + second_hole - 1);
                hole = second_hole - 1;
            }
            *(first + hole) = value;
        }

        template<class RandomIter, class Distance, class T, class Comp>
        void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, T value, Distance *, Comp comp) {
            *result = *first;
            hyn::stl::adjust_heap(first, static_cast<Distance>(0), last - first, value, comp);
        }

        template<class RandomIter, class Comp>
        void pop_heap(RandomIter first, RandomIter last, Comp comp) {
            hyn::stl::pop_heap_aux(first, last - 1, last - 1, *(last - 1), distance_type(first), comp);
        }

        /****************************************************************************************************************************************/
        //sort_heap
        template<class RandoIter>
        void sort_heap(RandoIter first, RandoIter last) {
            while (last - first > 1) {
                pop_heap(first, last--);
            }
        }

        template<class RandomIter, class Comp>
        void sort_heap(RandomIter first, RandomIter last, Comp comp) {
            while (last - first > 1)
                pop_heap(first, last--, comp);
        }

        /******************************************************************************************************************************/
        //make_heap
        template<class RandomIter, class Distance>
        void make_heap_aux(RandomIter first, RandomIter last, Distance *) {
            auto len = last - first;
            if (len < 2)
                return;
            auto hole = (len - 2) / 2;
            while (true) {
                adjust_heap(first, hole, len, *(first + hole));
                if (hole == 0)
                    return;
                hole--;
            }
        }

        template<class RandomIter, class Distance, class Comp>
        void make_heap_aux(RandomIter first, RandomIter last, Distance *, Comp comp) {
            auto len = last - first;
            if (len < 2)
                return;
            auto hole = (len - 2) / 2;
            while (true) {
                adjust_heap(first, hole, len, *(first + hole), comp);
                if (hole == 0)
                    return;
                hole--;
            }
        }

        template<class RandomIter>
        void make_heap(RandomIter first, RandomIter last) {
            make_heap_aux(first, last, distance_type(first));
        }

        template<class RandomIter, class Comp>
        void make_heap(RandomIter first, RandomIter last, Comp comp) {
            make_heap_aux(first, last, distance_type(first), comp);
        }
    }//namespace
}//namespace