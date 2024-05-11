#pragma once

#include <string>
#include <vector>
#include "declarations.h"
#include "argument.h"
#include "command.h"

namespace CodEXpander::Core {
    class CommandParser final {
    private:
        std::vector<Command*> availableCommands {};

        static bool IsCommand(const std::string &name);
        static std::vector<Argument> GetParsedArguments(const std::vector<std::string> &rawArguments);
        static bool TryParseArgument(const std::string &argumentString, Argument &argument);

    public:
        explicit CommandParser(std::vector<Command*> commands);
        ~CommandParser() = default;

        bool TryParseCommand(int argumentCount, c8 *rawArguments[], Command* &foundCommand);
        bool TryParseCommand(const std::vector<std::string> &rawArguments, Command* &foundCommand);
    };
}