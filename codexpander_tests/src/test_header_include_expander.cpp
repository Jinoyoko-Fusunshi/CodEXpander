#include <filesystem>
#include "file_manager.h"
#include "header_inlcude_expander.h"
#include "test_system.h"
#include "test_system.hpp"
#include "test_header_include_expander.h"

using namespace std::filesystem;
using namespace CodEXpander::Core;
using std::vector, std::string, std::filesystem::path, std::filesystem::exists;

namespace CodEXpander::Tests {
    void TestSourceFileExpander_ExpandHeaderIncludes_NoInlcudes_FileContentIsEqual() {
        const u64 expectedTokensCount = 0;
        const vector<string> expectedFileContent = {
            "int test(int a, int b) {",
            "    return a + b;",
            "}"
        };

        const string workingDirectory = "./res";
        const string filePath = "./res/test_file.cpp";
        const vector<HeaderToken> includeHeaders = GetTokensFromFile(filePath);
        vector<string> fileContent = ReadFileByLines(filePath);
      
        AssertAreEqual<u64>(expectedTokensCount, includeHeaders.size());
        AssertAreEqual<u64>(expectedFileContent.size(), fileContent.size());

        for (u64 i = 0; i < fileContent.size(); i++) {
            const auto currentLine = fileContent[i];
            AssertStringsAreEqual(expectedFileContent[i], currentLine);
        }
    }

    void TestSourceFileExpander_ExpandHeaderIncludes_OneInlcude_NewFileContentIsCorrect() {
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

        ExpandHeaderIncludes(fileContent, std::move(includeHeaders), workingDirectory);
        AssertAreEqual<u64>(expectedFileContent.size(), fileContent.size());

        for (u64 i = 0; i < fileContent.size(); i++) {
            const auto currentLine = fileContent[i];
            AssertStringsAreEqual(expectedFileContent[i], currentLine);
        }
    }
}