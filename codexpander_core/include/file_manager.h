#pragma once

#include <string>
#include <vector>
#include "header_token.h"

namespace CodEXpander::Core {
    std::vector<std::string> ReadFileByLines(const std::string &filePath);

    bool TryWriteToFile(const std::string &filePath, const std::vector<std::string> &expandedFileContent);
}