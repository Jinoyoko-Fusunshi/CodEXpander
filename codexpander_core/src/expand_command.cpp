#include <string>
#include "expand_command.h"
#include "header_dependy_finder.h"

using std::string;

namespace CodEXpander::Core {
    void WriteExpandedContentToFile(const string &sourceFile, string &outputFile, string &workingDirectory);

    void ExpandCommand::Execute() {
        if (!ArgumentsAreValid(providedArguments)) {
            logger.PrintLineInfoMessage("The given arguments for this command are invalid.");
            return;      
        }
    
        if (Argument sourceArgument; TryGetArgument("source_file", sourceArgument)) {
            const string sourceFile = sourceArgument.GetValue();
            string workingDirectory = "./";
            string outputFile = "./temp_extended_filename.cpp";
            
            if (Argument outputFileArgument; TryGetArgument("output_file", outputFileArgument))
                outputFile = outputFileArgument.GetValue();

            if (Argument workingDirArgument; TryGetArgument("working_dir", workingDirArgument))
                workingDirectory = workingDirArgument.GetValue();

            WriteExpandedContentToFile(sourceFile, outputFile, workingDirectory);
        }
    }

    void WriteExpandedContentToFile(const string &sourceFile, string &outputFile, string &workingDirectory) {
        HeaderDependencyGraph dependencyGraph(sourceFile, workingDirectory);
        const auto countedHeaderFiles = dependencyGraph.GetHeaderFilesSortedByOccurences();
        const auto expandedSourceFileContent = ExpandHeaderIncludes(sourceFile, countedHeaderFiles, workingDirectory);
        const auto wroteToFile = TryWriteToFile(outputFile, expandedSourceFileContent);
    }
}