#pragma once

#include "exception.h"

namespace CodEXpander::Tests {
    class AssertionException final : public CodEXpander::Core::Exception {
    public:
        AssertionException(std::string message) : Exception(std::move(message)) {}
    };
}