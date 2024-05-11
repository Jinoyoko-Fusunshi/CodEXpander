#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include "declarations.h"
#include "command_parser.h"
#include "file_manager.h"
#include "header_inlcude_expander.h"
#include "header_dependy_finder.h"
#include "logging.h"
#include "help_command.h"
#include "expand_command.h"

using namespace CodEXpander::Core;
using std::string, std::vector, std::filesystem::path, std::pair, std::cout, std::endl, std::views::filter;

int main(int argumentCount, c8 *rawArguments[]) {
    Logger logger;
    const vector<ValidArgument> expandValidArguments = {{"source_file", true}, {"output_file", true}, {"working_dir", true}};
    ExpandCommand expandCommand(logger, expandValidArguments);
    HelpCommand helpCommand(logger);
    const vector<Command*> availableCommands = {&helpCommand, &expandCommand};

    CommandParser commandParser(availableCommands);
    Command *foundCommand = nullptr;
    if (!commandParser.TryParseCommand(argumentCount, rawArguments, foundCommand)) {
        logger.PrintLineInfoMessage("There is no valid or to many commands were entered. Please provide one of the following valid commands.");
        helpCommand.Execute();
        return EXIT_FAILURE;
    }

    foundCommand->Execute();

    return EXIT_SUCCESS;
}