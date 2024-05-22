#pragma once

#include <vector>
#include <string>
#include "header_token.h"
#include "declarations.h"

namespace CodEXpander::Core {
    std::vector<std::string> ExpandHeaderIncludes(const std::string &sourceFile, std::vector<HeaderFile> headerFiles, const std::string &workingDirectory);

    void ExpandHeaderInclude(std::vector<std::string> &fileContent, HeaderFile &headerFile, const std::string &workingDirectory, u64 lineIndex, u64 &linesOffset);

    std::vector<HeaderToken> GetTokensFromFile(const std::string &filePath);

    bool TryGetHeaderToken(std::string &line, u64 lineNumber, HeaderToken &foundHeaderToken);

    bool TryGetPrgramaDirective(std::string &line, u64 lineNumber, std::string &foundDirective);

    std::vector<std::string> GetHeaderContent(const HeaderFile &headerFile, const std::string &workingDirectory);
}