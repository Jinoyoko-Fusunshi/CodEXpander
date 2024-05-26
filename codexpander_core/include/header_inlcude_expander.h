#pragma once

#include <vector>
#include <string>
#include "header_token.h"
#include "declarations.h"

namespace CodEXpander::Core {
    void ExpandHeaderInclude(std::vector<std::string> &fileContent, const HeaderFile &headerFile, const std::string &workingDirectory, const u64 lineIndex, u64 &linesOffset);
    const std::vector<std::string> ExpandHeaderIncludes(const std::string &sourceFile, std::vector<HeaderFile> headerFiles, const std::string &workingDirectory);
    const std::vector<HeaderToken> GetTokensFromFile(const std::string &filePath);
    const std::vector<std::string> GetHeaderContent(const HeaderFile &headerFile, const std::string &workingDirectory);
    const bool TryGetHeaderToken(const std::string &line, u64 lineNumber, HeaderToken &foundHeaderToken);
    const bool TryGetPrgramaDirective(const std::string &line, u64 lineNumber, std::string &foundDirective);
}