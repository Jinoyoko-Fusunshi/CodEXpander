#include <vector>
#include "test_system.h"
#include "test_file_manager.h"
#include "test_header_include_expander.h"
#include "test_command_parser.h"

using namespace CodEXpander::Tests;
using std::vector;

vector<TestMethod> GetAllTests();

#define CreateNamedTestMethod(testMethodName) CreateTestMethod(#testMethodName, testMethodName)

int main(int argumentCount, char* arguments[]) {
    vector<TestMethod> allTests = GetAllTests();
    RunTests(std::move(allTests));

    return 0;
}

vector<TestMethod> GetAllTests() {
    vector<TestMethod> tests = {
        CreateNamedTestMethod(TestFileManager_ReadFilesByLines_NotExistingFile_EmptyContent),
        CreateNamedTestMethod(TestFileManager_ReadFilesByLines_ExistingFile_ContentIsCorrect),
        CreateNamedTestMethod(TestFileManager_TryWriteToFile_NoFilePath_NotWritingToFile),
        CreateNamedTestMethod(TestFileManager_TryWriteToFile_NoFileContent_NotWritingToFile),
        CreateNamedTestMethod(TestFileManager_TryWriteToFile_ValidPathAndContent_WritesToFile),
        
        CreateNamedTestMethod(TestHeaderIncludeExpander_GetTokensFromFiles_NoHeaderIncludes_FoundNoTokens),
        CreateNamedTestMethod(TestHeaderIncludeExpander_GetTokensFromFile_FoundLocalTokens_TokensAreCorrect),
        CreateNamedTestMethod(TestHeaderIncludeExpander_GetTokensFromFile_FoundExternalTokens_TokensAreCorrect),
        CreateNamedTestMethod(TestHeaderIncludeExpander_GetTokensFromFile_FoundTwoExternalTokens_TokensAreCorrect),
        CreateNamedTestMethod(TestHeaderIncludeExpander_GetTokensFromFile_FoundExternalAndLocalTokens_TokensAreCorrect),
        CreateNamedTestMethod(TestHeaderIncludeExpander_GetTokensFromFile_FoundExternalTokens_TokensAreCorrect),
        CreateNamedTestMethod(TestHeaderIncludeExpander_GetTokensFromFile_HeaderFileNotExists_GetHeaderContent_EmptyResult),
        CreateNamedTestMethod(TestHeaderIncludeExpander_GetTokensFromFile_HeaderFileExists_GetHeaderContent_ContentIsCorrect),
        CreateNamedTestMethod(TestHeaderIncludeExpander_ExpandHeaderIncludes_NoInlcudes_FileContentIsEqual),
        CreateNamedTestMethod(TestHeaderIncludeExpander_ExpandHeaderIncludes_OneInlcude_NewFileContentIsCorrect),

        CreateNamedTestMethod(TestCommandParser_ParseArguments_StringIsEmpty_NoArguments),
        CreateNamedTestMethod(TestCommandParser_ParseArguments_ArgumentWithOnePrexifSymbol_ReturnsNoArguments),
        CreateNamedTestMethod(TestCommandParser_ParseArguments_ArgumentWithBothPrefixSymbol_ReturnsOneArgument),
        CreateNamedTestMethod(TestCommandParser_ParseArguments_TwoArgumentsPresent_ReturnsTwoArguments),

        CreateNamedTestMethod(TestCommandParser_TryGetExistingArgument_NameIsEmpty_ReturnsFalse),
        CreateNamedTestMethod(TestCommandParser_TryGetExistingArgument_NameIsValid_ArgumentDoesNotExist_ReturnsFalse),
        CreateNamedTestMethod(TestCommandParser_TryGetExistingArgument_NameIsValid_ArgumentDoesExist_ReturnsArgument),
        CreateNamedTestMethod(TestCommandParser_TryGetExistingArgument_ArgumentDoesExist_ValueIsEmpty_ReturnsFalse)
    };

    return std::move(tests);
}