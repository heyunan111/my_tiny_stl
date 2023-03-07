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

        template<class ForwardIter, class size, class T>
        ForwardIter such_n(ForwardIter first, ForwardIter last, size n, const T &value) {
            if (n <= 0) {
                return first;
            } else {
                first = hyn::stl::find(first, last, value);
                while (first != last) {
                    auto m = n - 1;
                    auto i = first;
                    ++i;
                    while (i != last && m != 0 && *i == value) {
                        ++i;
                        --m;
                    }
                    if (m == 0) {
                        return first;
                    } else {
                        first = hyn::stl::find(i, last, value);
                    }
                }
                return last;
            }

        }

        template<class ForwardIter, class Size, class T, class Compared>
        ForwardIter
        search_n(ForwardIter first, ForwardIter last,
                 Size n, const T &value, Compared comp) {
            if (n <= 0) {
                return first;
            } else {
                while (first != last) {
                    if (comp(*first, value))
                        break;
                    ++first;
                }
                while (first != last) {
                    auto m = n - 1;
                    auto i = first;
                    ++i;
                    while (i != last && m != 0 && comp(*i, value)) {
                        ++i;
                        --m;
                    }
                    if (m == 0) {
                        return first;
                    } else {
                        while (i != last) {
                            if (comp(*i, value))
                                break;
                            ++i;
                        }
                        first = i;
                    }
                }
                return last;
            }
        }

        /*****************************************************************************************/
        // find_end

        template<class ForwardIter1, class ForwardIter2>
        ForwardIter1
        find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2,
                          forward_iterator_tag, forward_iterator_tag) {
            if (first2 == last2) {
                return last1;
            } else {
                auto result = last1;
                while (true) {
                    auto new_result = hyn::stl::search(first1, last1, first2, last2);
                    if (new_result == last1) {
                        return last1;
                    } else {
                        result = new_result;
                        first1 = new_result + 1;
                    }
                }
            }
        }

        template<class BidirectionalIter1, class BidirectionalIter2>
        BidirectionalIter1
        find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1,
                          BidirectionalIter2 first2, BidirectionalIter2 last2,
                          bidirectional_iterator_tag, bidirectional_iterator_tag) {
            typedef reverse_iterator<BidirectionalIter1> reviter1;
            typedef reverse_iterator<BidirectionalIter2> reviter2;
            reviter1 rlast1(first1);
            reviter2 rlast2(first2);
            reviter1 rresult = hyn::stl::search(reviter1(last1), rlast1, reviter2(last2), rlast2);
            if (rresult == rlast1) {
                return last1;
            } else {
                auto result = rresult.base();
                hyn::stl::advance(result, -hyn::stl::distance(first2, last2));
                return result;
            }
        }

        template<class ForwardIter1, class ForwardIter2>
        ForwardIter1
        find_end(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2) {
            typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
            typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
            return hyn::stl::find_end_dispatch(first1, last1, first2, last2, Category1(), Category2());
        }

        template<class ForwardIter1, class ForwardIter2, class Compared>
        ForwardIter1
        find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2,
                          forward_iterator_tag, forward_iterator_tag, Compared comp) {
            if (first2 == last2) {
                return last1;
            } else {
                auto result = last1;
                while (true) {
                    // 利用 search 查找某个子序列的首次出现点，找不到则返回 last1
                    auto new_result = hyn::stl::search(first1, last1, first2, last2, comp);
                    if (new_result == last1) {
                        return result;
                    } else {
                        result = new_result;
                        first1 = new_result;
                        ++first1;
                    }
                }
            }
        }

        template<class BidirectionalIter1, class BidirectionalIter2, class Compared>
        BidirectionalIter1
        find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1, BidirectionalIter2 first2,
                          BidirectionalIter2 last2, bidirectional_iterator_tag, bidirectional_iterator_tag,
                          Compared comp) {
            typedef reverse_iterator<BidirectionalIter1> reviter1;
            typedef reverse_iterator<BidirectionalIter2> reviter2;
            reviter1 rlast1(first1);
            reviter2 rlast2(first2);
            reviter1 rresult = hyn::stl::search(reviter1(last1), rlast1, reviter2(last2), rlast2, comp);
            if (rresult == rlast1) {
                return last1;
            } else {
                auto result = rresult.base();
                hyn::stl::advance(result, -hyn::stl::distance(first2, last2));
                return result;
            }
        }

        template<class ForwardIter1, class ForwardIter2, class Compared>
        ForwardIter1
        find_end(ForwardIter1 first1, ForwardIter1 last1,
                 ForwardIter2 first2, ForwardIter2 last2, Compared comp) {
            typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
            typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
            return hyn::stl::find_end_dispatch(first1, last1, first2, last2, Category1(), Category2(), comp);
        }

        /*****************************************************************************************/
        // find_first_of

    }//namespace
}//namespace










