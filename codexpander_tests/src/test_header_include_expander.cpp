#include <filesystem>
#include "file_manager.h"
#include "header_inlcude_expander.h"
#include "test_system.h"
#include "test_header_include_expander.h"
#include <header_dependy_finder.h>

using namespace std::filesystem;
using namespace CodEXpander::Core;
using std::vector, std::string, std::filesystem::path, std::filesystem::exists;

namespace CodEXpander::Tests {
    void TestHeaderIncludeExpander_GetTokensFromFiles_NoHeaderIncludes_FoundNoTokens() {
        const string filePath = "./res/test_file.cpp";
        const u64 expectedHeaderTokenCount = 0;

        vector<HeaderToken> tokens = GetTokensFromFile(filePath);

        TestSystem::AssertValues<u64>(expectedHeaderTokenCount, tokens.size());
    }

    void TestHeaderIncludeExpander_GetTokensFromFile_FoundLocalTokens_TokensAreCorrect() {
        const u64 expectedHeaderTokenCount = 2;
        const auto expectedHeaderType = static_cast<int>(HeaderFileType::Local);
        const string expectedHeaderOneFileName = "test_file_one.h";
        const string expectedHeaderTwoFileName = "test_file_two.h";
        const unsigned int expectedHeaderOneLineNumber = 1;
        const unsigned int expectedHeaderTwoLineNumber = 8;

        const string filePath = "./res/source_file_with_two_local_headers.cpp";
        vector<HeaderToken> tokens = GetTokensFromFile(filePath);

        TestSystem::AssertValues<u64>(expectedHeaderTokenCount, tokens.size());
        TestSystem::AssertValues<u64>(expectedHeaderOneLineNumber, tokens[0].lineNumber);
        TestSystem::AssertStrings(expectedHeaderOneFileName, tokens[0].fileName);
        TestSystem::AssertValues<int>(expectedHeaderType, static_cast<int>(tokens[0].headerType));
        TestSystem::AssertValues<u64>(expectedHeaderTwoLineNumber, tokens[1].lineNumber);
        TestSystem::AssertStrings(expectedHeaderTwoFileName, tokens[1].fileName);
        TestSystem::AssertValues<int>(expectedHeaderType, static_cast<int>(tokens[1].headerType));
    }

    void TestHeaderIncludeExpander_GetTokensFromFile_FoundTwoExternalTokens_TokensAreCorrect() {
        const u64 expectedHeaderTokenCount = 2;
        const auto expectedHeaderType = static_cast<int>(HeaderFileType::System);
        const string expectedHeaderOneFileName = "test_file_one.h";
        const string expectedHeaderTwoFileName = "test_file_two.h";
        const unsigned int expectedHeaderOneLineNumber = 6;
        const unsigned int expectedHeaderTwoLineNumber = 7;

        const string filePath = "./res/source_file_with_two_external_headers.cpp";
        vector<HeaderToken> tokens = GetTokensFromFile(filePath);

        TestSystem::AssertValues<u64>(expectedHeaderTokenCount, tokens.size());
        TestSystem::AssertValues<u64>(expectedHeaderOneLineNumber, tokens[0].lineNumber);
        TestSystem::AssertStrings(expectedHeaderOneFileName, tokens[0].fileName);
        TestSystem::AssertValues<int>(expectedHeaderType, static_cast<int>(tokens[0].headerType));
        TestSystem::AssertValues<u64>(expectedHeaderTwoLineNumber, tokens[1].lineNumber);
        TestSystem::AssertStrings(expectedHeaderTwoFileName, tokens[1].fileName);
        TestSystem::AssertValues<int>(expectedHeaderType, static_cast<int>(tokens[1].headerType));
    }

    void TestHeaderIncludeExpander_GetTokensFromFile_FoundExternalAndLocalTokens_TokensAreCorrect() {
        const u64 expectedHeaderTokenCount = 2;
        const auto expectedHeaderOneType = static_cast<int>(HeaderFileType::System);
        const auto expectedHeaderTwoType = static_cast<int>(HeaderFileType::Local);
        const string expectedHeaderOneFileName = "test_file_one.h";
        const string expectedHeaderTwoFileName = "test_file_two.h";
        const unsigned int expectedHeaderOneLineNumber = 2;
        const unsigned int expectedHeaderTwoLineNumber = 10;

        const string filePath = "./res/source_file_with_two_different_headers.cpp";
        vector<HeaderToken> tokens = GetTokensFromFile(filePath);

        TestSystem::AssertValues<u64>(expectedHeaderTokenCount, tokens.size());
        TestSystem::AssertValues<u64>(expectedHeaderOneLineNumber, tokens[0].lineNumber);
        TestSystem::AssertStrings(expectedHeaderOneFileName, tokens[0].fileName);
        TestSystem::AssertValues<int>(expectedHeaderOneType, static_cast<int>(tokens[0].headerType));
        TestSystem::AssertValues<u64>(expectedHeaderTwoLineNumber, tokens[1].lineNumber);
        TestSystem::AssertStrings(expectedHeaderTwoFileName, tokens[1].fileName);
        TestSystem::AssertValues<int>(expectedHeaderTwoType, static_cast<int>(tokens[1].headerType));
    }

    void TestHeaderIncludeExpander_GetTokensFromFile_FoundExternalTokens_TokensAreCorrect() {
        const u64 expectedHeaderTokenCount = 1;
        const auto expectedHeaderType = static_cast<int>(HeaderFileType::Local);
        const string expectedHeaderFileName = "test_file_one.h";
        const unsigned int expectedHeaderLineNumber = 5;

        const string filePath = "./res/header_file_with_external_header.h";
        vector<HeaderToken> tokens = GetTokensFromFile(filePath);

        TestSystem::AssertValues<u64>(expectedHeaderTokenCount, tokens.size());
        TestSystem::AssertValues<u64>(expectedHeaderLineNumber, tokens[0].lineNumber);
        TestSystem::AssertStrings(expectedHeaderFileName, tokens[0].fileName);
        TestSystem::AssertValues<int>(expectedHeaderType, static_cast<int>(tokens[0].headerType));
    }

    void TestHeaderIncludeExpander_GetTokensFromFile_HeaderFileNotExists_GetHeaderContent_EmptyResult() {
        const u64 expectedHeaderContentSize = 0;
        const string filePath = "./res/source_file_with_local_not_existing_header.cpp";
        const string workingDirectory = "./res";

        vector<HeaderToken> tokens = GetTokensFromFile(filePath);
        const vector<string> headerContent = GetHeaderContent(tokens[0], workingDirectory);

        TestSystem::AssertValues<u64>(expectedHeaderContentSize, headerContent.size());        
    }

    void TestHeaderIncludeExpander_ExpandHeaderIncludes_NoInlcudes_FileContentIsEqual() {
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
      
        TestSystem::AssertValues<u64>(expectedTokensCount, includeHeaders.size());
        TestSystem::AssertValues<u64>(expectedFileContent.size(), fileContent.size());

        for (u64 i = 0; i < fileContent.size(); i++) {
            const auto currentLine = fileContent[i];
            TestSystem::AssertStrings(expectedFileContent[i], currentLine);
        }
    }

    void TestHeaderIncludeExpander_ExpandHeaderIncludes_OneInlcude_NewFileContentIsCorrect() {
        const vector<string> expectedFileContent = {
            "",
            "struct TestStructTwo {",
            "    int testField;",
            "}",                  
            "",
            "struct TestStructOne {",
            "    int testField;",
            "}",
            "",
            "void test() {",
            "    int x = 2 * 10;",
            "    int y = x - 20;",
            "}",
            ""
        };

        const string workingDirectory = "./res";
        string filePath = "./res/source_file_with_two_local_headers.cpp";
        const vector<HeaderToken> includeHeaders = GetTokensFromFile(filePath);

        HeaderDependencyGraph dependencyGraph(filePath, workingDirectory);
        vector<HeaderFile> sortedHeaderFileIncludes = dependencyGraph.GetHeaderFilesSortedByOccurences();
        vector<string> expandedSourceFile = ExpandHeaderIncludes(filePath, sortedHeaderFileIncludes, workingDirectory);
        TestSystem::AssertValues<u64>(expectedFileContent.size(), expandedSourceFile.size());

        for (u64 i = 0; i < expandedSourceFile.size(); i++) {
            const auto currentLine = expandedSourceFile[i];
            TestSystem::AssertStrings(expectedFileContent[i], currentLine);
        }
    }
}