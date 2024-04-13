#pragma once

#include <vector>
#include <string>
#include "header_token.h"
#include "declarations.h"

namespace CodEXpander::Core {
    std::vector<std::string> ExpandHeaderIncludes(std::string &sourceFile, std::vector<HeaderToken> headerFiles, const std::string &workingDirectory);

    void ExpandHeaderInclude(std::vector<std::string> &fileContent, HeaderToken &headerFile, const std::string &workingDirectory, u64 lineIndex, u64 &linesOffset);

    std::vector<HeaderToken> GetTokensFromFile(const std::string &filePath);

    bool TryGetHeaderToken(std::string &line, u64 lineNumber, HeaderToken &foundHeaderToken);
}