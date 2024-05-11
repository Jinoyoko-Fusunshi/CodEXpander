#include <algorithm>
#include <ranges>
#include "command_parser.h"
#include "declarations.h"

using std::vector, std::string, std::find, std::views::filter, std::distance;

namespace CodEXpander::Core {
    CommandParser::CommandParser(vector<Command*> commands) : availableCommands(commands) {}

    bool CommandParser::TryParseCommand(int argumentCount, c8 *rawArguments[], Command* &foundCommand) {
        vector<string> stringArguments;
        for (auto i = 0; i < argumentCount; i++)
            stringArguments.emplace_back(rawArguments[i]);

        return TryParseCommand(stringArguments, foundCommand);
    }

    bool CommandParser::TryParseCommand(const vector<string> &rawArguments, Command* &foundCommand) {
        const u64 argumentStartIndex = 1;
        vector<Command*> foundCommands;
        for (auto i = argumentStartIndex; i < rawArguments.size(); i++) {
            const string argument = rawArguments[i];
            if (!IsCommand(argument))
                continue;
            
            for (const auto &command : availableCommands) {
                if (command->GetName().compare(argument) == 0)
                    foundCommands.emplace_back(command);
            }
        }

        const u64 requiredCommandAmount = 1;
        if (foundCommands.size() != requiredCommandAmount)
            return false;

        const auto arguments = GetParsedArguments(std::move(rawArguments));
        foundCommand = *foundCommands.begin();
        foundCommand->SetProvidedArguments(std::move(arguments));
        return true;
    }

    bool CommandParser::IsCommand(const std::string &name) {
        for (auto character : name) {
            if (!std::isalpha(character))
                return false;
        }
        
        return true;
    }

    vector<Argument> CommandParser::GetParsedArguments(const vector<string> &rawArguments) {
        vector<Argument> parsedArguments;
        for (auto i = 0; i < rawArguments.size(); i++) {
            const string parameter(rawArguments[i]);
            if (Argument parsedArgument; TryParseArgument(parameter, parsedArgument))
                parsedArguments.emplace_back(parsedArgument);
        }

        return std::move(parsedArguments);
    }

    bool CommandParser::TryParseArgument(const string &argumentString, Argument &argument) {
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
}