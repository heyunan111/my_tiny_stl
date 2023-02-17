//
// Created by hyn on 2023/2/11.
//

#pragma once

#include <type_traits>

namespace hyn {
    namespace stl {
        namespace {
            template<bool, class Ta, class Tb>
            struct IfThenElse;
            template<class Ta, class Tb>
            struct IfThenElse<true, Ta, Tb> {
                using result = Ta;
            };
            template<class Ta, class Tb>
            struct IfThenElse<false, Ta, Tb> {
                using result = Tb;
            };
        }

        struct _true_type {
        };
        struct _false_type {
        };

        template<class T>
        struct _type_traits {
            typedef _false_type has_trivial_default_constructor;
            typedef _false_type has_trivial_copy_constructor;
            typedef _false_type has_trivial_assignment_operator;
            typedef _false_type has_trivial_destructor;
            typedef _false_type is_POD_type;
        };

        template<>
        struct _type_traits<bool> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<char> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<unsigned char> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<signed char> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<wchar_t> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<short> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<unsigned short> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<int> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<unsigned int> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<long> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<unsigned long> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<long long> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<unsigned long long> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<float> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<double> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<long double> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };

        template<class T>
        struct _type_traits<T *> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<class T>
        struct _type_traits<const T *> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<char *> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<unsigned char *> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<signed char *> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<const char *> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<const unsigned char *> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };
        template<>
        struct _type_traits<const signed char *> {
            typedef _true_type has_trivial_default_constructor;
            typedef _true_type has_trivial_copy_constructor;
            typedef _true_type has_trivial_assignment_operator;
            typedef _true_type has_trivial_destructor;
            typedef _true_type is_POD_type;
        };

        /***********************************************************************************************************/
        template<typename T, T v>
        struct m_integral_constant {
            static constexpr T value = v;
        };

        template<bool T>
        using m_bool_constant = m_integral_constant<bool, T>;
        typedef m_bool_constant<true> m_true_type;
        typedef m_bool_constant<false> m_false_type;
    }//name space stl
}//name space hyn

