#include <algorithm>
#include <ranges>
#include "command_parser.h"
#include "declarations.h"

using std::vector, std::string, std::find, std::views::filter, std::distance;

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

    vector<Argument> ParseArguments(const int argument_count, const vector<string> &arguments) {
        vector<Argument> parsedArguments;
        for (auto i = 0; i < argument_count; i++) {
            const string parameter(arguments[i]);
            if (Argument parsedArgument; TryParseArgument(parameter, parsedArgument))
                parsedArguments.emplace_back(parsedArgument);
        }

        return std::move(parsedArguments);
    }

    bool TryParseArgument(const string &argumentString, Argument &argument) {
        const u64 argumentPrefixLength = 2;
        const u64 argumentLength = argumentString.size();
        if (argumentLength <= argumentPrefixLength)
            return false;
        
        const c8 argumentPrefix = '-';
        for (u64 i = 0; i < argumentPrefixLength; i++) {
            if (argumentString[i] != argumentPrefix)
                return false;
        }

        const c8 valueAssignmentOperator = '=';
        const u64 assingmentIndex = argumentString.find(valueAssignmentOperator);
        const bool hasValue = assingmentIndex != string::npos;

        const u64 argumentNameStartIndex = argumentPrefixLength;
        const u64 argumentNameEndIndex = hasValue ? assingmentIndex : argumentString.size();
        const u64 argumentNameLength = argumentNameEndIndex - argumentNameStartIndex;
        if (argumentNameLength == 0)
            return false;

        const string argumentName = argumentString.substr(argumentNameStartIndex, argumentNameLength);
        if (!hasValue) {
            argument = Argument(std::move(argumentName));
            return true;
        }
        
        const u64 argumentValueLength = argumentString.size() - assingmentIndex;
        if (argumentValueLength == 0) {
            argument = Argument(std::move(argumentName));
            return true;
        }

        const string argumentValue = argumentString.substr(assingmentIndex + 1, argumentValueLength);
        argument = Argument(std::move(argumentName), std::move(argumentValue));

        return true;
    }

    bool TryGetArgumentWithValue(const vector<Argument> &arguments, const string &name, Argument &foundArgument) {
        auto argumentExists = TryGetArgument(arguments, name, foundArgument);
        if (!argumentExists)
            return false;
        
        if (!foundArgument.HasValue() || foundArgument.GetValue().compare("") == 0)
            return false;

        return true;
    }

    bool TryGetArgument(const vector<Argument> &arguments, const string &name, Argument &foundArgument) {
        const auto findElementByName = [name](Argument argument) {
            return argument.GetName().compare(name) == 0;
        };

        auto filteredArguments = arguments | filter(findElementByName);
        const auto size = distance(filteredArguments.begin(), filteredArguments.end());
        if (size == 0)
            return false;

        const vector<Argument> foundArguments(filteredArguments.begin(), filteredArguments.end());
        Argument argument = foundArguments[0];
        if (argument.GetName().compare("") == 0)
            return false;
        
        foundArgument = argument;
        return true;
    }
}