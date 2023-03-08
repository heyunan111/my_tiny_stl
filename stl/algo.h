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

        template<class InputIter, class ForwardIter>
        InputIter
        find_first_of(InputIter first1, InputIter last1, ForwardIter first2, ForwardIter last2) {
            for (; first1 != last1; ++first1) {
                for (auto it = first2; it != last2; ++it) {
                    if (*first1 == *it)
                        return first1;
                }
            }
            return last1;
        }

        template<class InputIter, class ForwardIter, class Compared>
        InputIter
        find_first_of(InputIter first1, InputIter last1,
                      ForwardIter first2, ForwardIter last2, Compared comp) {
            for (; first1 != last1; ++first1) {
                for (auto iter = first2; iter != last2; ++iter) {
                    if (comp(*first1, *iter))
                        return first1;
                }
            }
            return last1;
        }

        /*****************************************************************************************/
        // for_each
        template<class InputIter, class Function>
        Function for_each(InputIter first, InputIter last, Function f) {
            for (; first != last; ++first) {
                f(*first);
            }
            return f;
        }

        /*****************************************************************************************/
        // adjacent_find
        template<class ForwardIter>
        ForwardIter adjacent_find(ForwardIter first, ForwardIter last) {
            if (first == last)
                return last;
            auto next = first;
            while (next != last) {
                if (*first == *last)
                    return first;
                first = next;
            }
            return last;
        }

        template<class ForwardIter, class Compared>
        ForwardIter adjacent_find(ForwardIter first, ForwardIter last, Compared comp) {
            if (first == last) return last;
            auto next = first;
            while (++next != last) {
                if (comp(*first, *next)) return first;
                first = next;
            }
            return last;
        }

        /*****************************************************************************************/
        // lower_bound
        template<class ForwardIter, class T>
        ForwardIter
        lbound_dispatch(ForwardIter first, ForwardIter last, const T &value, forward_iterator_tag) {
            auto len = hyn::stl::distance(first, last);
            auto half = len;
            ForwardIter middle;
            while (len > 0) {
                half = len >> 1;
                middle = first;
                hyn::stl::advance(middle, half);
                if (*middle < value) {
                    first = middle + 1;
                    len = len - half - 1;
                } else {
                    len = half;
                }
            }
            return first;
        }

        template<class RandomIter, class T>
        RandomIter
        lbound_dispatch(RandomIter first, RandomIter last, const T &value, random_access_iterator_tag) {
            auto len = hyn::stl::distance(first, last);
            auto half = len;
            RandomIter middle;
            while (len > 0) {
                half = len >> 1;
                middle = first + half;
                if (*middle < value) {
                    first = middle + 1;
                    len = len - half - 1;
                } else {
                    len = half;
                }
            }
            return first;
        }

        template<class ForwardIter, class T>
        ForwardIter
        lower_bound(ForwardIter first, ForwardIter last, const T &value) {
            return hyn::stl::lbound_dispatch(first, last, value, iterator_category(first));
        }

        template<class ForwardIter, class T, class Compared>
        ForwardIter
        lbound_dispatch(ForwardIter first, ForwardIter last,
                        const T &value, forward_iterator_tag, Compared comp) {
            auto len = hyn::stl::distance(first, last);
            auto half = len;
            ForwardIter middle;
            while (len > 0) {
                half = len >> 1;
                middle = first;
                hyn::stl::advance(middle, half);
                if (comp(*middle, value)) {
                    first = middle;
                    ++first;
                    len = len - half - 1;
                } else {
                    len = half;
                }
            }
            return first;
        }

        template<class RandomIter, class T, class Compared>
        RandomIter
        lbound_dispatch(RandomIter first, RandomIter last,
                        const T &value, random_access_iterator_tag, Compared comp) {
            auto len = last - first;
            auto half = len;
            RandomIter middle;
            while (len > 0) {
                half = len >> 1;
                middle = first + half;
                if (comp(*middle, value)) {
                    first = middle + 1;
                    len = len - half - 1;
                } else {
                    len = half;
                }
            }
            return first;
        }

        template<class ForwardIter, class T, class Compared>
        ForwardIter
        lower_bound(ForwardIter first, ForwardIter last, const T &value, Compared comp) {
            return hyn::stl::lbound_dispatch(first, last, value, iterator_category(first), comp);
        }

        /*****************************************************************************************/
        // upper_bound
        template<class ForwardIter, class T>
        ForwardIter
        ubound_dispatch(ForwardIter first, ForwardIter last, const T &value, forward_iterator_tag) {
            auto len = hyn::stl::distance(first, last);
            auto half = len;
            ForwardIter middle;
            while (len > 0) {
                half = len >> 1;
                middle = first;
                hyn::stl::advance(middle, half);
                if (value < *middle) {
                    len = half;
                } else {
                    first = middle + 1;
                    len = len - half - 1;
                }
            }
            return first;
        }

        template<class RandomIter, class T>
        RandomIter
        ubound_dispatch(RandomIter first, RandomIter last, const T &value, random_access_iterator_tag) {
            auto len = last - first;
            auto half = len;
            RandomIter middle;
            while (len > 0) {
                half = len >> 1;
                middle = first + half;
                if (value < *middle) {
                    len = half;
                } else {
                    first = middle + 1;
                    len = len - half - 1;
                }
            }
            return first;
        }

        template<class ForwardIter, class T>
        ForwardIter
        upper_bound(ForwardIter first, ForwardIter last, const T &value) {
            return hyn::stl::ubound_dispatch(first, last, value, iterator_category(first));
        }

        template<class ForwardIter, class T, class Compared>
        ForwardIter
        ubound_dispatch(ForwardIter first, ForwardIter last,
                        const T &value, forward_iterator_tag, Compared comp) {
            auto len = hyn::stl::distance(first, last);
            auto half = len;
            ForwardIter middle;
            while (len > 0) {
                half = len >> 1;
                middle = first;
                hyn::stl::advance(middle, half);
                if (comp(value, *middle)) {
                    len = half;
                } else {
                    first = middle;
                    ++first;
                    len = len - half - 1;
                }
            }
            return first;
        }

        template<class RandomIter, class T, class Compared>
        RandomIter
        ubound_dispatch(RandomIter first, RandomIter last,
                        const T &value, random_access_iterator_tag, Compared comp) {
            auto len = last - first;
            auto half = len;
            RandomIter middle;
            while (len > 0) {
                half = len >> 1;
                middle = first + half;
                if (comp(value, *middle)) {
                    len = half;
                } else {
                    first = middle + 1;
                    len = len - half - 1;
                }
            }
            return first;
        }

        template<class ForwardIter, class T, class Compared>
        ForwardIter
        upper_bound(ForwardIter first, ForwardIter last, const T &value, Compared comp) {
            return hyn::stl::ubound_dispatch(first, last, value, iterator_category(first), comp);
        }

        /*****************************************************************************************/
        // binary_search
        template<class ForwardIter, class T>
        bool binary_search(ForwardIter first, ForwardIter last, const T &value) {
            auto i = hyn::stl::lower_bound(first, last, value);
            return i != last && !(value < *i);
        }

        template<class ForwardIter, class T, class Comp>
        bool binary_search(ForwardIter first, ForwardIter last, const T &value, Comp comp) {
            auto i = hyn::stl::lower_bound(first, last, value);
            return i != last && !comp(value, *i);
        }

        /*****************************************************************************************/
        // equal_range
        template<class ForwardIter, class T>
        hyn::stl::pair<ForwardIter, ForwardIter>
        erange_dispatch(ForwardIter first, ForwardIter last, const T &value, forward_iterator_tag) {
            auto len = hyn::stl::distance(first, last);
            auto half = len;
            ForwardIter middle, left, right;
            while (len > 0) {
                if (*middle < len) {
                    first = middle + 1;
                    len = len - half - 1;
                } else if (value < *middle) {
                    len = half;
                } else {
                    left = hyn::stl::lower_bound(first, last, value);
                    hyn::stl::advance(first, len);
                    right = hyn::stl::upper_bound(++middle, first, value);
                    return hyn::stl::pair<ForwardIter, ForwardIter>(left, right);
                }
            }
            return hyn::stl::pair<ForwardIter, ForwardIter>(last, last);
        }

        template<class RandomIter, class T>
        hyn::stl::pair<RandomIter, RandomIter>
        erange_dispatch(RandomIter first, RandomIter last,
                        const T &value, random_access_iterator_tag) {
            auto len = last - first;
            auto half = len;
            RandomIter middle, left, right;
            while (len > 0) {
                half = len >> 1;
                middle = first + half;
                if (*middle < value) {
                    first = middle + 1;
                    len = len - half - 1;
                } else if (value < *middle) {
                    len = half;
                } else {
                    left = hyn::stl::lower_bound(first, middle, value);
                    right = hyn::stl::upper_bound(++middle, first + len, value);
                    return hyn::stl::pair<RandomIter, RandomIter>(left, right);
                }
            }
            return hyn::stl::pair<RandomIter, RandomIter>(last, last);
        }

        template<class ForwardIter, class T>
        hyn::stl::pair<ForwardIter, ForwardIter>
        equal_range(ForwardIter first, ForwardIter last, const T &value) {
            return hyn::stl::erange_dispatch(first, last, value, iterator_category(first));
        }

        template<class ForwardIter, class T, class Compared>
        hyn::stl::pair<ForwardIter, ForwardIter>
        erange_dispatch(ForwardIter first, ForwardIter last,
                        const T &value, forward_iterator_tag, Compared comp) {
            auto len = hyn::stl::distance(first, last);
            auto half = len;
            ForwardIter middle, left, right;
            while (len > 0) {
                half = len >> 1;
                middle = first;
                hyn::stl::advance(middle, half);
                if (comp(*middle, value)) {
                    first = middle;
                    ++first;
                    len = len - half - 1;
                } else if (comp(value, *middle)) {
                    len = half;
                } else {
                    left = hyn::stl::lower_bound(first, last, value, comp);
                    hyn::stl::advance(first, len);
                    right = hyn::stl::upper_bound(++middle, first, value, comp);
                    return hyn::stl::pair<ForwardIter, ForwardIter>(left, right);
                }
            }
            return hyn::stl::pair<ForwardIter, ForwardIter>(last, last);
        }

        template<class RandomIter, class T, class Compared>
        hyn::stl::pair<RandomIter, RandomIter>
        erange_dispatch(RandomIter first, RandomIter last,
                        const T &value, random_access_iterator_tag, Compared comp) {
            auto len = last - first;
            auto half = len;
            RandomIter middle, left, right;
            while (len > 0) {
                half = len >> 1;
                middle = first + half;
                if (comp(*middle, value)) {
                    first = middle + 1;
                    len = len - half - 1;
                } else if (comp(value, *middle)) {
                    len = half;
                } else {
                    left = hyn::stl::lower_bound(first, middle, value, comp);
                    right = hyn::stl::upper_bound(++middle, first + len, value, comp);
                    return hyn::stl::pair<RandomIter, RandomIter>(left, right);
                }
            }
            return hyn::stl::pair<RandomIter, RandomIter>(last, last);
        }

        template<class ForwardIter, class T, class Compared>
        hyn::stl::pair<ForwardIter, ForwardIter>
        equal_range(ForwardIter first, ForwardIter last, const T &value, Compared comp) {
            return hyn::stl::erange_dispatch(first, last, value, iterator_category(first), comp);
        }

        /*****************************************************************************************/
        // generate_n

        template<class ForwardIter, class size, class Generator>
        void generate_n(ForwardIter first, size n, Generator gen) {
            for (; n > 0; --n, --first) {
                *first = gen();
            }
        }

        /*****************************************************************************************/
        // includes

        template<class InputIter1, class InputIter2>
        bool includes(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2) {
            while (first1 != last1 && first2 != last2) {
                if (*first2 < *first1) {
                    return false;
                } else if (*first1 < *first2) {
                    ++first1;
                } else {
                    ++first1;
                    ++first2;
                }
            }
            return true;
        }

        template<class InputIter1, class InputIter2, class Comp>
        bool includes(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, Comp comp) {
            while (first1 != last1 && first2 != last2) {
                if (comp(*first2, *first1)) {
                    return false;
                } else if (comp(*first1, *first2)) {
                    ++first1;
                } else {
                    ++first1;
                    ++first2;
                }
            }
            return true;
        }

        /*****************************************************************************************/
        // is_heap
        template<class RandomIter>
        bool is_heap(RandomIter first, RandomIter last) {
            auto n = hyn::stl::distance(first, last);
            auto parent = 0;
            for (auto child = 0; child < n; ++child) {
                if (first[child] > first[parent]) {
                    return false;
                }
                if ((child & 1) == 0) //是偶数
                    ++parent;
            }
            return true;
        }

        template<class RandomIter, class Comp>
        bool is_heap(RandomIter first, RandomIter last, Comp comp) {
            auto n = hyn::stl::distance(first, last);
            auto parent = 0;
            for (auto child = 0; child < n; ++child) {
                if (comp(first[parent], first[child])) {
                    return false;
                }
                if ((child & 1) == 0) //是偶数
                    ++parent;
            }
            return true;
        }

        /*****************************************************************************************/
        // is_sorted
        template<class ForwardIter>
        bool is_sorted(ForwardIter first, ForwardIter last) {
            if (first == last)
                return true;
            auto next = first + 1;
            for (; next != last; first = next, ++next) {
                if (*next < *first)
                    return false;
            }
            return true;
        }

        template<class ForwardIter, class Compared>
        bool is_sorted(ForwardIter first, ForwardIter last, Compared comp) {
            if (first == last)
                return true;
            auto next = first;
            ++next;
            for (; next != last; first = next, ++next) {
                if (comp(*next, *first))
                    return false;
            }
            return true;
        }

        /*****************************************************************************************/
        // median
        template<class T>
        const T &median(const T &left, const T &mid, const T &right) {
            if (left < mid)
                if (mid < right)        // left < mid < right
                    return mid;
                else if (left < right)  // left < right <= mid
                    return right;
                else                    // right <= left < mid
                    return left;
            else if (left < right)      // mid <= left < right
                return left;
            else if (mid < right)       // mid < right <= left
                return right;
            else                        // right <= mid <= left
                return mid;
        }

        template<class T, class Compared>
        const T &median(const T &left, const T &mid, const T &right, Compared comp) {
            if (comp(left, mid))
                if (comp(mid, right))
                    return mid;
                else if (comp(left, right))
                    return right;
                else
                    return left;
            else if (comp(left, right))
                return left;
            else if (comp(mid, right))
                return right;
            else
                return mid;
        }

        /*****************************************************************************************/
        // max_element
        template<class ForwardIter>
        ForwardIter max_element(ForwardIter first, ForwardIter last) {
            if (first == last)
                return first;
            auto result = first;
            while (++first != last) {
                if (*result < *first)
                    result = first;
            }
            return result;
        }

        template<class ForwardIter, class Compared>
        ForwardIter max_element(ForwardIter first, ForwardIter last, Compared comp) {
            if (first == last)
                return first;
            auto result = first;
            while (++first != last) {
                if (comp(*result, *first))
                    result = first;
            }
            return result;
        }

        /*****************************************************************************************/
        // min_element

        template<class ForwardIter>
        ForwardIter min_elememt(ForwardIter first, ForwardIter last) {
            if (first == last)
                return first;
            auto result = first;
            while (++first != last) {
                if (*first < *result)
                    result = first;
            }
            return result;
        }

        template<class ForwardIter, class Compared>
        ForwardIter min_elememt(ForwardIter first, ForwardIter last, Compared comp) {
            if (first == last)
                return first;
            auto result = first;
            while (++first != last) {
                if (comp(*first, *result))
                    result = first;
            }
            return result;
        }

        /*****************************************************************************************/
        // swap_ranges
        template<class ForwardIter1, class ForwardIter2>
        ForwardIter2 swap_ranges(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2) {
            for (; first1 != last1; ++first1, ++first2) {
                hyn::stl::iter_swap(first1, first2);
            }
            return first2;
        }

        /*****************************************************************************************/
        // transform
        template<class InputIter, class OutputIter, class UnaryOperation>
        OutputIter transform(InputIter first, InputIter last, OutputIter result, UnaryOperation unary_op) {
            for (; first != last; ++first, ++result) {
                *result = unary_op(*first);
            }
            return result;
        }

        template<class InputIter1, class InputIter2, class OutputIter, class BinaryOperation>
        OutputIter
        transform(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result,
                  BinaryOperation binary_op) {
            for (; first1 != last1; ++first1, ++first2, ++result) {
                *result = binary_op(*first1, *first2);
            }
            return result;
        }

        /*****************************************************************************************/
        // remove_copy
        template<class InputIter, class OutputIter, class T>
        OutputIter remove_copy(InputIter first, InputIter last, OutputIter result, const T &value) {
            for (; first != last; ++first) {
                if (*first != value) {
                    *result++ = *first;
                }
            }
            return result;
        }
    }//namespace
}//namespace










