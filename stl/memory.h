//
// Created by hyn on 2023/2/18.
//
#pragma once

#include <cstddef>
#include <cstdlib>
#include <climits>
#include <limits>

#include "algo_base.h"
#include "allocator.h"
#include "construct.h"
#include "uninitialized.h"

namespace hyn {
    namespace stl {

        template<class T>
        constexpr T *address_of(T &value) noexcept {
            return &value;
        }

        template<class T>
        hyn::stl::pair<T *, ptrdiff_t> get_buffer_helper(ptrdiff_t len, T *) {
            if (len > static_cast<ptrdiff_t>(std::numeric_limits<int>::max() / sizeof(T)))
                len = std::numeric_limits<int>::max() / sizeof(T);
            while (len > 0) {
                T *temp = static_cast<T *>(malloc(static_cast<size_t>(len) * sizeof(T)));
                if (temp)
                    return hyn::stl::pair<T *, ptrdiff_t>(temp, len);
                len /= 2;
            }
            return hyn::stl::pair<T *, ptrdiff_t>(nullptr, 0);
        }

        template<class T>
        hyn::stl::pair<T *, ptrdiff_t> get_temporary_buffer(ptrdiff_t len) {
            return get_buffer_helper(len, static_cast<T *>(0));
        }

        template<class T>
        hyn::stl::pair<T *, ptrdiff_t> get_temporary_buffer(ptrdiff_t len, T *) {
            return get_buffer_helper(len, static_cast<T *>(0));
        }

        template<class T>
        void release_temporary_buffer(T *ptr) {
            free(ptr);
        }

        /*************************************************************************************************************************/
        //temporary_buffer 缓冲区的申请与释放
        template<class T, class ForwardIterator>
        class temporary_buffer {
        private:
            ptrdiff_t original_len{}; //缓冲区申请大小
            ptrdiff_t len{};          //缓冲区实际大小
            T *buffer;              //指向缓冲区的指针
        public:
            temporary_buffer(ForwardIterator first, ForwardIterator last);

            ~temporary_buffer() {
                hyn::stl::destroy(buffer, buffer + len);
                free(buffer);
            }

            ptrdiff_t size() const noexcept {
                return len;
            }

            ptrdiff_t requested_size() const noexcept {
                return original_len;
            }

            T *begin() noexcept {
                return buffer;
            }

            T *end() noexcept {
                return buffer + len;
            }

        private:
            void allocate_buff();

            void initialize_buffer(const T &, std::true_type) {}

            void initialize_buffer(const T &value, std::false_type) {
                hyn::stl::uninitialized_fill_n(buffer, len, value);
            }

        public:

            temporary_buffer(const temporary_buffer &) = delete;

            void operator=(const temporary_buffer &) = delete;
        };

        template<class T, class ForwardIterator>
        void temporary_buffer<T, ForwardIterator>::allocate_buff() {
            original_len = len;
            if (len > static_cast<ptrdiff_t>(std::numeric_limits<int>::max() / sizeof(T)))
                len = std::numeric_limits<int>::max() / sizeof(T);
            while (len > 0) {
                buffer = static_cast<T *>(malloc(len * sizeof(T)));
                if (buffer)
                    break;
                len /= 2;
            }
        }

        template<class T, class ForwardIterator>
        temporary_buffer<T, ForwardIterator>::temporary_buffer(ForwardIterator first, ForwardIterator last) {
            try {
                len = hyn::stl::distance(first, last);
                allocate_buff();
                if (len > 0) {
                    initialize_buffer(*first, std::is_trivially_default_constructible<T>());
                }
            } catch (...) {
                free(buffer);
                buffer = nullptr;
                len = 0;
            }
        }

        /*****************************************************************************************************/
        //auto ptr
        template<class T>
        class auto_ptr {
        public:
            typedef T elem_type;
        private:
            T *m_ptr;
        public:
            T *get() const {
                return m_ptr;
            }

            T *release() {
                T *temp = m_ptr;
                m_ptr = nullptr;
                return temp;
            }

            T *reset(T *p = nullptr) {
                if (m_ptr != p) {
                    delete m_ptr;
                    m_ptr = p;
                }
            }

            explicit auto_ptr(T *p = nullptr) : m_ptr(p) {}

            auto_ptr(auto_ptr &p) : m_ptr(p.release()) {}

            template<class U>
            auto_ptr(auto_ptr<U> &p):m_ptr(p.release()) {}

            ~auto_ptr() { delete m_ptr; }

            auto_ptr &operator=(auto_ptr &p) {
                if (this != p) {
                    delete m_ptr;
                    m_ptr = p.release();
                }
                return *this;
            }

            template<class U>
            auto_ptr &operator=(auto_ptr<U> &p) {
                if (this->get() != p.get()) {
                    delete m_ptr;
                    m_ptr = p.release();
                }
                return *this;
            }

            T &operator*() const { return *m_ptr; }

            T *operator&() const { return m_ptr; }
        };
    }//namespace
}//namespace