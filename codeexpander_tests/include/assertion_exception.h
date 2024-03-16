#pragma once

#include "exception.h"

class AssertionException final : public Exception {
public:
    AssertionException(std::string message) : Exception(std::move(message)) {}
};
