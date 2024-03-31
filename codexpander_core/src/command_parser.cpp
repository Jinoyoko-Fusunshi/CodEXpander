#include "command_parser.h"
#include "declarations.h"

using std::vector, std::string;

namespace CodEXpander::Core {
    vector<Argument> ParseArguments(int argument_count, string arguments[]) {
        vector<Argument> parsedArguments;
        for (auto i = 0; i < argument_count; i++) {
            const string parameter(arguments[i]);
            Argument parsedArgument;

            if (!TryGetArgument(parameter, parsedArgument))
                continue;

            parsedArguments.emplace_back(parsedArgument);
        }

        return std::move(parsedArguments);
    }

    bool TryGetArgument(string argumentString, Argument &argument) {
        const u64 argumentPrefixLength = 2;
        u64 argumentLength = argumentString.size();
        if (argumentLength <= argumentPrefixLength)
            return false;
        
        const c8 argumentPrefix = '-';
        for (u64 i = 0; i < argumentPrefixLength; i++) {
            if (argumentString[i] != argumentPrefix)
                return false;
        }

        const c8 valueAssignmentOperator = '=';
        u64 assingmentIndex = argumentString.find(valueAssignmentOperator);
        if (assingmentIndex == string::npos)
            return false;

        u64 argumentNameLength = assingmentIndex - argumentPrefixLength;
        if (argumentLength == 0)
            return false;

        string argumentName = argumentString.substr(argumentPrefixLength, argumentNameLength);
        u64 argumentValueLength = argumentString.size() - assingmentIndex;
        if (argumentValueLength == 0)
            return false;

        string argumentValue = argumentString.substr(assingmentIndex + 1, argumentValueLength);
        argument.name = std::move(argumentName);
        argument.value = std::move(argumentValue);

        return true;
    }
}