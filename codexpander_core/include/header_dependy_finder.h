#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
#include "declarations.h"
#include "header_token.h"
#include "header_inlcude_expander.h"
#include "file_manager.h"

namespace CodEXpander::Core {
    struct HeaderFileIncludes {
        HeaderToken headerFile;
        std::vector<HeaderFileIncludes> innerIncludes;
    };

    struct HeaderFileCount {
        HeaderFile headerFile;
        u64 occurenceCount;
    };

    using HeaderCountDictionary = std::map<std::string, HeaderFileCount>;

    class HeaderDependencyGraph final {
    private:
        std::vector<HeaderFileIncludes> foundHeaderFiles;
        HeaderFileIncludes headerIncludes;

        void AddHeaderFiles(HeaderFileIncludes &parentHeader, const std::string &fileName, const std::string &workingDirectory);

    public:
        HeaderDependencyGraph() = default;
        explicit HeaderDependencyGraph(const std::string &sourceFileName, const std::string &workingDirectory);
        ~HeaderDependencyGraph() = default;

        void RegisterHeader(HeaderFileIncludes headerFile);
        std::vector<HeaderFile> GetHeaderFilesSortedByOccurences();
        HeaderCountDictionary CountHeaderOccurences();
    };
}