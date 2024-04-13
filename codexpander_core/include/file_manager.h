#pragma once

#include <string>
#include <vector>
#include "header_token.h"

namespace CodEXpander::Core {
    std::vector<std::string> ReadFileByLines(const std::string &filePath);

    bool TryWriteToFile(std::string filePath, std::vector<std::string> &expandedFileContent);
}