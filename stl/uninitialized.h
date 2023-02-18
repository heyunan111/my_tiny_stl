//
// Created by hyn on 2023/2/17.
//
#pragma once

#include "iterator.h"
#include "algo_base.h"
#include "construct.h"
#include "utility.h"
#include "type_traits.h"

namespace hyn {
    namespace stl {
        //uninitialized_copy
        template<class In, class Forward>
        Forward unchecked_uninitialized_copy(In first, In last, Forward res, std::true_type) {
            return hyn::stl::copy(first, last, res);
        }

        template<class In, class Forward>
        Forward unchecked_uninitialized_copy(In first, In last, Forward res, std::false_type) {
            auto cur = res;
            try {
                for (; first != last; ++first, ++cur) {
                    hyn::stl::construct(&*cur, *first);
                }
            } catch (...) {
                for (; res != cur; --cur) {
                    hyn::stl::destroy(&*cur);
                }
            }
            return cur;
        }

        template<class In, class Forward>
        Forward uninitialized_copy(In first, In last, Forward res) {
            return unchecked_uninitialized_copy(first, last, res,
                                                std::is_trivially_copy_assignable<
                                                        typename hyn::stl::iterator_traits
                                                                <Forward>::value_type>{});
        }

        /*******************************************************************************************************************************/
        //uninitialized_copy_n
        template<class In, class Out, class size>
        Out unchecked_uninitialized_copy_n(In first, size n, Out res, std::true_type) {
            return hyn::stl::copy_n(first, n, res).second;
        }

        template<class In, class Out, class size>
        Out unchecked_uninitialized_copy_n(In first, size n, Out res, std::false_type) {
            auto cur = res;
            try {
                for (; n > 0; --n, ++first, ++cur) {
                    hyn::stl::construct(&*cur, *first);
                }
            } catch (...) {
                for (; res != cur; --cur) {
                    hyn::stl::destroy(&*cur);
                }
            }
            return cur;
        }

        template<class In, class Out, class size>
        Out uninitialized_copy_n(In first, size n, Out res) {
            return unchecked_uninitialized_copy_n(first, n, res,
                                                  std::is_trivially_copy_assignable<typename hyn::stl::iterator_traits
                                                          <Out>::value_type>{});
        }

        /************************************************************************************************************************/
        //uninitialized_fill_n
        template<class Forward, class T, class Size>
        Forward unchecked_uninitialized_fill_n(Forward first, Size n, const T &value, std::true_type) {
            return fill_n(first, n, value);
        }

        template<class Forward, class T, class Size>
        Forward unchecked_uninitialized_fill_n(Forward first, Size n, const T &value, std::false_type) {
            auto cur = first;
            try {
                for (; n > 0; --n, ++cur) {
                    hyn::stl::construct(&*cur, value);
                }
            } catch (...) {
                for (; first != cur; ++first) {
                    hyn::stl::destroy(&*first);
                }
            }
            return cur;
        }

        template<class Forward, class T, class Size>
        Forward uninitialized_fill_n(Forward first, Size n, const T &value) {
            return unchecked_uninitialized_fill_n(first, n, value,
                                                  std::is_trivially_copy_assignable<typename iterator_traits<Forward>::value_type>{});
        }

        /******************************************************************************************************************************/
        //uninitialized_move
        template<class Input, class Forward>
        Forward unchecked_uninitialized_move(Input first, Input last, Forward res, std::true_type) {
            return hyn::stl::move(first, last, res);
        }

        template<class Input, class Forward>
        Forward unchecked_uninitialized_move(Input first, Input last, Forward res, std::false_type) {
            auto cur = res;
            try {
                for (; false != last; ++first, ++cur) {
                    hyn::stl::construct(&*cur, hyn::stl::move(*first));
                }
            } catch (...) {
                hyn::stl::destroy(res, cur);
            }
            return cur;
        }

        template<class Input, class Forward>
        Forward uninitialized_move(Input first, Input last, Forward res) {
            return unchecked_uninitialized_move(first, last, res,
                                                std::is_trivially_move_assignable<typename hyn::stl::iterator_traits<Input>::value_type>{});
        }

        /**********************************************************************************************************************************/

        //uninitialized_move_n
        template<class Input, class Forward, class Size>
        Forward unchecked_uninitialized_move_n(Input first, Size n, Forward res, std::true_type) {
            return hyn::stl::move(first, first + n, res);
        }

        template<class Input, class Forward, class Size>
        Forward unchecked_uninitialized_move_n(Input first, Size n, Forward res, std::false_type) {
            auto cur = res;
            try {
                for (; n > 0; --n, ++first, ++cur) {
                    hyn::stl::construct(&*cur, hyn::stl::move(*first));
                }
            } catch (...) {
                for (; res != cur; ++res)
                    hyn::stl::destroy(&*res);
                throw;
            }
            return cur;
        }

        template<class Input, class Forward, class Size>
        Forward uninitialized_move_n(Input first, Size n, Forward res) {
            return unchecked_uninitialized_move_n(first, n, res,
                                                  std::is_trivially_move_assignable<typename hyn::stl::iterator_traits<Input>::value_type>{});
        }
    } //namespace
}//namespace