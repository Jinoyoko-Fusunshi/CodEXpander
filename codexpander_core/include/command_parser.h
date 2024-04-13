#pragma once

#include <string>
#include <vector>

namespace CodEXpander::Core {
    struct Argument {
        std::string name;
        std::string value;
    };

    std::vector<Argument> ParseArguments(const int argument_count, const std::vector<std::string> &arguments);
    bool TryGetArgument(const std::string &argumentString, Argument &argument);
    bool TryGetExistingArgument(const std::vector<Argument> &arguments, const std::string &name, Argument &foundArgument);
}