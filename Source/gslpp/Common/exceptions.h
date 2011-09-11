#pragma once

#include "macros.h"

#include <stdexcept>

BEGIN_GSL_NAMESPACE

    class null_pointer_dereference : public std::runtime_error{
        public:
        null_pointer_dereference() : std::runtime_error("Cannot dereference null pointer"){}
    };

    class divide_by_zero : public std::runtime_error{
        public:
        divide_by_zero() : std::runtime_error("divide-by-zero error"){}
    };

    class undefined_value : public std::runtime_error{
        public:
        undefined_value() : std::runtime_error("value is undefined"){}
    };

    class size_mismatch : public std::runtime_error{
        public:
        size_mismatch() : std::runtime_error("Elements must be of equal size"){}
    };

END_GSL_NAMESPACE
