#pragma once

#include "exception.h"

namespace CodEXpander::Core {
    class IllegalOperationException final : public Exception {
    public:
        explicit IllegalOperationException(std::string message) : Exception(std::move(message)) {}
    };
}
