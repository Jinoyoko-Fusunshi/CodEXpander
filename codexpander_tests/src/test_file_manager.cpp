#include <string>
#include <vector>
#include <filesystem>
#include "file_manager.h"
#include "header_inlcude_expander.h"
#include "declarations.h"
#include "test_file_manager.h"
#include "test_system.h"
#include "test_system.hpp"

using std::string, std::vector, std::filesystem::path, std::filesystem::exists;

using namespace CodEXpander::Core;

namespace CodEXpander::Tests {
    void TestSourceFileReader_ReadFileContent_NotExistingFile_EmptyContent() {
        const u64 expectedLineCount = 0;
        const string filePath = "./res/missing_file.cpp";

        const auto fileContentLines = ReadFileByLines(filePath);
        AssertAreEqual<u64>(expectedLineCount, fileContentLines.size());
    }

    void TestSourceFileReader_ReadFileContent_ExistingFile_ContentIsCorrect() {
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

    void TestSourceFileReader_ReadSourceFile_NoHeaderIncludes_FoundNoTokens() {
        const string filePath = "./res/test_file.cpp";
        const u64 expectedHeaderTokenCount = 0;

        vector<HeaderToken> tokens = GetTokensFromFile(filePath);

        AssertAreEqual<u64>(expectedHeaderTokenCount, tokens.size());
    }

    void TestSourceFileReader_ReadSourceFile_HeaderIncludes_FoundLocalTokens_TokensAreCorrect() {
        const u64 expectedHeaderTokenCount = 2;
        const auto expectedHeaderType = static_cast<int>(HeaderFileType::Local);
        const string expectedHeaderOneFileName = "test_file_one.h";
        const string expectedHeaderTwoFileName = "test_file_two.h";
        const unsigned int expectedHeaderOneLineNumber = 1;
        const unsigned int expectedHeaderTwoLineNumber = 8;

        const string filePath = "./res/source_file_with_two_local_headers.cpp";
        vector<HeaderToken> tokens = GetTokensFromFile(filePath);

        AssertAreEqual<u64>(expectedHeaderTokenCount, tokens.size());
        AssertAreEqual<u64>(expectedHeaderOneLineNumber, tokens[0].lineNumber);
        AssertStringsAreEqual(expectedHeaderOneFileName, tokens[0].fileName);
        AssertAreEqual<int>(expectedHeaderType, static_cast<int>(tokens[0].headerType));
        AssertAreEqual<u64>(expectedHeaderTwoLineNumber, tokens[1].lineNumber);
        AssertStringsAreEqual(expectedHeaderTwoFileName, tokens[1].fileName);
        AssertAreEqual<int>(expectedHeaderType, static_cast<int>(tokens[1].headerType));
    }

    void TestSourceFileReader_ReadSourceFile_HeaderIncludes_FoundExternalTokens_TokensAreCorrect() {
        const u64 expectedHeaderTokenCount = 2;
        const auto expectedHeaderType = static_cast<int>(HeaderFileType::External);
        const string expectedHeaderOneFileName = "test_file_one.h";
        const string expectedHeaderTwoFileName = "test_file_two.h";
        const unsigned int expectedHeaderOneLineNumber = 6;
        const unsigned int expectedHeaderTwoLineNumber = 7;

        const string filePath = "./res/source_file_with_two_external_headers.cpp";
        vector<HeaderToken> tokens = GetTokensFromFile(filePath);

        AssertAreEqual<u64>(expectedHeaderTokenCount, tokens.size());
        AssertAreEqual<u64>(expectedHeaderOneLineNumber, tokens[0].lineNumber);
        AssertStringsAreEqual(expectedHeaderOneFileName, tokens[0].fileName);
        AssertAreEqual<int>(expectedHeaderType, static_cast<int>(tokens[0].headerType));
        AssertAreEqual<u64>(expectedHeaderTwoLineNumber, tokens[1].lineNumber);
        AssertStringsAreEqual(expectedHeaderTwoFileName, tokens[1].fileName);
        AssertAreEqual<int>(expectedHeaderType, static_cast<int>(tokens[1].headerType));
    }

    void TestSourceFileReader_ReadSourceFile_HeaderIncludes_FoundExternalAndLocalTokens_TokensAreCorrect() {
        const u64 expectedHeaderTokenCount = 2;
        const auto expectedHeaderOneType = static_cast<int>(HeaderFileType::External);
        const auto expectedHeaderTwoType = static_cast<int>(HeaderFileType::Local);
        const string expectedHeaderOneFileName = "test_file_one.h";
        const string expectedHeaderTwoFileName = "test_file_two.h";
        const unsigned int expectedHeaderOneLineNumber = 2;
        const unsigned int expectedHeaderTwoLineNumber = 10;

        const string filePath = "./res/source_file_with_two_different_headers.cpp";
        vector<HeaderToken> tokens = GetTokensFromFile(filePath);

        AssertAreEqual<u64>(expectedHeaderTokenCount, tokens.size());
        AssertAreEqual<u64>(expectedHeaderOneLineNumber, tokens[0].lineNumber);
        AssertStringsAreEqual(expectedHeaderOneFileName, tokens[0].fileName);
        AssertAreEqual<int>(expectedHeaderOneType, static_cast<int>(tokens[0].headerType));
        AssertAreEqual<u64>(expectedHeaderTwoLineNumber, tokens[1].lineNumber);
        AssertStringsAreEqual(expectedHeaderTwoFileName, tokens[1].fileName);
        AssertAreEqual<int>(expectedHeaderTwoType, static_cast<int>(tokens[1].headerType));
    }

    void TestSourceFileReader_ReadHeaderFile_HeaderIncludes_FoundExternalTokens_TokensAreCorrect() {
        const u64 expectedHeaderTokenCount = 1;
        const auto expectedHeaderType = static_cast<int>(HeaderFileType::Local);
        const string expectedHeaderFileName = "test_file_one.h";
        const unsigned int expectedHeaderLineNumber = 5;

        const string filePath = "./res/header_file_with_external_header.h";
        vector<HeaderToken> tokens = GetTokensFromFile(filePath);

        AssertAreEqual<u64>(expectedHeaderTokenCount, tokens.size());
        AssertAreEqual<u64>(expectedHeaderLineNumber, tokens[0].lineNumber);
        AssertStringsAreEqual(expectedHeaderFileName, tokens[0].fileName);
        AssertAreEqual<int>(expectedHeaderType, static_cast<int>(tokens[0].headerType));
    }

    void TestSourceFileReader_ReadSourceFile_HeaderFileNotExists_GetHeaderContent_EmptyResult() {
        const u64 expectedHeaderContentSize = 0;
        const string filePath = "./res/source_file_with_local_not_existing_header.cpp";
        const string workingDirectory = "./res";

        vector<HeaderToken> tokens = GetTokensFromFile(filePath);
        const vector<string> headerContent = GetHeaderContent(tokens[0], workingDirectory);

        AssertAreEqual<u64>(expectedHeaderContentSize, headerContent.size());        
    }

    void TestSourceFileReader_ReadSourceFile_HeaderFileExists_GetHeaderContent_ContentIsCorrect() {
        const u64 expectedHeaderContentSize = 5;
        const string filePath = "./res/source_file_with_two_local_headers.cpp";
        const string workingDirectory = "./res";

        vector<HeaderToken> tokens = GetTokensFromFile(filePath);
        const vector<string> headerOneContent = GetHeaderContent(tokens[0], workingDirectory);
        const vector<string> headerTwoContent = GetHeaderContent(tokens[1], workingDirectory);

        AssertAreEqual<u64>(expectedHeaderContentSize, headerOneContent.size());
        AssertAreEqual<u64>(expectedHeaderContentSize, headerTwoContent.size());
    }

    void TestSourceFileReader_TryWriteToFile_NoFilePath_NotWritingToFile() {
        const auto expectedResult = false;
        const string outputFile = "./res/expanded_source_file.cpp";

        vector<string> fileContent;
        path outputFilePath(outputFile);
        auto wroteToFile = TryWriteToFile(outputFile, fileContent);
        auto outputPathExists = exists(outputFilePath);

        AssertAreEqual<bool>(expectedResult, wroteToFile);
        AssertAreEqual<bool>(expectedResult, outputPathExists);
    }

    void TestSourceFileReader_TryWriteToFile_NoFileContent_NotWritingToFile() {
        const auto expectedResult = false;
        const string outputFile = "";

        vector<string> fileContent;
        path outputFilePath(outputFile);
        auto wroteToFile = TryWriteToFile(outputFile, fileContent);
        auto outputPathExists = exists(outputFilePath);

        AssertAreEqual<bool>(expectedResult, wroteToFile);
        AssertAreEqual<bool>(expectedResult, outputPathExists);
    }

    void TestSourceFileReader_TryWriteToFile_ValidPathAndContent_WritesToFile() {
        const auto expectedResult = true;
        const string filePath = "./res/source_file_with_two_local_headers.cpp";
        const string workingDirectory = "./res";
        const string outputFile = "./res/expanded_source_file.cpp";

        vector<HeaderToken> includeHeaders = GetTokensFromFile(filePath);
        vector<string> fileContent = ReadFileByLines(filePath);
        ExpandHeaderIncludes(fileContent, includeHeaders, workingDirectory);

        path outputFilePath(outputFile);
        auto wroteToFile = TryWriteToFile(outputFile, fileContent);
        auto outputPathExists = exists(outputFilePath);

        AssertAreEqual<bool>(expectedResult, wroteToFile);
        AssertAreEqual<bool>(expectedResult, outputPathExists);

        vector<string> outputFileContent = ReadFileByLines(outputFile);
        AssertAreEqual<u64>(fileContent.size(), outputFileContent.size());

        for (u64 i = 0; i < outputFileContent.size(); i++)
            AssertStringsAreEqual(fileContent[i], outputFileContent[i]);
    }
}