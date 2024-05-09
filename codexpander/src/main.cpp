#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include "declarations.h"
#include "command_parser.h"
#include "file_manager.h"
#include "header_inlcude_expander.h"
#include "header_dependy_finder.h"
#include "logging.h"
#include "color_builder.h"

using namespace CodEXpander::Core;
using std::string, std::vector, std::filesystem::path, std::pair, std::cout, std::endl;

void DisplayHelpPage(Logger &logger);
void WriteExpandedContentToFile(const string &sourceFile, string &outputFile, string &workingDirectory);

int main(int argumentCount, c8 *rawArguments[]) {
    Logger logger;

    vector<string> arguments;
    for (u64 i = 0; i < argumentCount; i++) {
        string argument(rawArguments[i]);
        arguments.emplace_back(argument);
    }

    auto parsedArguments = ParseArguments(argumentCount, arguments);
    if (Argument helpArgument; TryGetArgument(parsedArguments, "help", helpArgument)) {
        DisplayHelpPage(logger);
    }

    if (Argument sourceArgument; TryGetArgumentWithValue(parsedArguments, "source_file", sourceArgument)) {
        const string sourceFile = sourceArgument.GetValue();
        string workingDirectory = "./";
        string outputFile = "./temp_extended_filename.cpp";
        
        if (Argument outputFileArgument; TryGetArgument(parsedArguments, "output_file", outputFileArgument))
            outputFile = outputFileArgument.GetValue();

        if (Argument workingDirArgument; TryGetArgument(parsedArguments, "working_dir", workingDirArgument))
            workingDirectory = workingDirArgument.GetValue();

        WriteExpandedContentToFile(sourceFile, outputFile, workingDirectory);
    }

    return 0;
}

void DisplayHelpPage(Logger &logger) {
    auto displayTextColor = Color::White();

    logger.PrintLineInfoMessage("");
    logger.PrintMessage("Usage:", displayTextColor);
    logger.PrintLineInfoMessage("     codexpander [OPTIONS]");
    logger.PrintLineInfoMessage("");
    logger.PrintLineMessage("Description:", displayTextColor);
    logger.PrintLineInfoMessage("A tool to resolve header include statements in a source file and enlist the content based on the correct call and structure hierarchy.");
    logger.PrintLineInfoMessage("");
    logger.PrintLineMessage("Options:", displayTextColor);
    logger.PrintMessage("   --source_file       ", displayTextColor);
    logger.PrintLineInfoMessage("Specifies the source file to be expanded");
    logger.PrintMessage("   --output_file       ", displayTextColor);
    logger.PrintLineInfoMessage("Specifies the expanded source file to be created by a given valid path");
    logger.PrintMessage("   --working_dir       ", displayTextColor);
    logger.PrintLineInfoMessage("Specifies the root directory where the include directory should exist to look for header files");
    logger.PrintLineMessage("", displayTextColor);
}

void WriteExpandedContentToFile(const string &sourceFile, string &outputFile, string &workingDirectory) {
    HeaderDependencyGraph dependencyGraph(sourceFile, workingDirectory);
    const auto countedHeaderFiles = dependencyGraph.GetHeaderFilesSortedByOccurences();
    auto expandedSourceFileContent = ExpandHeaderIncludes(sourceFile, countedHeaderFiles, workingDirectory);
    const auto wroteToFile = TryWriteToFile(outputFile, expandedSourceFileContent);
}