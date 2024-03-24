#pragma once

#include <vector>
#include <string>
#include "header_token.h"
#include "declarations.h"

namespace CodEXpander::Core {
    std::vector<std::string> GetCopyOfExpandedSourceFileContent(std::vector<std::string> fileContent, 
        std::vector<HeaderToken> foundHeaderIncludes);

    void ReplaceIncludeStatementWithHeaderContent(std::vector<std::string> &fileContent, HeaderToken headerInclude, 
        const std::string workingDirectory, u64 &linesOffset);

    void WriteExpandedSourceFileInTempFile(std::string filePath, std::string expandedFileContent);
}