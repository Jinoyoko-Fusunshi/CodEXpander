#pragma once

#include <string>
#include <vector>

namespace CodEXpander::Core {
    enum class HeaderFileType {
        System,
        Local,
        External
    };

    struct HeaderToken {
        std::string fileName;
        unsigned int lineNumber;
        HeaderFileType headerType;
    };

    std::vector<std::string> ReadFileByLines(const std::string& filePath);

    std::vector<HeaderToken> GetTokensFromFile(const std::string& filePath);
}