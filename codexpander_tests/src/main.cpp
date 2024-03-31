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
        CreateNamedTestMethod(TestSourceFileReader_ReadFileContent_NotExistingFile_EmptyContent),
        CreateNamedTestMethod(TestSourceFileReader_ReadFileContent_ExistingFile_ContentIsCorrect),
        CreateNamedTestMethod(TestSourceFileReader_ReadSourceFile_NoHeaderIncludes_FoundNoTokens),
        CreateNamedTestMethod(TestSourceFileReader_ReadSourceFile_HeaderIncludes_FoundLocalTokens_TokensAreCorrect),
        CreateNamedTestMethod(TestSourceFileReader_ReadSourceFile_HeaderIncludes_FoundExternalTokens_TokensAreCorrect),
        CreateNamedTestMethod(TestSourceFileReader_ReadSourceFile_HeaderIncludes_FoundExternalAndLocalTokens_TokensAreCorrect),
        CreateNamedTestMethod(TestSourceFileReader_ReadHeaderFile_HeaderIncludes_FoundExternalTokens_TokensAreCorrect),
        CreateNamedTestMethod(TestSourceFileReader_ReadSourceFile_HeaderFileNotExists_GetHeaderContent_EmptyResult),
        CreateNamedTestMethod(TestSourceFileReader_ReadSourceFile_HeaderFileExists_GetHeaderContent_ContentIsCorrect),

        CreateNamedTestMethod(TestSourceFileExpander_ExpandHeaderIncludes_NoInlcudes_FileContentIsEqual),
        CreateNamedTestMethod(TestSourceFileExpander_ExpandHeaderIncludes_OneInlcude_NewFileContentIsCorrect),
        CreateNamedTestMethod(TestSourceFileReader_TryWriteToFile_NoFilePath_NotWritingToFile),
        CreateNamedTestMethod(TestSourceFileReader_TryWriteToFile_NoFileContent_NotWritingToFile),
        CreateNamedTestMethod(TestSourceFileReader_TryWriteToFile_ValidPathAndContent_WritesToFile),

        CreateNamedTestMethod(TestCommandParser_ParseArguments_StringIsEmpty_NoArguments),
        CreateNamedTestMethod(TestCommandParser_ParseArguments_ArgumentWithOnePrexifSymbol_ReturnsNoArguments),
        CreateNamedTestMethod(TestCommandParser_ParseArguments_ArgumentWithBothPrefixSymbol_ReturnsOneArgument),
        CreateNamedTestMethod(TestCommandParser_ParseArguments_TwoArgumentsPresent_ReturnsTwoArguments)
    };

    return std::move(tests);
}