#pragma once

#include <string>
#include <vector>
#include "argument.h"
#include "logging.h"

namespace CodEXpander::Core {
    struct ValidArgument {
        std::string name;
        bool needsValue;
    };

    class Command {
    protected:
        Logger &logger;
        std::string name;
        std::vector<ValidArgument> validArguments;
        std::vector<Argument> providedArguments;

        bool ArgumentsAreValid(std::vector<Argument> &arguments);
        bool TryGetArgument(const std::string &name, Argument &foundArgument, bool needsValue = true);

    public:
        explicit Command(Logger &logger, std::vector<ValidArgument> validArguments, std::string name) : logger(logger), validArguments(validArguments), name(name) {}

        virtual void Execute() = 0;
        void SetValidArguments(const std::vector<ValidArgument> validArguments);
        void SetProvidedArguments(const std::vector<Argument> providedArguments);
        const std::string& GetName();
        const bool NeedsArguments();
    };
}