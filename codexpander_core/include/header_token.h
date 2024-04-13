#pragma once

#include "declarations.h"

namespace CodEXpander::Core {
    enum class HeaderFileType {
        System,
        Local,
        External
    };

    struct HeaderToken {
        std::string fileName;
        u64 lineNumber;
        HeaderFileType headerType;
    };
}