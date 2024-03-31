#include <vector>
#include <string>
#include "declarations.h"
#include "header_inlcude_expander.h"
#include "command_parser.h"

using namespace CodEXpander::Core;
using std::string, std::vector;

int main(int argument_count, c8 **arguments) {
    auto parsedArguments = ParseArguments(argument_count, arguments);

    return 0;
}