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
        ForwardIter2 swap_ranges(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2) {
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

        /*****************************************************************************************/
        // remove

        template<class ForwardIter, class T>
        ForwardIter remove(ForwardIter first, ForwardIter last, const T &value) {
            first = hyn::stl::find(first, last, value);
            auto next = first;
            return first == last ? first : hyn::stl::remove_copy(++next, last, first, value);
        }

        /*****************************************************************************************/
        // remove_copy_if
        template<class InputIter, class OutputIter, class UnaryPredicate>
        OutputIter
        remove_copy_if(InputIter first, InputIter last,
                       OutputIter result, UnaryPredicate unary_pred) {
            for (; first != last; ++first) {
                if (!unary_pred(*first)) {
                    *result = *first;
                    ++result;
                }
            }
            return result;
        }

        /*****************************************************************************************/
        // remove_if
        template<class ForwardIter, class UnaryPredicate>
        ForwardIter remove_if(ForwardIter first, ForwardIter last, UnaryPredicate unary_op) {
            first = hyn::stl::find_if(first, last, unary_op);
            auto next = first;
            return first == last ? first : hyn::stl::remove_copy_if(++next, last, first, unary_op);
        }

        /*****************************************************************************************/
        // replace
        template<class ForwardIter, class T>
        void replace(ForwardIter first, ForwardIter last, const T &old_value, const T &new_value) {
            for (; first != last; ++first) {
                if (*first == old_value) {
                    *first = new_value;
                }
            }
        }

        /*****************************************************************************************/
        // replace_copy
        template<class InputIter, class OutputIter, class T>
        OutputIter
        replace_copy(InputIter first, InputIter last, OutputIter result, const T &old_value, const T &new_value) {
            for (; first != last; ++first, ++result) {
                *result = *first == old_value ? new_value : *first;
            }
            return result;
        }

        /*****************************************************************************************/
        // replace_copy_if
        template<class InputIter, class OutputIter, class UnaryPredicate, class T>
        OutputIter
        replace_copy_if(InputIter first, InputIter last,
                        OutputIter result, UnaryPredicate unary_pred, const T &new_value) {
            for (; first != last; ++first, ++result) {
                *result = unary_pred(*first) ? new_value : *first;
            }
            return result;
        }

        /*****************************************************************************************/
        // replace_if
        template<class ForwardIter, class UnaryPredicate, class T>
        void replace_if(ForwardIter first, ForwardIter last, const T &value, UnaryPredicate unary_op) {
            for (; first != last; ++first) {
                if (unary_op(*first))
                    *first = value;
            }
        }

        /*****************************************************************************************/
        // reverse
        template<class BidirectionalIter>
        void reverse_dispatch(BidirectionalIter first, BidirectionalIter last, bidirectional_iterator_tag) {
            while (true) {
                if (first == last || first == --last) {
                    return;
                }
                hyn::stl::iter_swap(first++, last);
            }
        }

        template<class RandomIter>
        void reverse_dispatch(RandomIter first, RandomIter last, random_access_iterator_tag) {
            while (first < last) {
                hyn::stl::iter_swap(first++, --last);
            }
        }

        template<class RandomIter>
        void reverse(RandomIter first, RandomIter last) {
            hyn::stl::reverse_dispatch(first, last, iterator_category(first));
        }

        /*****************************************************************************************/
        // reverse_copy
        template<class BidirectionalIter, class OutputIter>
        OutputIter reverse_copy(BidirectionalIter first, BidirectionalIter last, OutputIter result) {
            while (first != last) {
                --last;
                *result = *last;
                ++result;
            }
            return result;
        }

        /*****************************************************************************************/
        // random_shuffle

        template<class RandomIter>
        void random_shuffle(RandomIter first, RandomIter last) {
            if (first == last)
                return;
            srand((unsigned) time(0));
            for (auto i = first + 1; i != last; ++i) {
                hyn::stl::iter_swap(i, first + (rand() % (i - first + 1)));
            }
        }

        template<class RandomIter, class RandomNumberGenerator>
        void random_shuffle(RandomIter first, RandomIter last, RandomNumberGenerator &rand) {
            if (first == last)
                return;
            auto len = hyn::stl::distance(first, last);
            for (auto it = first + 1; it != last; ++it) {
                hyn::stl::iter_swap(it, first + rand(it - first + 1) % len);
            }
        }

        /*****************************************************************************************/
        // rotate
        template<class ForwardIter>
        ForwardIter rotate_dispatch(ForwardIter first, ForwardIter middle, ForwardIter last, forward_iterator_tag) {
            auto first2 = middle;
            do {
                hyn::stl::swap(*first++, *first2++);
                if (middle == first)
                    middle = first2;
            } while (first2 != last);

            auto new_middle = first;
            first2 = middle;
            while (first2 != last) {
                hyn::stl::swap(*first++, *first2++);
                if (first == middle) {
                    middle = first2;
                } else if (first2 == last) {
                    first2 = middle;
                }
            }
            return new_middle;
        }

        template<class BidirectionalIter>
        BidirectionalIter rotate_dispatch(BidirectionalIter first, BidirectionalIter middle, BidirectionalIter last,
                                          bidirectional_iterator_tag) {
            hyn::stl::reverse_dispatch(first, middle, bidirectional_iterator_tag());
            hyn::stl::reverse_dispatch(middle, last, bidirectional_iterator_tag());
            while (first != middle && last != middle) {
                hyn::stl::swap(*first++, --*last);
                if (first == middle) {
                    hyn::stl::reverse_dispatch(middle, last, bidirectional_iterator_tag());
                    return last;
                } else {
                    hyn::stl::reverse_dispatch(first, middle, bidirectional_iterator_tag());
                    return first;
                }
            }
        }

        // 求最大公因子
        template<class EuclideanRingElement>
        EuclideanRingElement rgcd(EuclideanRingElement m, EuclideanRingElement n) {
            while (n != 0) {
                auto t = m % n;
                m = n;
                n = t;
            }
            return m;
        }

        template<class RandomIter>
        RandomIter rotate_dispatch(RandomIter first, RandomIter middle, RandomIter last, random_access_iterator_tag) {
            auto n = last - first;
            auto l = middle - first;
            auto r = n - 1;
            auto result = first + (last - middle);
            if (l == r) {
                hyn::stl::swap_ranges(first, last, middle);
                return result;
            }
            auto cycle_times = rgcd(n, l);
            for (auto i = 0; i < cycle_times; ++i) {
                auto tmp = *first;
                auto p = first;
                if (l < r) {
                    for (auto j = 0; j < r / cycle_times; ++j) {
                        if (p > first + r) {
                            *p = *(p - r);
                            p -= r;
                        }
                        *p = *(p + l);
                        p += l;
                    }
                } else {
                    for (auto j = 0; j < l / cycle_times - 1; ++j) {
                        if (p < last - l) {
                            *p = *(p + l);
                            p += l;
                        }
                        *p = *(p - r);
                        p -= r;
                    }
                }
                *p = tmp;
                ++first;
            }
            return result;
        }

        template<class ForwardIter>
        ForwardIter rotate(ForwardIter first, ForwardIter middle, ForwardIter last) {
            if (first == last)
                return last;
            if (middle == last)
                return first;
            return hyn::stl::rotate_dispatch(first, middle, last, hyn::stl::iterator_category(first));
        }

        /*****************************************************************************************/
        // rotate_copy
        template<class ForwardIter, class OutputIter>
        OutputIter rotate_copy(ForwardIter first, ForwardIter middle, ForwardIter last, OutputIter result) {
            return hyn::stl::copy(first, middle, hyn::stl::copy(middle, last, result));
        }

        /*****************************************************************************************/
        // is_permutation
        template<class ForwardIter1, class ForwardIter2, class BinaryPred>
        bool is_permutation_aux(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2,
                                BinaryPred pre) {
            constexpr bool is_ra_it = hyn::stl::is_random_access_iterator<ForwardIter1>::value &&
                                      hyn::stl::is_random_access_iterator<ForwardIter2>::value;
            if (is_ra_it) {
                auto len1 = last1 - first1;
                auto len2 = last2 - first2;
                if (len1 != len2)
                    return false;
            }

            for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
                if (!pre(*first1, *first2))
                    break;
            }

            if (is_ra_it) {
                if (first1 == last1)
                    return true;
            } else {
                auto len1 = hyn::stl::distance(first1, last1);
                auto len2 = hyn::stl::distance(first2, last2);
                if (len1 == 0 && len2 == 0) {
                    return true;
                }
                if (len1 != len2)
                    return false;
            }

            for (auto i = first1; i != last1; ++i) {
                bool is_repeated = false;
                for (auto j = first1; j != i; ++j) {
                    if (pre(*j, *i)) {
                        is_repeated = true;
                        break;
                    }
                }

                if (!is_repeated) {
                    auto c2 = 0;
                    for (auto j = first2; j != last2; ++j) {
                        if (pre(*i, *j))
                            ++c2;
                    }

                    if (c2 == 0)
                        return false;

                    auto c1 = 0;
                    auto j = i + 1;
                    for (; j != last1; ++j) {
                        if (pre(*i, *j)) {
                            ++c1;
                        }
                    }

                    if (c1 != c2)
                        return false;
                }
            }

            return true;
        }

        template<class ForwardIter1, class ForwardIter2, class BinaryPred>
        bool is_permutation(ForwardIter1 f1, ForwardIter1 l1, ForwardIter2 f2, ForwardIter2 l2, BinaryPred pred) {
            return is_permutation_aux(f1, l1, f2, l2, pred);
        }

        template<class ForwardIter1, class ForwardIter2>
        bool is_permutation(ForwardIter1 f1, ForwardIter1 l1, ForwardIter2 f2, ForwardIter1 l2) {
            typedef typename iterator_traits<ForwardIter1>::value_type v1;
            typedef typename iterator_traits<ForwardIter2>::value_type v2;
            static_assert(std::is_same<v1, v2>::value, "the type should be same in is_permutation");
            return is_permutation_aux(f1, l1, f2, l2, hyn::stl::equal_to<v1>());
        }

        /*****************************************************************************************/
        // next_permutation

        template<class BidirectionalIter>
        bool next_permutation(BidirectionalIter first, BidirectionalIter last) {
            auto i = last;
            if (first == last || first == --i)
                return false;
            for (;;) {
                auto ii = i;
                if (*--i < *ii) {
                    auto j = last;
                    while (!(*i < *--j)) {}
                    hyn::stl::iter_swap(i, j);
                    hyn::stl::reverse(ii, last);
                    return true;
                }
                if (i == first) {
                    hyn::stl::reverse(first, last);
                    return false;
                }
            }
        }

        template<class BidirectionalIter, class Compared>
        bool next_permutation(BidirectionalIter first, BidirectionalIter last, Compared comp) {
            auto i = last;
            if (first == last || first == --i)
                return false;
            for (;;) {
                auto ii = i;
                if (comp(*--i, *ii)) {
                    auto j = last;
                    while (!comp(*i, *--j)) {}
                    hyn::stl::iter_swap(i, j);
                    hyn::stl::reverse(ii, last);
                    return true;
                }
                if (i == first) {
                    hyn::stl::reverse(first, last);
                    return false;
                }
            }
        }

        /*****************************************************************************************/
        // merge
        template<class InputIter1, class InputIter2, class OutputITer>
        OutputITer merge(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputITer result) {
            while (first1 != last1 && first2 != last2) {
                if (*first2 < *first1) {
                    *result = *first2;
                    ++first2;
                } else {
                    *result = *first1;
                    ++first1;
                }
                ++result;
            }
            return hyn::stl::copy(first2, last2, hyn::stl::copy(first1, last1, result));
        }

        template<class InputIter1, class InputIter2, class OutputIter, class Compared>
        OutputIter
        merge(InputIter1 first1, InputIter1 last1,
              InputIter2 first2, InputIter2 last2,
              OutputIter result, Compared comp) {
            while (first1 != last1 && first2 != last2) {
                if (comp(*first2, *first1)) {
                    *result = *first2;
                    ++first2;
                } else {
                    *result = *first1;
                    ++first1;
                }
                ++result;
            }
            return hyn::stl::copy(first2, last2, hyn::stl::copy(first1, last1, result));
        }

        /*****************************************************************************************/
        // inplace_merge
        template<class BidirectionalIter, class Distance>
        void
        merge_without_buffer(BidirectionalIter first, BidirectionalIter middle, BidirectionalIter last, Distance len1,
                             Distance len2) {
            if (len1 == 0 || len2 == 0)
                return;

            if (len1 + len2 == 2) {
                if (*middle < *first)
                    hyn::stl::iter_swap(first, middle);
                return;
            }

            auto first_cut = first;
            auto second_cut = middle;
            Distance len11 = 0;
            Distance len22 = 0;

            if (len1 > len2) {
                len11 = len1 >> 1;
                hyn::stl::advance(first_cut, len11);
                second_cut = hyn::stl::lower_bound(middle, last, *first);
                len22 = hyn::stl::distance(middle, second_cut);
            } else {
                len22 = len2 >> 1;
                hyn::stl::advance(second_cut, len22);
                first_cut = hyn::stl::lower_bound(first, middle, *second_cut);
                len22 = hyn::stl::advance(first, first_cut);
            }

            auto new_middle = hyn::stl::rotate(first_cut, middle, second_cut);
            hyn::stl::merge_without_buffer(first, first_cut, new_middle, len11, len22);
            hyn::stl::merge_without_buffer(new_middle, second_cut, last, len1 - len11, len2 - len22);
        }

        template<class BidirectionalIter1, class BidirectionalIter2>
        BidirectionalIter1
        merge_backward(BidirectionalIter1 first1, BidirectionalIter1 last1, BidirectionalIter2 first2,
                       BidirectionalIter2 last2, BidirectionalIter1 result) {
            if (first1 == last1)
                return hyn::stl::copy_backward(first2, last2, result);
            if (first2 == last2)
                return hyn::stl::copy_backward(first1, last1, result);

            --last1;
            --last2;

            while (true) {
                if (*last1 < *last2) {
                    *--result = *last1;
                    if (first1 == last1)
                        return hyn::stl::copy_backward(first2, ++last2, result);
                    --last1;
                } else {
                    *--result = *last2;
                    if (first2 == last2)
                        return hyn::stl::copy_backward(first1, ++last1, result);
                    --last2;
                }
            }

        }

        template<class BidirectionalIter1, class BidirectionalIter2, class Distance>
        BidirectionalIter1
        rotate_adaptive(BidirectionalIter1 first, BidirectionalIter1 middle, BidirectionalIter2 last,
                        Distance len1, Distance len2, BidirectionalIter2 buffer, Distance buffer_size) {
            BidirectionalIter2 buffer_end;
            if (len1 > len2 && len2 <= buffer_size) {
                buffer_end = hyn::stl::copy(middle, last, buffer);
                hyn::stl::copy_backward(first, middle, last);
                return hyn::stl::copy(buffer, buffer_end, first);
            } else if (len1 <= buffer_size) {
                buffer_end = hyn::stl::copy(first, middle, buffer);
                hyn::stl::copy_backward(middle, last, first);
                return hyn::stl::copy(buffer, buffer_end, last);
            } else {
                return hyn::stl::rotate(first, middle, last);
            }
        }

        template<class BidirectionalIter, class Distance, class Pointer>
        void merge_adaptive(BidirectionalIter first, BidirectionalIter middle, BidirectionalIter last, Distance len1,
                            Distance len2, Pointer buffer, Distance buffer_size) {
            if (len1 <= len2 && len1 <= buffer_size) {
                Pointer buffer_end = hyn::stl::copy(first, middle, buffer);
                hyn::stl::merge(buffer, buffer_end, middle, last, first);
            } else if (len2 <= buffer_size) {
                Pointer buffer_end = hyn::stl::copy(middle, last, buffer);
                hyn::stl::merge_backward(first, middle, buffer, buffer_end, last);
            } else {
                auto first_cut = first;
                auto second_cut = middle;
                Distance len11 = 0;
                Distance len22 = 0;

                if (len1 > len2) {
                    len11 = len1 >> 1;
                    hyn::stl::advance(first_cut, len11);
                    second_cut = hyn::stl::lower_bound(middle, last, *first_cut);
                    len22 = hyn::stl::distance(middle, second_cut);
                } else {
                    len22 = len2 >> 1;
                    hyn::stl::advance(second_cut, len22);
                    first_cut = hyn::stl::upper_bound(first, middle, *second_cut);
                    len11 = hyn::stl::distance(first, first_cut);
                }
                auto new_middle = hyn::stl::rotate_adaptive(first_cut, middle, second_cut, len1 - len11, len22, buffer,
                                                            buffer_size);

                hyn::stl::merge_adaptive(first, first_cut, new_middle, len11, len22, buffer, buffer_size);

                hyn::stl::merge_adaptive(new_middle, second_cut, last, len1 - len11, len2 - len22, buffer, buffer_size);
            }
        }

        template<class BidirectionalIter, class T>
        void
        inplace_merge_aux(BidirectionalIter first, BidirectionalIter middle,
                          BidirectionalIter last, T *) {
            auto len1 = hyn::stl::distance(first, middle);
            auto len2 = hyn::stl::distance(middle, last);
            temporary_buffer<BidirectionalIter, T> buf(first, last);
            if (!buf.begin()) {
                hyn::stl::merge_without_buffer(first, middle, last, len1, len2);
            } else {
                hyn::stl::merge_adaptive(first, middle, last, len1, len2, buf.begin(), buf.size());
            }
        }

        template<class BidirectionalIter>
        void
        inplace_merge(BidirectionalIter first, BidirectionalIter middle,
                      BidirectionalIter last) {
            if (first == middle || middle == last)
                return;
            hyn::stl::inplace_merge_aux(first, middle, last, value_type(first));
        }

        template<class BidirectionalIter, class Distance, class Compared>
        void merge_without_buffer(BidirectionalIter first, BidirectionalIter middle,
                                  BidirectionalIter last, Distance len1, Distance len2,
                                  Compared comp) {
            if (len1 == 0 || len2 == 0)
                return;
            if (len1 + len2 == 2) {
                if (comp(*middle, *first))
                    hyn::stl::iter_swap(first, middle);
                return;
            }
            auto first_cut = first;
            auto second_cut = middle;
            Distance len11 = 0;
            Distance len22 = 0;
            if (len1 > len2) {
                len11 = len1 >> 1;
                hyn::stl::advance(first_cut, len11);
                second_cut = hyn::stl::lower_bound(middle, last, *first_cut, comp);
                len22 = hyn::stl::distance(middle, second_cut);
            } else {
                len22 = len2 >> 1;
                hyn::stl::advance(second_cut, len22);
                first_cut = hyn::stl::upper_bound(first, middle, *second_cut, comp);
                len11 = hyn::stl::distance(first, first_cut);
            }
            auto new_middle = hyn::stl::rotate(first_cut, middle, second_cut);
            hyn::stl::merge_without_buffer(first, first_cut, new_middle, len11, len22, comp);
            hyn::stl::merge_without_buffer(new_middle, second_cut, last, len1 - len11, len2 - len22, comp);
        }

        template<class BidirectionalIter1, class BidirectionalIter2, class Compared>
        BidirectionalIter1
        merge_backward(BidirectionalIter1 first1, BidirectionalIter1 last1,
                       BidirectionalIter2 first2, BidirectionalIter2 last2,
                       BidirectionalIter1 result, Compared comp) {
            if (first1 == last1)
                return hyn::stl::copy_backward(first2, last2, result);
            if (first2 == last2)
                return hyn::stl::copy_backward(first1, last1, result);
            --last1;
            --last2;
            while (true) {
                if (comp(*last2, *last1)) {
                    *--result = *last1;
                    if (first1 == last1)
                        return hyn::stl::copy_backward(first2, ++last2, result);
                    --last1;
                } else {
                    *--result = *last2;
                    if (first2 == last2)
                        return hyn::stl::copy_backward(first1, ++last1, result);
                    --last2;
                }
            }
        }

        template<class BidirectionalIter, class Distance, class Pointer, class Compared>
        void merge_adaptive(BidirectionalIter first, BidirectionalIter middle,
                            BidirectionalIter last, Distance len1, Distance len2,
                            Pointer buffer, Distance buffer_size, Compared comp) {
            if (len1 <= len2 && len1 <= buffer_size) {
                Pointer buffer_end = hyn::stl::copy(first, middle, buffer);
                hyn::stl::merge(buffer, buffer_end, middle, last, first, comp);
            } else if (len2 <= buffer_size) {
                Pointer buffer_end = hyn::stl::copy(middle, last, buffer);
                hyn::stl::merge_backward(first, middle, buffer, buffer_end, last, comp);
            } else {
                auto first_cut = first;
                auto second_cut = middle;
                Distance len11 = 0;
                Distance len22 = 0;
                if (len1 > len2) {
                    len11 = len1 >> 1;
                    hyn::stl::advance(first_cut, len11);
                    second_cut = hyn::stl::lower_bound(middle, last, *first_cut, comp);
                    len22 = hyn::stl::distance(middle, second_cut);
                } else {
                    len22 = len2 >> 1;
                    hyn::stl::advance(second_cut, len22);
                    first_cut = hyn::stl::upper_bound(first, middle, *second_cut, comp);
                    len11 = hyn::stl::distance(first, first_cut);
                }
                auto new_middle = hyn::stl::rotate_adaptive(first_cut, middle, second_cut, len1 - len11,
                                                            len22, buffer, buffer_size);
                hyn::stl::merge_adaptive(first, first_cut, new_middle, len11,
                                         len22, buffer, buffer_size, comp);
                hyn::stl::merge_adaptive(new_middle, second_cut, last, len1 - len11,
                                         len2 - len22, buffer, buffer_size, comp);
            }
        }

        template<class BidirectionalIter, class T, class Compared>
        void
        inplace_merge_aux(BidirectionalIter first, BidirectionalIter middle,
                          BidirectionalIter last, T *, Compared comp) {
            auto len1 = hyn::stl::distance(first, middle);
            auto len2 = hyn::stl::distance(middle, last);
            temporary_buffer<BidirectionalIter, T> buf(first, last);
            if (!buf.begin()) {
                hyn::stl::merge_without_buffer(first, middle, last, len1, len2, comp);
            } else {
                hyn::stl::merge_adaptive(first, middle, last, len1, len2, buf.begin(), buf.size(), comp);
            }
        }

        template<class BidirectionalIter, class Compared>
        void
        inplace_merge(BidirectionalIter first, BidirectionalIter middle,
                      BidirectionalIter last, Compared comp) {
            if (first == middle || middle == last)
                return;
            hyn::stl::inplace_merge_aux(first, middle, last, value_type(first), comp);
        }
    }//namespace
}//namespace










