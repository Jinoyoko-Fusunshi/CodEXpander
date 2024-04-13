#pragma once

namespace CodEXpander::Tests {
    void TestFileManager_ReadFilesByLines_NotExistingFile_EmptyContent();

    void TestFileManager_ReadFilesByLines_ExistingFile_ContentIsCorrect();

    void TestFileManager_TryWriteToFile_NoFilePath_NotWritingToFile();

    void TestFileManager_TryWriteToFile_NoFileContent_NotWritingToFile();

    void TestFileManager_TryWriteToFile_ValidPathAndContent_WritesToFile();
}