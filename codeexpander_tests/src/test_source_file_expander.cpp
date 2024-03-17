#include "source_file_reader.h"
#include "source_file_expander.h"
#include "test_system.h"
#include "test_system.hpp"
#include "test_source_file_expander.h"

using namespace CodEXpander::Core;
using std::vector, std::string;

namespace CodEXpander::Tests {
    void TestSourceFileExpander_ReplaceIncludeStatemens_NoInlcudes_FileContentIsEqual() {
        const vector<string> expectedFileContent = {
            "#pragma once",
            "",
            "struct TestStructOne {",
            "    int testField;",
            "}",
            "",
            "void test() {",
            "    int x = 2 * 10;",
            "    int y = x - 20;",
            "}",
            "",
            "#pragma once",
            "",
            "struct TestStructTwo {",
            "    int testField;",
            "}"
        };

        const string workingDirectory = "./res";
        const string filePath = "./res/source_file_with_two_local_headers.cpp";
        const vector<HeaderToken> includeHeaders = GetTokensFromFile(filePath);
        vector<string> fileContent = ReadFileByLines(filePath);

        size_t extendedLinesOffset = 0;
        ReplaceIncludeStatementWithHeaderContent(fileContent, includeHeaders[0], workingDirectory, extendedLinesOffset);
        ReplaceIncludeStatementWithHeaderContent(fileContent, includeHeaders[1], workingDirectory, extendedLinesOffset);

        AssertAreEqual<size_t>(expectedFileContent.size(), fileContent.size());

        for (size_t i = 0; i < fileContent.size(); i++) {
            const auto currentLine = fileContent[i];
            AssertStringsAreEqual(expectedFileContent[i], currentLine);
        }
    }

    void TestSourceFileExpander_ReplaceIncludeStatemens_OneInlcude_NewFileContentIsCorrect() {

    }
}