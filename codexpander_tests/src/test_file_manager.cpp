#include <string>
#include <vector>
#include <filesystem>
#include "file_manager.h"
#include "header_inlcude_expander.h"
#include "declarations.h"
#include "test_file_manager.h"
#include "test_system.h"
#include "test_system.hpp"
#include <header_dependy_finder.h>

using std::string, std::vector, std::filesystem::path, std::filesystem::exists;

using namespace CodEXpander::Core;

namespace CodEXpander::Tests {
    void TestFileManager_ReadFilesByLines_NotExistingFile_EmptyContent() {
        const u64 expectedLineCount = 0;
        const string filePath = "./res/missing_file.cpp";

        const auto fileContentLines = ReadFileByLines(filePath);
        AssertAreEqual<u64>(expectedLineCount, fileContentLines.size());
    }

    void TestFileManager_ReadFilesByLines_ExistingFile_ContentIsCorrect() {
        const string filePath = "./res/test_file.cpp";
        const vector<string> expectedFileContent = {
            "int test(int a, int b) {",
            "    return a + b;",
            "}"
        };

        const auto fileContentLines = ReadFileByLines(filePath);
        for (u64 i = 0; i < fileContentLines.size(); i++) {
            const string &currentExpectedFileLine = expectedFileContent[i];
            string currentFileLine = fileContentLines[i];
            const auto lineIsEqual = currentExpectedFileLine == currentFileLine;
            AssertAreEqual<bool>(true, lineIsEqual);
        }
    }

    void TestHeaderIncludeExpander_GetTokensFromFile_HeaderFileExists_GetHeaderContent_ContentIsCorrect() {
        const u64 expectedHeaderContentSize = 5;
        const string filePath = "./res/source_file_with_two_local_headers.cpp";
        const string workingDirectory = "./res";

        vector<HeaderToken> tokens = GetTokensFromFile(filePath);
        const vector<string> headerOneContent = GetHeaderContent(tokens[0].fileName, workingDirectory);
        const vector<string> headerTwoContent = GetHeaderContent(tokens[1].fileName, workingDirectory);

        AssertAreEqual<u64>(expectedHeaderContentSize, headerOneContent.size());
        AssertAreEqual<u64>(expectedHeaderContentSize, headerTwoContent.size());
    }

    void TestFileManager_TryWriteToFile_NoFilePath_NotWritingToFile() {
        const auto expectedResult = false;
        const string outputFile = "./res/expanded_source_file.cpp";

        vector<string> fileContent;
        path outputFilePath(outputFile);
        auto wroteToFile = TryWriteToFile(outputFile, fileContent);
        auto outputPathExists = exists(outputFilePath);

        AssertAreEqual<bool>(expectedResult, wroteToFile);
        AssertAreEqual<bool>(expectedResult, outputPathExists);
    }

    void TestFileManager_TryWriteToFile_NoFileContent_NotWritingToFile() {
        const auto expectedResult = false;
        const string outputFile = "";

        vector<string> fileContent;
        path outputFilePath(outputFile);
        auto wroteToFile = TryWriteToFile(outputFile, fileContent);
        auto outputPathExists = exists(outputFilePath);

        AssertAreEqual<bool>(expectedResult, wroteToFile);
        AssertAreEqual<bool>(expectedResult, outputPathExists);
    }

    void TestFileManager_TryWriteToFile_ValidPathAndContent_WritesToFile() {
        const auto expectedResult = true;
        string filePath = "./res/source_file_with_two_local_headers.cpp";
        const string workingDirectory = "./res";
        const string outputFile = "./res/expanded_source_file.cpp";

        HeaderDependencyGraph dependencyGraph(filePath, workingDirectory);
        auto countedHeaderFiles = dependencyGraph.GetHeaderFilesSortedByOccurences();
        vector<string> expandedSourceFile = ExpandHeaderIncludes(filePath, countedHeaderFiles, workingDirectory);

        path outputFilePath(outputFile);
        auto wroteToFile = TryWriteToFile(outputFile, expandedSourceFile);
        auto outputPathExists = exists(outputFilePath);

        AssertAreEqual<bool>(expectedResult, wroteToFile);
        AssertAreEqual<bool>(expectedResult, outputPathExists);

        vector<string> outputFileContent = ReadFileByLines(outputFile);
        AssertAreEqual<u64>(expandedSourceFile.size(), outputFileContent.size());

        for (auto i = 0; i < outputFileContent.size(); i++)
            AssertStringsAreEqual(expandedSourceFile[i], outputFileContent[i]);
    }
}