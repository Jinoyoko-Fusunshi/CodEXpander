#pragma once

#include <string>
#include <vector>
#include "header_token.h"

namespace CodEXpander::Core {
    std::vector<std::string> ReadFileByLines(const std::string& filePath);

    std::vector<HeaderToken> GetTokensFromFile(const std::string& filePath);

    std::vector<std::string> GetHeaderContent(const HeaderToken headerToken, const std::string workingDirectory);

    bool TryWriteToFile(std::string filePath, std::vector<std::string> &expandedFileContent);
}