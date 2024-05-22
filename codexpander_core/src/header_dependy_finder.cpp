#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
#include "declarations.h"
#include "header_token.h"
#include "header_inlcude_expander.h"
#include "file_manager.h"
#include "header_dependy_finder.h"

using std::vector, std::string, std::map, std::views::filter, std::pair, std::make_pair;

namespace CodEXpander::Core {
    void AddHeaderFileEntry(HeaderCountDictionary &countedHeaderFiles, HeaderFileIncludes &headerFile);

    HeaderDependencyGraph::HeaderDependencyGraph(const string &sourceFileName, const string &workingDirectory) {
        headerIncludes.headerFile = HeaderToken(sourceFileName, HeaderFileType::Local, 0);
        AddHeaderFiles(headerIncludes, sourceFileName, workingDirectory);
    }

    void HeaderDependencyGraph::AddHeaderFiles(HeaderFileIncludes &parentHeader, const string &fileName, const string &workingDirectory) {
        const auto filterHeaderFiles = [fileName](HeaderFileIncludes include) {
            return include.headerFile.fileName.compare(fileName) == 0;
        };
        auto filteredHeaders = foundHeaderFiles | filter(filterHeaderFiles);
        vector<HeaderFileIncludes> existingHeaderFiles(filteredHeaders.begin(), filteredHeaders.end());
        vector<HeaderFileIncludes> childHeaders;
        if (existingHeaderFiles.size() != 0) {
            auto existingHeaderFile = existingHeaderFiles[0];
            childHeaders = vector(existingHeaderFile.innerIncludes.begin(), existingHeaderFile.innerIncludes.end());
        } else {
            const auto headerTokens = GetTokensFromFile(fileName);
            for (const auto &token : headerTokens) {
                const HeaderFileIncludes childHeader = {
                    .headerFile = std::move(token)
                };
                childHeaders.emplace_back(std::move(childHeader));
            }
        }

        for (auto &childHeader : childHeaders) {
            const auto childHeaderFileName = workingDirectory + "include/" + childHeader.headerFile.fileName;
            AddHeaderFiles(childHeader, std::move(childHeaderFileName), workingDirectory);
            parentHeader.innerIncludes.emplace_back(childHeader);
            RegisterHeader(childHeader);
        }
    }

    void HeaderDependencyGraph::RegisterHeader(HeaderFileIncludes currentHeaderFile) {
        for (auto headerFile : foundHeaderFiles) {
            if (headerFile.headerFile.fileName.compare(currentHeaderFile.headerFile.fileName) == 0)
                return;
        }

        foundHeaderFiles.emplace_back(currentHeaderFile);
    }

    vector<HeaderFile> HeaderDependencyGraph::GetHeaderFilesSortedByOccurences() {
        const HeaderCountDictionary haederFilesByIncludeCount = CountHeaderOccurences();
        vector<pair<string, HeaderFileCount>> countedHeaderFilesPairs;
        for (const auto &headerFileCountPair : haederFilesByIncludeCount)
            countedHeaderFilesPairs.emplace_back(headerFileCountPair);

        const auto sortHeaderFilesByCount = [](pair<string, HeaderFileCount> current, pair<string, HeaderFileCount> next) {
            return current.second.occurenceCount >= next.second.occurenceCount;
        };

        sort(countedHeaderFilesPairs.begin(), countedHeaderFilesPairs.end(), sortHeaderFilesByCount);
        vector<HeaderFile> sortedHeaderFiles;
        for (const auto &headerFileCountPair : countedHeaderFilesPairs) {
            HeaderFile headerFile = headerFileCountPair.second.headerFile;
            sortedHeaderFiles.emplace_back(headerFile);
        }

        return std::move(sortedHeaderFiles);
    }

    HeaderCountDictionary HeaderDependencyGraph::CountHeaderOccurences() {
        HeaderCountDictionary headerFilesByIncludeCount;
        AddHeaderFileEntry(headerFilesByIncludeCount, headerIncludes);  
        return std::move(headerFilesByIncludeCount);
    }

    void AddHeaderFileEntry(HeaderCountDictionary &countedHeaderFiles, HeaderFileIncludes &headerInclude) {
        if (headerInclude.innerIncludes.size() != 0) {
            for (auto innerInclude : headerInclude.innerIncludes)
                AddHeaderFileEntry(countedHeaderFiles, innerInclude);
        }

        string headerFileName = headerInclude.headerFile.fileName;
        if (countedHeaderFiles.contains(headerFileName)) {
            u64 &headerFileCount = countedHeaderFiles[headerFileName].occurenceCount;
            headerFileCount += 1;
            return;
        }

        HeaderFileCount fileCount = {
            .headerFile = headerInclude.headerFile,
            .occurenceCount = 1
        };
        const auto newPair = std::make_pair<string, HeaderFileCount>(std::move(headerFileName), std::move(fileCount));
        countedHeaderFiles.insert(std::move(newPair));
    }
}