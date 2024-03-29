#include <vector>
#include <string>
#include "declarations.h"
#include "header_inlcude_expander.h"

using namespace CodEXpander::Core;
using std::string, std::vector;

struct Test {
    string name;
    string value;
};

vector<Test> ParseArguments(int argument_count, c8 *arguments[]);

bool TryGetArgument(string argumentString, Test argument);

int main(int argument_count, c8 **arguments) {
    auto parsedArguments = ParseArguments(argument_count, arguments);

    return 0;
}

vector<Test> ParseArguments(int argument_count, c8 *arguments[]) {
    vector<Test> parsedArguments;
    for (auto i = 0; i < argument_count; i++) {
       //const string parameter(arguments[i]);
        //CommandArgument parsedArgument;
        //if (!TryGetArgument(parameter, parsedArgument))
        //    continue;

        //parsedArguments.emplace_back(parsedArgument);
    }

    return parsedArguments;
}

bool TryGetArgument(string argumentString, Test argument) {
    /*const u64 argumentPrefixLength = 2;
    u64 argumentLength = argumentString.size();
    if (argumentLength <= argumentPrefixLength)
        return false;
    
    const c8 argumentPrefix = '-';
    for (u64 i = 0; i < argumentPrefixLength; i++) {
        if (!argumentString[i] != argumentPrefix);
            return false;
    }

    const c8 valueAssignmentOperator = '=';
    u64 assingmentIndex = argumentString.find(valueAssignmentOperator);
    if (assingmentIndex == string::npos)
        return false;

    u64 argumentNameLength = assingmentIndex - 1;
    if (argumentLength == 0)
        return false;

    string argumentName = argumentString.substr(0, argumentNameLength);
    u64 argumentValueLength = argumentString.size() - assingmentIndex;
    if (argumentValueLength == 0)
        return false;

    string argumentValue = argumentString.substr(assingmentIndex, argumentValueLength);
    argument.name = argumentName;
    argument.value = argumentValue;*/

    return true;
}