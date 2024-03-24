#include <iterator>
#include "source_file_expander.h"
#include "source_file_reader.h"

using std::vector, std::string, std::distance;

namespace CodEXpander::Core {
    vector<string> GetCopyOfExpandedSourceFileContent(vector<string> fileContent, vector<HeaderToken> foundHeaderIncludes) {
        return vector<string>();
    }

    void ReplaceIncludeStatementWithHeaderContent(vector<string> &fileContent, const HeaderToken headerInclude, 
        const string workingDirectory, u64 &linesOffset) {
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

    void WriteExpandedSourceFileInTempFile(string filePath, string expandedFileContent) {
        
    }
}