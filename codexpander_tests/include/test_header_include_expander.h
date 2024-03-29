#pragma once

namespace CodEXpander::Tests {
    void TestSourceFileExpander_ExpandHeaderIncludes_NoInlcudes_FileContentIsEqual();

    void TestSourceFileExpander_ExpandHeaderIncludes_OneInlcude_NewFileContentIsCorrect();

    void TestSourceFileReader_TryWriteToFile_NoFilePath_NotWritingToFile();

    void TestSourceFileReader_TryWriteToFile_NoFileContent_NotWritingToFile();

    void TestSourceFileReader_TryWriteToFile_ValidPathAndContent_WritesToFile();
}