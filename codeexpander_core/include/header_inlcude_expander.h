#pragma once

#include <vector>
#include <string>
#include "header_token.h"
#include "declarations.h"

namespace CodEXpander::Core {
    std::vector<std::string> GetCopyOfExpandedSourceFileContent(std::vector<std::string> fileContent, 
        std::vector<HeaderToken> foundHeaderIncludes, const std::string workingDirectory);

    void ExpandHeaderIncludes(std::vector<std::string> &fileContent, std::vector<HeaderToken> headerIncludes, 
        const std::string &workingDirectory);

    void ExpandHeaderInclude(std::vector<std::string> &fileContent, HeaderToken headerInclude, 
        const std::string &workingDirectory, u64 &linesOffset);
}