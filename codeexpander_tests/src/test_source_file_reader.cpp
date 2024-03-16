#include <string>
#include <vector>
#include "source_file_reader.h"
#include "test_source_file_reader.h"
#include "test_system.h"
#include "test_system.hpp"

using std::string, std::vector;

void TestSourceFileReader_ReadFileContent_NotExistingFile_EmptyContent() {
    const size_t expectedLineCount = 0;
    const string filePath = "./res/missing_file.cpp";

    const auto fileContentLines = ReadFileByLines(filePath);
    AssertAreEqual<size_t>(expectedLineCount, fileContentLines.size());
}

void TestSourceFileReader_ReadFileContent_ExistingFile_ContentIsCorrect() {
    const string filePath = "./res/test_file.cpp";
    const vector<string> expectedFileContent = {
        "int test(int a, int b) {",
        "    return a + b;",
        "}"
    };

    const auto fileContentLines = ReadFileByLines(filePath);
    for (size_t i = 0; i < fileContentLines.size(); i++) {
        const string &currentExpectedFileLine = expectedFileContent[i];
        string currentFileLine = fileContentLines[i];
        const auto lineIsEqual = currentExpectedFileLine == currentFileLine;
        AssertAreEqual<bool>(true, lineIsEqual);
    }
}

void TestSourceFileReader_ReadSourceFile_NoHeaderIncludes_FoundNoTokens() {
    const string filePath = "./res/test_file.cpp";
    const size_t expectedHeaderTokenCount = 0;

    vector<HeaderToken> tokens = GetTokensFromFile(filePath);

    AssertAreEqual<size_t>(expectedHeaderTokenCount, tokens.size());
}

void TestSourceFileReader_ReadSourceFile_HeaderIncludes_FoundLocalTokens_TokensAreCorrect() {
    const size_t expectedHeaderTokenCount = 2;
    const auto expectedHeaderType = static_cast<int>(HeaderFileType::Local);
    const string expectedHeaderOneFileName = "test_file_one.h";
    const string expectedHeaderTwoFileName = "test_file_two.h";
    const unsigned int expectedHeaderOneLineNumber = 1;
    const unsigned int expectedHeaderTwoLineNumber = 8;

    const string filePath = "./res/source_file_with_two_local_headers.cpp";
	vector<HeaderToken> tokens = GetTokensFromFile(filePath);

	AssertAreEqual<size_t>(expectedHeaderTokenCount, tokens.size());
	AssertAreEqual<size_t>(expectedHeaderOneLineNumber, tokens[0].lineNumber);
	AssertStringsAreEqual(expectedHeaderOneFileName, tokens[0].fileName);
    AssertAreEqual<int>(expectedHeaderType, static_cast<int>(tokens[0].headerType));
	AssertAreEqual<size_t>(expectedHeaderTwoLineNumber, tokens[1].lineNumber);
	AssertStringsAreEqual(expectedHeaderTwoFileName, tokens[1].fileName);
    AssertAreEqual<int>(expectedHeaderType, static_cast<int>(tokens[1].headerType));
}

void TestSourceFileReader_ReadSourceFile_HeaderIncludes_FoundExternalTokens_TokensAreCorrect() {
    const size_t expectedHeaderTokenCount = 2;
    const auto expectedHeaderType = static_cast<int>(HeaderFileType::External);
    const string expectedHeaderOneFileName = "test_file_one.h";
    const string expectedHeaderTwoFileName = "test_file_two.h";
    const unsigned int expectedHeaderOneLineNumber = 6;
    const unsigned int expectedHeaderTwoLineNumber = 7;

    const string filePath = "./res/source_file_with_two_external_headers.cpp";
	vector<HeaderToken> tokens = GetTokensFromFile(filePath);

	AssertAreEqual<size_t>(expectedHeaderTokenCount, tokens.size());
	AssertAreEqual<size_t>(expectedHeaderOneLineNumber, tokens[0].lineNumber);
	AssertStringsAreEqual(expectedHeaderOneFileName, tokens[0].fileName);
	AssertAreEqual<int>(expectedHeaderType, static_cast<int>(tokens[0].headerType));
	AssertAreEqual<size_t>(expectedHeaderTwoLineNumber, tokens[1].lineNumber);
	AssertStringsAreEqual(expectedHeaderTwoFileName, tokens[1].fileName);
    AssertAreEqual<int>(expectedHeaderType, static_cast<int>(tokens[1].headerType));
}

void TestSourceFileReader_ReadSourceFile_HeaderIncludes_FoundExternalAndLocalTokens_TokensAreCorrect() {
    const size_t expectedHeaderTokenCount = 2;
    const auto expectedHeaderOneType = static_cast<int>(HeaderFileType::External);
    const auto expectedHeaderTwoType = static_cast<int>(HeaderFileType::Local);
    const string expectedHeaderOneFileName = "test_file_one.h";
    const string expectedHeaderTwoFileName = "test_file_two.h";
    const unsigned int expectedHeaderOneLineNumber = 2;
    const unsigned int expectedHeaderTwoLineNumber = 10;

    const string filePath = "./res/source_file_with_two_different_headers.cpp";
	vector<HeaderToken> tokens = GetTokensFromFile(filePath);

	AssertAreEqual<size_t>(expectedHeaderTokenCount, tokens.size());
	AssertAreEqual<size_t>(expectedHeaderOneLineNumber, tokens[0].lineNumber);
	AssertStringsAreEqual(expectedHeaderOneFileName, tokens[0].fileName);
	AssertAreEqual<int>(expectedHeaderOneType, static_cast<int>(tokens[0].headerType));
	AssertAreEqual<size_t>(expectedHeaderTwoLineNumber, tokens[1].lineNumber);
	AssertStringsAreEqual(expectedHeaderTwoFileName, tokens[1].fileName);
    AssertAreEqual<int>(expectedHeaderTwoType, static_cast<int>(tokens[1].headerType));
}

void TestSourceFileReader_ReadHeaderFile_HeaderIncludes_FoundExternalTokens_TokensAreCorrect() {
    const size_t expectedHeaderTokenCount = 1;
    const auto expectedHeaderType = static_cast<int>(HeaderFileType::Local);
    const string expectedHeaderFileName = "test_file_one.h";
    const unsigned int expectedHeaderLineNumber = 5;

    const string filePath = "./res/header_file_with_external_header.h";
	vector<HeaderToken> tokens = GetTokensFromFile(filePath);

	AssertAreEqual<size_t>(expectedHeaderTokenCount, tokens.size());
	AssertAreEqual<size_t>(expectedHeaderLineNumber, tokens[0].lineNumber);
	AssertStringsAreEqual(expectedHeaderFileName, tokens[0].fileName);
	AssertAreEqual<int>(expectedHeaderType, static_cast<int>(tokens[0].headerType));
}