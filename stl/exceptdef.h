//
// Created by hyn on 2023/3/14.
//

#pragma once

#include <stdexcept>
#include <cassert>

namespace hyn {
    namespace stl {

#define DEBUG(expr) \
        assert(expr)

#define THROW_LENGHT_ERROR_IF(expr, what) \
        if((expr)) throw std::length_error(what)

#define THROW_OUT_OF_RANGE_IF(expr, what) \
  if ((expr)) throw std::out_of_range(what)

#define THROW_RUNTIME_ERROR_IF(expr, what) \
  if ((expr)) throw std::runtime_error(what)


    }
}
