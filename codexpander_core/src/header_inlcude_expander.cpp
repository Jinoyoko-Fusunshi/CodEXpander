#include <iterator>
#include <fstream>
#include <algorithm>
#include <optional>
#include <filesystem>
#include "file_manager.h"
#include "header_inlcude_expander.h"

using std::vector, std::string, std::distance, std::ofstream, std::endl, std::find, std::optional, std::nullopt, std::filesystem::path;

namespace CodEXpander::Core {
    enum class IncludeTagType {
        None = 0,
        Start,
        End
    };

    struct IncludeEntry {
        u64 position;
        HeaderFileType headerType;
        IncludeTagType tagType;
    };

    u64 FindIncludeMacro(const string &line);

    optional<IncludeEntry> FindIncludeStartingTag(const string &line, u64 startPosition);

    optional<IncludeEntry> FindIncludeClosingTag(const string &line, u64 startPosition);

    IncludeEntry FindTag(const string &line, const string& tag, u64 startPosition,
        HeaderFileType headerType, IncludeTagType tagType);

    vector<string> ExpandHeaderIncludes(vector<string> &fileContent, vector<HeaderToken> headerIncludes, const string &workingDirectory) {
        u64 lineOffset = 0;

        for (auto headerInclude : headerIncludes)
            ExpandHeaderInclude(fileContent, headerInclude, workingDirectory, lineOffset);
    }

    void ExpandHeaderInclude(std::vector<std::string> &fileContent, HeaderToken headerInclude, const string &workingDirectory, u64 &linesOffset)  {
        vector<string> headerContent = GetHeaderContent(headerInclude, workingDirectory);
        u64 headerContentSize = headerContent.size();
        if (headerContentSize == 0)
            return;

        u64 includeIndex = (headerInclude.lineNumber - 1) + linesOffset;
        vector<string>::iterator includePosition = fileContent.begin() + includeIndex;
        fileContent.erase(includePosition);

        for (u64 i = 0; i < headerContentSize; i++) {
            vector<string>::iterator nextLinePosition = fileContent.begin() + includeIndex + i;
            u64 nextLineIndex = distance(fileContent.begin(), nextLinePosition);
            if (nextLineIndex >= fileContent.size())
                nextLinePosition = fileContent.end();

            string &currentLine = headerContent[i];
            fileContent.insert(nextLinePosition, std::move(currentLine));
        }

        linesOffset += headerContentSize;
    }
}