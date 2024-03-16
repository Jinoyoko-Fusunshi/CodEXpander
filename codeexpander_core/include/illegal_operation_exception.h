#pragma once

#include "exception.h"

class IllegalOperationException final : public Exception {
public:
    explicit IllegalOperationException(std::string message) : Exception(std::move(message)) {}
};
