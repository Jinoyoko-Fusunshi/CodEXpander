#pragma once

#include "command.h"

namespace CodEXpander::Core {
    class HelpCommand final : public Command {
    public:
        HelpCommand(Logger &logger, std::vector<ValidArgument> validArguments = std::vector<ValidArgument>()) : Command(logger, validArguments, "help") {}
        ~HelpCommand() = default;

        void Execute();
    };
}