#pragma once

#include <vector>
#include <string>
#include "header_token.h"
#include "declarations.h"

namespace CodEXpander::Core {
    std::vector<std::string> ExpandHeaderIncludes(std::string &sourceFile, std::vector<std::string> headerFiles, const std::string &workingDirectory);

    void ExpandHeaderInclude(std::vector<std::string> &fileContent, std::string &headerFile, const std::string &workingDirectory, u64 lineIndex, u64 &linesOffset);

    std::vector<HeaderToken> GetTokensFromFile(const std::string &filePath);

    bool TryGetHeaderToken(std::string &line, u64 lineNumber, HeaderToken &foundHeaderToken);

    bool TryGetPrgramaDirective(std::string &line, u64 lineNumber, std::string &foundDirective);

    std::vector<std::string> GetHeaderContent(const std::string &headerFileName, const std::string &workingDirectory);
}