#pragma once

namespace CodEXpander::Tests {
    void TestHeaderIncludeExpander_GetTokensFromFiles_NoHeaderIncludes_FoundNoTokens();

    void TestHeaderIncludeExpander_GetTokensFromFile_FoundLocalTokens_TokensAreCorrect();

    void TestHeaderIncludeExpander_GetTokensFromFile_FoundExternalTokens_TokensAreCorrect();

    void TestHeaderIncludeExpander_GetTokensFromFile_FoundTwoExternalTokens_TokensAreCorrect();

    void TestHeaderIncludeExpander_GetTokensFromFile_FoundExternalAndLocalTokens_TokensAreCorrect();

    void TestHeaderIncludeExpander_GetTokensFromFile_HeaderFileNotExists_GetHeaderContent_EmptyResult();

    void TestHeaderIncludeExpander_GetTokensFromFile_HeaderFileExists_GetHeaderContent_ContentIsCorrect();

    void TestHeaderIncludeExpander_ExpandHeaderIncludes_NoInlcudes_FileContentIsEqual();

    void TestHeaderIncludeExpander_ExpandHeaderIncludes_OneInlcude_NewFileContentIsCorrect();
}