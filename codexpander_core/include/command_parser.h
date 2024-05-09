#pragma once

#include <string>
#include <vector>
#include "declarations.h"
#include "argument.h"

namespace CodEXpander::Core {
    class CommandParser final {
    private:
        std::vector<Argument> parsedArguments;

        void ParseArguments(std::vector<std::string> rawArguments);

    public:
        CommandParser() = default;
        explicit CommandParser(int argumentCount, c8 *rawArguments[]);
        explicit CommandParser(std::vector<std::string> rawArguments);
        ~CommandParser() = default;

        bool TryParseArgument(const std::string &argumentString, Argument &argument);
        bool TryGetArgumentWithValue(const std::string &name, Argument &foundArgument);
        bool TryGetArgument(const std::string &name, Argument &foundArgument);    
        const u64 GetArgumentCount();
    };
}