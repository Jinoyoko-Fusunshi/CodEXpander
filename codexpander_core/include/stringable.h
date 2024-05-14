#pragma once

#include <string>

namespace CodEXpander::Core {
    class Stringable {
    public:
        virtual std::string ToString() = 0;
    };
}