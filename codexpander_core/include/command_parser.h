#pragma once

#include <string>
#include <vector>

namespace CodEXpander::Core {
    struct Argument {
        std::string name;
        std::string value;
    };

    std::vector<Argument> ParseArguments(int argument_count, std::vector<std::string> arguments);

    bool TryGetArgument(std::string argumentString, Argument &argument);
}