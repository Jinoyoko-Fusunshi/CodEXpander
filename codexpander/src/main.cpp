#include <vector>
#include <string>
#include "declarations.h"
#include "header_inlcude_expander.h"
#include "command_parser.h"

using namespace CodEXpander::Core;
using std::string, std::vector;

int main(int argument_count, c8 *raw_arguments[]) {
    vector<string> arguments;
    for (u64 i = 0; i < argument_count; i++) {
        string argument(raw_arguments[i]);
        arguments.emplace_back(argument);
    }

    auto parsedArguments = ParseArguments(argument_count, arguments);

    return 0;
}