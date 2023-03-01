//
// Created by hyn on 2023/3/1.
//

#pragma once

#include "iterator.h"

namespace hyn {
    namespace stl {
        // accumulate
        template<class InputIter, class T>
        T accumulate(InputIter first, InputIter last, T init) {
            for (; first != last; ++first) {
                init += *first;
            }
            return init;
        }

        template<class InputIter, class T, class BinaryOp>
        T accumulate(InputIter first, InputIter last, T init, BinaryOp binary_op) {
            for (; first != last; ++first) {
                init = binary_op(init, *first);
            }
            return init;
        }

        /*******************************************************************************************************/
        // adjacent_difference
        template<class InputIter, class OutputIter>
        OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result) {
            if (first == last)
                return result;
            *result = *first;
            auto value = *first;
            while (++first != last) {
                auto temp = *first;
                *++result = temp - value;
                value = temp;
            }
            return ++result;
        }

        template<class InputIter, class OutputIter, class BinaryOp>
        OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result, BinaryOp binary_op) {
            if (first == last) return result;
            *result = *first;
            auto value = *first;
            while (++first != last) {
                auto tmp = *first;
                *++result = binary_op(tmp, value);
                value = tmp;
            }
            return ++result;
        }

        /*****************************************************************************************/
        // inner_product
        template<class InputIter, class OutputInter, class T>
        T inner_product(InputIter first1, InputIter last1, OutputInter first2, T init) {
            for (; first1 != last1; ++first1, ++first2) {
                init += *first1 * *first2;
            }
            return init;
        }

        template<class InputIter1, class InputIter2, class T, class BinaryOp1, class BinaryOp2>
        T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init, BinaryOp1 binary_op1,
                        BinaryOp2 binary_op2) {
            for (; first1 != last1; ++first1, ++first2) {
                init = binary_op1(init, binary_op2(*first1, *first2));
            }
            return init;
        }
        /*****************************************************************************************/
        // iota
        template<class ForwardIter, class T>
        void iota(ForwardIter first, ForwardIter last, T value) {
            while (first != last) {
                *first = value;
                ++first;
                ++value;
            }
        }

        /*****************************************************************************************/
        // partial_sum
        template<class InputIter, class OutputIter>
        OutputIter partial_sum(InputIter first, InputIter last, OutputIter result) {
            if (first == last) return result;
            *result = *first;
            auto value = *first;
            while (++first != last) {
                value = value + *first;
                *++result = value;
            }
            return ++result;
        }

        template<class InputIter, class OutputIter, class BinaryOp>
        OutputIter partial_sum(InputIter first, InputIter last, OutputIter result, BinaryOp binary_op) {
            if (first == last) return result;
            *result = *first;
            auto value = *first;
            while (++first != last) {
                value = binary_op(value, *first);
                *++result = value;
            }
            return ++result;
        }
    }//namespace
};//namespace
