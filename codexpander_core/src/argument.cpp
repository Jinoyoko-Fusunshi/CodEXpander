#include "argument.h"

namespace CodEXpander::Core {
    Argument::Argument(std::string name, std::string value) {
        this->name = name;
        this->value = value;
    }

    const std::string& Argument::GetName() {
        return name;
    }

    const std::string& Argument::GetValue() {
        return value;
    }

    bool Argument::HasValue() {
        return value.compare("") != 0;
    }
}