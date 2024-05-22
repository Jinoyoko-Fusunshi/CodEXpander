#pragma once

#include "declarations.h"

namespace CodEXpander::Core {
    enum class HeaderFileType {
        System,
        Local,
        External
    };

    struct HeaderFile {
        std::string fileName = "";
        HeaderFileType headerType = HeaderFileType::Local;

        HeaderFile() = default;
        explicit HeaderFile(std::string fileName, HeaderFileType headerType) : fileName(fileName), headerType(headerType) {}
    };

    struct HeaderToken final : public HeaderFile {
        u64 lineNumber = 0;

        HeaderToken() = default;
        explicit HeaderToken(std::string fileName, HeaderFileType headerType, u64 lineNumber) 
            : HeaderFile(fileName, headerType), lineNumber(lineNumber) {}
    };
}