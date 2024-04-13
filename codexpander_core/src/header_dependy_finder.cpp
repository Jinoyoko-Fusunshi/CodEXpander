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
    void AddHeaderFileEntry(map<string, u64> &countedHeaderFiles, HeaderFileIncludes &headerFile);

    HeaderDependencyGraph::HeaderDependencyGraph(const string &sourceFileName, const string &workingDirectory) {
        HeaderToken token = {
            .fileName = sourceFileName,
            .lineNumber = 0,
            .headerType = HeaderFileType::Local
        };
        
        headerIncludes.headerFile = token;
        AddHeaderFiles(headerIncludes, sourceFileName, workingDirectory);
    }

    void HeaderDependencyGraph::AddHeaderFiles(HeaderFileIncludes &parentHeader, const string &fileName, const string &workingDirectory) {
        auto filterHeaderFiles = [fileName](HeaderFileIncludes include) {
            return include.headerFile.fileName.compare(fileName) == 0;
        };
        auto filteredHeaders = foundHeaderFiles | filter(filterHeaderFiles);
        vector<HeaderFileIncludes> existingHeaderFiles(filteredHeaders.begin(), filteredHeaders.end());
        vector<HeaderFileIncludes> childHeaders;
        if (existingHeaderFiles.size() != 0) {
            auto existingHeaderFile = existingHeaderFiles[0];
            childHeaders = vector(existingHeaderFile.innerIncludes.begin(), existingHeaderFile.innerIncludes.end());
        } else {
            auto headerTokens = GetTokensFromFile(fileName);
            for (auto token : headerTokens) {
                HeaderFileIncludes childHeader = {
                    .headerFile = token
                };
                childHeaders.emplace_back(childHeader);
            }
        }

        for (auto childHeader : childHeaders) {
            auto childHeaderFileName = workingDirectory + "include/" + childHeader.headerFile.fileName;
            AddHeaderFiles(childHeader, childHeaderFileName, workingDirectory);
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

    vector<string> HeaderDependencyGraph::GetHeaderFilesSortedByOccurences() {
        map<string, u64> haederFilesByIncludeCount = CountHeaderOccurences();
        vector<pair<string, u64>> countedHeaderFilesPairs;
        for (auto headerFileCountPair : haederFilesByIncludeCount)
            countedHeaderFilesPairs.emplace_back(headerFileCountPair);

        auto sortHeaderFilesByCount = [](pair<string, u64> current, pair<string, u64> next) {
            return current.second >= next.second;
        };

        sort(countedHeaderFilesPairs.begin(), countedHeaderFilesPairs.end(), sortHeaderFilesByCount);
        vector<string> sortedHeaderFiles;
        for (auto headerFileCountPair : countedHeaderFilesPairs) {
            auto headerFileName = headerFileCountPair.first;
            sortedHeaderFiles.emplace_back(std::move(headerFileName));
        }

        return std::move(sortedHeaderFiles);
    }

    map<string, u64> HeaderDependencyGraph::CountHeaderOccurences() {
        map<string, u64> headerFilesByIncludeCount;
        AddHeaderFileEntry(headerFilesByIncludeCount, headerIncludes);  
        return std::move(headerFilesByIncludeCount);
    }

    void AddHeaderFileEntry(map<string, u64> &countedHeaderFiles, HeaderFileIncludes &headerInclude) {
        if (headerInclude.innerIncludes.size() != 0) {
            for (auto innerInclude : headerInclude.innerIncludes)
                AddHeaderFileEntry(countedHeaderFiles, innerInclude);
        }

        auto headerFileName = headerInclude.headerFile.fileName;
        if (countedHeaderFiles.contains(headerInclude.headerFile.fileName)) {
            u64 &headerFileCount = countedHeaderFiles[headerFileName];
            headerFileCount += 1;
            return;
        }

        auto newPair = std::make_pair<string, u64>(std::move(headerInclude.headerFile.fileName), 1);
        countedHeaderFiles.insert(std::move(newPair));
    }
}