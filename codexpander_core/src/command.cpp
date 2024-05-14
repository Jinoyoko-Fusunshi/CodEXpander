#include <algorithm>
#include <ranges>
#include "command.h"
#include "declarations.h"

using std::string, std::vector, std::views::filter;

namespace CodEXpander::Core {
    string Command::ToString() {
        string objectString = "Command { ";

        objectString += "providedArguments: {";
        for (auto& argument : providedArguments)
            objectString += " name: " + argument.GetName() + "; " + "value: " + argument.GetValue() + "; ";

        objectString += "}; ";
        objectString += "name: " + name + ";";

        objectString += " }";
        return objectString;
    }

    void Command::SetValidArguments(const vector<ValidArgument> validArguments) {
        this->validArguments = validArguments;
    }

    void Command::SetProvidedArguments(const std::vector<Argument> providedArguments) {
        this->providedArguments = providedArguments;
    }

    bool Command::ArgumentsAreValid(vector<Argument> &arguments) {
        if (!NeedsArguments() && arguments.size() == 0)
            return true;

        if (!NeedsArguments() && arguments.size() > 0)
            return false;

        for (const auto &validArgument : validArguments) {
            const auto filterArguments = [validArgument](Argument &argument) {
                return validArgument.name.compare(argument.GetName()) == 0 && validArgument.needsValue == argument.HasValue();
            };
            auto filteredArguments = arguments | filter(filterArguments);
            if (filteredArguments.begin() == filteredArguments.end())
                return false;
        }

        return true;
    }

    bool Command::TryGetArgument(const string &name, Argument &foundArgument, bool needsValue) {
        const auto filterArguments = [name, needsValue](Argument &argument) {
            return argument.GetName().compare(name) == 0 && argument.HasValue() == needsValue;
        };
        auto filteredArguments = providedArguments | filter(filterArguments);
        if (filteredArguments.begin() == filteredArguments.end())
            return false;

        foundArgument = *filteredArguments.begin();
        return true;
    }

    const std::string& Command::GetName() {
        return name;
    }

    const bool Command::NeedsArguments() {
        return validArguments.size() > 0;
    }
}