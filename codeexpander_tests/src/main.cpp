#include <vector>
#include "test_system.h"
#include "test_source_file_reader.h"

using namespace CodEXpander::Tests;
using std::vector, std::move;

vector<TestMethod> GetAllTests();

#define CreateNamedTestMethod(testMethodName) \
    CreateTestMethod(#testMethodName, testMethodName)

int main(int argumentCount, char* arguments[]) {
    vector<TestMethod> allTests = GetAllTests();
    RunTests(move(allTests));

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
        CreateNamedTestMethod(TestSourceFileReader_ReadHeaderFile_HeaderIncludes_FoundExternalTokens_TokensAreCorrect)
    };

    return std::move(tests);
}