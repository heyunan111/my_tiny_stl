//
// Created by hyn on 2023/3/1.
//

#pragma once

#include "iterator.h"
#include "algo_base.h"

namespace hyn {
    namespace stl {
        //set_union
        template<class InputIter1, class InputIter2, class OutputIter>
        OutputIter
        set_union(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result) {
            while (first1 != last1 && first2 != last2) {
                if (*first1 < *first2) {
                    *result = *first1;
                    ++first1;
                } else if (*first2 < *first1) {
                    *result = *first2;
                    ++first2;
                } else {
                    *result = *first1;
                    ++first1;
                    ++first2;
                }
                ++result;
            }
            return hyn::stl::copy(first2, last2, copy(first1, first2, result));
        }

        template<class InputIter1, class InputIter2, class OutputIter, class Compared>
        OutputIter
        set_union(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result,
                  Compared comp) {
            while (first1 != last1 && first2 != last2) {
                if (comp(*first1, *first2)) {
                    *result = *first1;
                    ++first1;
                } else if (comp(*first2, *first1)) {
                    *result = *first2;
                    ++first2;
                } else {
                    *result = *first1;
                    ++first1;
                    ++first2;
                }
                ++result;
            }
            return hyn::stl::copy(first2, last2, hyn::stl::copy(first1, last1, result));
        }

        /**********************************************************************************************************/
        //set_intersection
        template<class InputIter1, class InputIter2, class OutputIter>
        OutputIter
        set_intersection(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result) {
            while (first1 != last1 && first2 != last2) {
                if (*first1 < *first2) {
                    ++first1;
                } else if (*first2 < *first1) {
                    ++first2;
                } else {
                    *result = *first1;
                    ++first1;
                    ++first2;
                    ++result;
                }
            }
            return result;
        }

        template<class InputIter1, class InputIter2, class OutputIter, class Compared>
        OutputIter
        set_intersection(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result,
                         Compared comp) {
            while (first1 != last1 && first2 != last2) {
                if (comp(*first1, *first2)) {
                    ++first1;
                } else if (comp(*first2, *first1)) {
                    ++first2;
                } else {
                    *result = *first1;
                    ++first1;
                    ++first2;
                    ++result;
                }
            }
            return result;
        }

        /**********************************************************************************************************/
        //set_difference
        template<class InputIter1, class InputIter2, class OutputIter>
        OutputIter
        set_difference(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result) {
            while (first1 != last1 && first2 != last2) {
                if (*first1 < *first2) {
                    *result = *first1;
                    ++first1;
                    ++result;
                } else if (*first2 < *first1) {
                    ++first2;
                } else {
                    ++first1;
                    ++first2;
                }
            }
            return hyn::stl::copy(first1, last1, result);
        }

        template<class InputIter1, class InputIter2, class OutputIter, class Compared>
        OutputIter
        set_difference(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result,
                       Compared comp) {
            while (first1 != last1 && first2 != last2) {
                if (comp(*first1, *first2)) {
                    *result = *first1;
                    ++first1;
                    ++result;
                } else if (comp(*first2, *first1)) {
                    ++first2;
                } else {
                    ++first1;
                    ++first2;
                }
            }
            return hyn::stl::copy(first1, last1, result);
        }

        /*****************************************************************************************/
        // set_symmetric_difference

        template<class InputIter1, class InputIter2, class OutputIter>
        OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2,
                                            OutputIter result) {
            while (first1 != last1 && first2 != last2) {
                if (*first1 < *first2) {
                    *result = *first1;
                    ++first1;
                    ++result;
                } else if (*first2 < *first1) {
                    *result = *first2;
                    ++first2;
                    ++result;
                } else {
                    ++first1;
                    ++first2;
                }
            }
            return hyn::stl::copy(first2, last2, hyn::stl::copy(first1, last1, result));
        }

        template<class InputIter1, class InputIter2, class OutputIter, class Compared>
        OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2,
                                            OutputIter result, Compared comp) {
            while (first1 != last1 && first2 != last2) {
                if (comp(*first1, *first2)) {
                    *result = *first1;
                    ++first1;
                    ++result;
                } else if (comp(*first2, *first1)) {
                    *result = *first2;
                    ++first2;
                    ++result;
                } else {
                    ++first1;
                    ++first2;
                }
            }
            return hyn::stl::copy(first2, last2, hyn::stl::copy(first1, last1, result));
        }

    }//namespace
}//namespace