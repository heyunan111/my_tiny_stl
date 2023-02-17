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
        /*******************************************************************************************************************************************************/
        //min
        template<class T>
        const T &min(const T &a, const T &b) {
            return a > b ? b : a;
        }

        template<class T, class Comp>
        const T &min(const T &a, const T &b, Comp comp) {
            return comp(b, a) ? b : a;
        }
        /*******************************************************************************************************************************************************/
        // copy

        // input_iterator_tag 版本
        template<class InputIter, class OutputIter>
        OutputIter
        unchecked_copy_cat(InputIter first, InputIter last, OutputIter result,
                           hyn::stl::input_iterator_tag) {
            for (; first != last; ++first, ++result) {
                *result = *first;
            }
            return result;
        }

        // random_access_iterator_tag
        template<class RandomIter, class OutputIter>
        OutputIter
        unchecked_copy_cat(RandomIter first, RandomIter last, OutputIter result,
                           hyn::stl::random_access_iterator_tag) {
            for (auto n = last - first; n > 0; --n, ++first, ++result) {
                *result = *first;
            }
            return result;
        }

        template<class InputIter, class OutputIter>
        OutputIter
        unchecked_copy(InputIter first, InputIter last, OutputIter result) {
            return unchecked_copy_cat(first, last, result, iterator_category(first));
        }

        //trivially_copy_assignable
        template<class T, class U>
        typename std::enable_if<std::is_same<typename std::remove_const<T>::type, U>::value &&
                                std::is_trivially_copy_assignable<U>::value, U *>::type
        unchecked_copy(T *first, T *last, U *res) {
            const auto n = static_cast<size_t>(last - first);
            if (n != 0) {
                std::memmove(res, first, n * sizeof(U));
            }
            return res + n;
        }

        template<class In, class Out>
        Out copy(In first, In last, Out res) {
            return unchecked_copy(first, last, res);
        }
        /*******************************************************************************************************************************************************/
        //copy_backward

        //bidirectional_iterator
        template<class Bid1, class Bid2>
        Bid2 unchecked_copy_backward_cat(Bid1 first, Bid1 last, Bid2 res, bidirectional_iterator_tag) {
            while (first != last) {
                *--res = *last;
            }
            return res;
        }

        //random_access_iterator
        template<class Rand1, class Rand2>
        Rand2 unchecked_copy_backward_cat(Rand1 first, Rand1 last, Rand2 res, random_access_iterator_tag) {
            for (auto i = last - first; i > 0; --i) {
                *--res = *last;
            }
            return res;
        }

        template<class Rand1, class Rand2>
        Rand2 unchecked_copy_backward(Rand1 first, Rand1 last, Rand2 res) {
            return unchecked_copy_backward_cat(first, last, res, iterator_category(first));
        }

        //trivially_copy_assignable
        template<class T, class U>
        typename std::enable_if<std::is_same<typename std::remove_const<T>::type, U>::value &&
                                std::is_trivially_copy_assignable<U>::value, U *>::type
        unchecked_copy_backward(T *first, T *last, U *res) {
            const auto n = static_cast<size_t>(last - first);
            if (n != 0) {
                res -= n;
                std::memmove(res, first, n * sizeof(U));
            }
            return res;
        }

        template<class T, class U>
        U copy_backward(T first, T last, U res) {
            return unchecked_copy_backward(first, last, res);
        }

        //copy_if
        template<class In, class Out, class UnaryPredicate>
        Out copy_if(In first, In last, Out res, UnaryPredicate up) {
            for (; first != last; ++first) {
                if (up(*first)) {
                    *res++ = first;
                }
            }
            return res;
        }
        /*******************************************************************************************************************************************************/
        //copy_n

        //input_iterator
        template<class In, class Out>
        hyn::stl::pair<In, Out> unchecked_copy_n(In first, size_t n, Out res, hyn::stl::input_iterator_tag) {
            for (; n > 0; --n, ++first, ++res) {
                *res = first;
            }
            return hyn::stl::pair<In, Out>(first, res);
        }

        //random_iterator
        template<class In, class Out>
        hyn::stl::pair<In, Out> unchecked_copy_n(In first, size_t n, Out res, hyn::stl::random_access_iterator_tag) {
            auto last = first + n;
            return pair<In, Out>(last, hyn::stl::copy(first, last, res));
        }

        template<class In, class Out>
        hyn::stl::pair<In, Out> copy_n(In first, size_t n, Out res) {
            return unchecked_copy_n(first, n, res);
        }


        /*******************************************************************************************************************************************************/
        //move

        //input_iterator
        template<class In, class Out>
        Out unchecked_move_cat(In first, In last, Out res, hyn::stl::input_iterator_tag) {
            for (; first != last; ++first, ++res) {
                *res = hyn::stl::move(*first);
            }
            return res;
        }

        //random_iterator
        template<class In, class Out>
        Out unchecked_move_cat(In first, In last, Out res, hyn::stl::random_access_iterator_tag) {
            for (auto n = last - first; n > 0; --n, ++first, ++res) {
                *res = hyn::stl::move(*first);
            }
            return res;
        }

        template<class In, class Out>
        Out unchecked_move(In first, In last, Out res) {
            return unchecked_move_cat(first, last, res);
        }

        //trivially_copy_assignable
        //如果T没有const限定，则返回布尔值true，否则返回false  remove_const :: type 去掉const
        //enable_if 只有第一个模板参数为true时，struct 才会定义一个public的type类型（struct成员默认是public类型），type即为第二个模板参数。
        template<class T, class U>
        typename std::enable_if<
                std::is_same<typename std::remove_const<T>::type, U>::value &&
                std::is_trivially_copy_assignable<U>::value, U *>::type
        unchecked_move(T *first, T *last, U *result) {
            const auto n = static_cast<size_t>(last - first);
            if (n != 0)
                std::memmove(result, first, n * sizeof(U));
            return result + n;
        }

        template<class In, class Out>
        Out move(In first, In last, Out res) {
            return unchecked_move(first, last, res);
        }

        /*******************************************************************************************************************************************************/
        //move_backward

        //bidirectional_iterator
        template<class In, class Out>
        Out unchecked_move_backward_cat(In first, In last, Out res, hyn::stl::bidirectional_iterator_tag) {
            while (first != last) {
                *--res = hyn::stl::move(*--last);
            }
            return res;
        }

        //random_access_iterator
        template<class In, class Out>
        Out unchecked_move_backward_cat(In first, In last, Out res, hyn::stl::random_access_iterator_tag) {
            for (auto n = last - first; n > 0; --n) {
                *--res = hyn::stl::move(*--last);
            }
            return res;
        }

        template<class In, class Out>
        Out unchecked_move_backward(In first, In last, Out res) {
            return unchecked_move_backward_cat(first, last, res, hyn::stl::iterator_category(first));
        }

        //trivially_copy_assignable
        template<class T, class U>
        typename std::enable_if<
                std::is_same<typename std::remove_const<T>::type, U>::value &&
                std::is_trivially_copy_assignable<U>::value, U *>::type
        unchecked_move_backward(T *first, T *last, U *res) {
            const auto n = static_cast<size_t>(last - first);
            if (n != 0) {
                res -= n;
                std::memmove(res, first, n * sizeof(U));
            }
            return res;
        }

        template<class In, class Out>
        Out move_backward(In first, In last, Out res) {
            return unchecked_move_backward(first, last, res);
        }

        /*******************************************************************************************************************************************************/
        //equal
        template<class In1, class In2>
        bool equal(In1 first1, In1 last, In2 first2) {
            for (; first1 != last; ++first1, ++first2) {
                if (*first1 != *first2) {
                    return false;
                }
            }
            return true;
        }

        template<class In1, class In2, class Comp>
        bool equal(In1 first1, In1 last, In2 first2, Comp comp) {
            for (; first1 != last; ++first1, ++first2) {
                if (!comp(*first1, *first2)) {
                    return false;
                }
            }
            return true;
        }

        /****************************************************************************************************************************************************************/
        //fill_n
        template<class Out, class size, class T>
        Out unchecked_fill_n(Out first, size n, const T &value) {
            for (; n > 0; --n, ++first) {
                *first = value;
            }
            return first;
        }

        //one-byte
        //memset是计算机中C/C++语言初始化函数。作用是将某一块内存中的内容全部设置为指定的值， 这个函数通常为新申请的内存做初始化工作。
        template<class Out, class size, class T>
        typename std::enable_if<
                std::is_integral<Out>::value && std::is_integral<T>::value && !std::is_same<Out, bool>::value &&
                sizeof(Out) == 1 && sizeof(T) == 1, T *>::type
        unchecked_fill_n(Out first, size n, T value) {
            if (n > 0) {
                std::memset(first, static_cast<unsigned char>(value), static_cast<size_t>(n));
            }
            return first + n;
        }

        template<class Out, class size, class T>
        Out fill_n(Out first, size n, const T &value) {
            return unchecked_fill_n(first, n, value);
        }

        /*******************************************************************************************************************************************************/
        //fill

        //forward_iterator
        template<class Iter, class T>
        void fill_cat(Iter first, Iter last, const T &value, hyn::stl::forward_iterator_tag) {
            for (; first != last; ++first) {
                *first = value;
            }
        }

        //random_access_iterator
        template<class Iter, class T>
        void fill_cat(Iter first, Iter last, const T &value, hyn::stl::random_access_iterator_tag) {
            fill_n(first, last - first, value);
        }

        template<class Iter, class T>
        void fill(Iter first, Iter last, const T &value) {
            fill_cat(first, last, value, hyn::stl::iterator_category(first));
        }

        /*******************************************************************************************************************************************************/

    }//namespace
}//namespace