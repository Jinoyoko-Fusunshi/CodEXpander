#pragma once

namespace CodEXpander::Tests {
    void TestSourceFileReader_ReadFileContent_NotExistingFile_EmptyContent();

    void TestSourceFileReader_ReadFileContent_ExistingFile_ContentIsCorrect();

    void TestSourceFileReader_ReadSourceFile_NoHeaderIncludes_FoundNoTokens();

    void TestSourceFileReader_ReadSourceFile_HeaderIncludes_FoundLocalTokens_TokensAreCorrect();

    void TestSourceFileReader_ReadSourceFile_HeaderIncludes_FoundExternalTokens_TokensAreCorrect();

    void TestSourceFileReader_ReadSourceFile_HeaderIncludes_FoundExternalAndLocalTokens_TokensAreCorrect();
    
    void TestSourceFileReader_ReadHeaderFile_HeaderIncludes_FoundExternalTokens_TokensAreCorrect();

    void TestSourceFileReader_ReadSourceFile_HeaderFileNotExists_GetHeaderContent_EmptyResult();

    void TestSourceFileReader_ReadSourceFile_HeaderFileExists_GetHeaderContent_ContentIsCorrect();
}