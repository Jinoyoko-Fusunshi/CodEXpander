#include <vector>
#include "test_system.h"
#include "test_file_manager.h"
#include "test_header_include_expander.h"
#include "test_command_parser.h"

using namespace CodEXpander::Tests;
using std::vector;

vector<TestMethod> GetAllTests();

#define CreateNamedTestMethod(testMethodName) TestSystem::CreateTestMethod(#testMethodName, testMethodName)

int main(int argumentCount, char* arguments[]) {
    const vector<TestMethod> allTests = GetAllTests();
    
    TestSystem testSystem;
    testSystem.AddTests(allTests);
    
    return testSystem.RunTests();
}

vector<TestMethod> GetAllTests() {
    return vector<TestMethod> {
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

        CreateNamedTestMethod(TestCommandParser_TryParseCommand_NoCommandsProvided_NoCommandFound),
        CreateNamedTestMethod(TestCommandParser_TryParseCommand_NoCommandsProvided_ArgumentsProvided_NoCommandFound),
        CreateNamedTestMethod(TestCommandParser_TryParseCommand_CommandAndArgumentsProvided_CommandNotExisting_CommandNotFound),
        CreateNamedTestMethod(TestCommandParser_TryParseCommand_CommandAndArgumentsProvided_CommandExist_CommandWasFound)
    };
}