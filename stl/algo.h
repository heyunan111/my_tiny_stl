//
// Created by hyn on 2023/3/2.
//

#pragma once

#include <cstddef>
#include <ctime>

#include "algo_base.h"
#include "memory.h"
#include "heap_algo.h"
#include "functional.h"

namespace hyn {
    namespace stl {
        // all_of
        template<class InputIter, class UnaryPredicate>
        bool all_of(InputIter first, InputIter last, UnaryPredicate unary_predicate) {
            for (; first != last; ++first)
                if (!unary_predicate(*first))
                    return false;
            return true;
        }

        /*****************************************************************************************/
        // any_of
        template<class InputIter, class UnaryPredicate>
        bool any_of(InputIter first, InputIter last, UnaryPredicate unary_predicate) {
            for (; first != last; ++first)
                if (unary_predicate(*first))
                    return true;
            return false;
        }

        /*****************************************************************************************/
        // none_of
        template<class InputIter, class UnaryPredicate>
        bool none_of(InputIter first, InputIter last, UnaryPredicate unary_predicate) {
            for (; first != last; ++first)
                if (unary_predicate(*first))
                    return false;
            return true;
        }

        /*****************************************************************************************/
        // count
        template<class InputIter, class T>
        size_t count(InputIter first, InputIter last, const T &value) {
            size_t n = 0;
            for (; first != last; ++first) {
                if (*first == value)
                    ++n;
            }
            return n;
        }

        /*****************************************************************************************/
        // count_if
        template<class InputIter, class UnaryPredicate>
        size_t count_if(InputIter first, InputIter last, UnaryPredicate unary_predicate) {
            size_t n = 0;
            for (; first != last; ++first) {
                if (unary_predicate(*first))
                    ++n;
            }
            return n;
        }

        /*****************************************************************************************/
        // find
        template<class InputIter, class T>
        InputIter find(InputIter first, InputIter last, const T &value) {
            while (first != last && *first != value)
                ++first;
            return first;
        }

        /*****************************************************************************************/
        // find_if
        template<class InputIter, class UnaryPredicate>
        InputIter find_if(InputIter first, InputIter last, UnaryPredicate unary_predicate) {
            while (first != last && !unary_predicate(*first))
                ++first;
            return first;
        }

        /*****************************************************************************************/
        // find_if_not
        template<class InputIter, class UnaryPredicate>
        InputIter find_if_not(InputIter first, InputIter last, UnaryPredicate unary_predicate) {
            while (first != last && unary_predicate(*first))
                ++first;
            return first;
        }

        /*****************************************************************************************/
        // search
        template<class ForwardIter1, class ForwardIter2>
        ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2) {
            auto distance1 = hyn::stl::distance(first1, last1);
            auto distance2 = hyn::stl::distance(first2, last2);
            if (distance1 < distance2)
                return last1;
            auto current1 = first1;
            auto current2 = first2;
            while (current2 != last2) {
                if (*current1 == *current2) {
                    ++current1;
                    ++current2;
                } else {
                    if (distance1 <= distance2) {
                        return last1;
                    } else {
                        ++first1;
                        current1 = first1;
                        current2 = first2;
                        --distance1;
                    }
                }
            }
            return first1;
        }

        template<class ForwardIter1, class ForwardIter2, class Compared>
        ForwardIter1
        search(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, Compared com) {
            auto distance1 = hyn::stl::distance(first1, last1);
            auto distance2 = hyn::stl::distance(first2, last2);
            if (distance1 < distance2)
                return last1;
            auto current1 = first1;
            auto current2 = first2;
            while (current2 != last2) {
                if (com(*current1, *current2)) {
                    ++current1;
                    ++current2;
                } else {
                    if (distance1 <= distance2) {
                        return last1;
                    } else {
                        ++first1;
                        current1 = first1;
                        current2 = first2;
                        --distance1;
                    }
                }
            }
            return first1;
        }

        /*****************************************************************************************/
        // search_n
    }//namespace
}//namespace










