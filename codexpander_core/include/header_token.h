#pragma once

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
}