#include <iterator>
#include <fstream>
#include "file_manager.h"
#include "header_inlcude_expander.h"

using std::vector, std::string, std::distance, std::ofstream, std::endl;

namespace CodEXpander::Core {
    vector<string> GetCopyOfExpandedSourceFileContent(vector<string> fileContent, vector<HeaderToken> foundHeaderIncludes, const string workingDirectory) {
        vector<string> replacedFileContent(fileContent);
        ExpandHeaderIncludes(replacedFileContent, std::move(foundHeaderIncludes), workingDirectory);

        return std::move(replacedFileContent);
    }

    void ExpandHeaderIncludes(vector<string> &fileContent, vector<HeaderToken> headerIncludes, const string &workingDirectory) {
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