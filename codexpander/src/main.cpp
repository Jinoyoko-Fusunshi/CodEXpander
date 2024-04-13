#include <vector>
#include <string>
#include <filesystem>
#include "declarations.h"
#include "command_parser.h"
#include "file_manager.h"
#include "header_inlcude_expander.h"
#include "header_dependy_finder.h"

using namespace CodEXpander::Core;
using std::string, std::vector, std::filesystem::path, std::pair;

void WriteExpandedContentToFile(const string &sourceFile, string &outputFile, string &workingDirectory);

int main(int argument_count, c8 *raw_arguments[]) {
    vector<string> arguments;
    for (u64 i = 0; i < argument_count; i++) {
        string argument(raw_arguments[i]);
        arguments.emplace_back(argument);
    }

    auto parsedArguments = ParseArguments(argument_count, arguments);
    if (Argument source_argument; TryGetExistingArgument(parsedArguments, "source_file", source_argument)) {
        const string sourceFile = source_argument.value;
        string workingDirectory = "./";
        string outputFile = "./temp_extended_filename.cpp";
        
        if (Argument argument; TryGetExistingArgument(parsedArguments, "output_file", argument))
            outputFile = argument.value;

        if (Argument argument; TryGetExistingArgument(parsedArguments, "working_dir", argument))
            workingDirectory = argument.value;

        WriteExpandedContentToFile(sourceFile, outputFile, workingDirectory);
    }

    return 0;
}

void WriteExpandedContentToFile(const string &sourceFile, string &outputFile, string &workingDirectory) {
    HeaderDependencyGraph dependencyGraph(sourceFile, workingDirectory);
    const auto countedHeaderFiles = dependencyGraph.GetHeaderFilesSortedByOccurences();
    auto expandedSourceFileContent = ExpandHeaderIncludes(sourceFile, countedHeaderFiles, workingDirectory);
    const auto wroteToFile = TryWriteToFile(outputFile, expandedSourceFileContent);
}