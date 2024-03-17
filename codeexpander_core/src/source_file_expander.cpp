#include <iterator>
#include "source_file_expander.h"
#include "source_file_reader.h"

using std::vector, std::string, std::distance;

namespace CodEXpander::Core {
    vector<string> GetCopyOfExpandedSourceFileContent(vector<string> fileContent, vector<HeaderToken> foundHeaderIncludes) {
        return vector<string>();
    }

    void ReplaceIncludeStatementWithHeaderContent(vector<string> &fileContent, const HeaderToken headerInclude, 
        const string workingDirectory, size_t &linesOffset) {
        vector<string> headerContent = GetHeaderContent(headerInclude, workingDirectory);
        size_t headerContentSize = headerContent.size();
        if (headerContentSize == 0)
            return;

        size_t includeIndex = (headerInclude.lineNumber - 1) + linesOffset;
        vector<string>::iterator includePosition = fileContent.begin() + includeIndex;
        fileContent.erase(includePosition);

        for (size_t i = 0; i < headerContentSize; i++) {
            vector<string>::iterator nextLinePosition = fileContent.begin() + includeIndex + i;
            size_t nextLineIndex = distance(fileContent.begin(), nextLinePosition);
            if (nextLineIndex >= fileContent.size())
                nextLinePosition = fileContent.end();

            string &currentLine = headerContent[i];
            fileContent.insert(nextLinePosition, std::move(currentLine));
        }

        linesOffset += headerContentSize;
    }

    void WriteExpandedSourceFileInTempFile(string filePath, string expandedFileContent) {
        
    }
}