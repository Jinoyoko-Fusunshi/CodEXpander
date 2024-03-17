#pragma once

#include <string>
#include "assertion_exception.h"

namespace CodEXpander::Tests {
    template<typename T> void AssertAreEqual(T expectedValue, T actualValue) {
        auto valueMatches = expectedValue == actualValue;
        if (!valueMatches) {
            std::string message = std::string("Assertion failed:") + std::string("\n\t\t\texpected value: ")
                + std::to_string(expectedValue) + std::string("\n\t\t\tactual value: \t") + std::to_string(actualValue);

            throw AssertionException(message);
        }
    }
}