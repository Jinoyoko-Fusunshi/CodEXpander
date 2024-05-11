#pragma once

#include "command.h"

namespace CodEXpander::Core {
    class ExpandCommand final : public Command {
    public:
        explicit ExpandCommand(Logger &logger, std::vector<ValidArgument> validArguments = std::vector<ValidArgument>()) : Command(logger, validArguments, "expand") {}
        ~ExpandCommand() = default;

        void Execute();
    };
}