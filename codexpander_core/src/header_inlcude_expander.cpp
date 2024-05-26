#include <iterator>
#include <fstream>
#include <algorithm>
#include <optional>
#include <filesystem>
#include "file_manager.h"
#include "header_inlcude_expander.h"

using std::vector, std::string, std::distance, std::ofstream, std::endl, std::find, std::optional, std::nullopt, std::filesystem::path;

namespace CodEXpander::Core {
    enum class IncludeTagPosition {
        None = 0,
        Start,
        End
    };

    struct IncludeTag final {
        u64 position;
        HeaderFileType headerType;
        IncludeTagPosition tagType;
    };

    struct IncludeTagDefinition final {
        string startingTag;
        string closingTag;
        HeaderFileType headerType;
    };

    const u64 FindIncludeMacro(const string &line);
    const optional<IncludeTag> FindIncludeStartingTag(const string &line, const u64 startPosition);
    const optional<IncludeTag> FindIncludeClosingTag(const string &line, const u64 startPosition);
    const u64 FindTagPosition(const string &line, const string& tag, const u64 startPosition);

    const IncludeTagDefinition localIncludeTag = {
        .startingTag = "\"",
        .closingTag = "\"",
        .headerType = HeaderFileType::Local
    };

    const IncludeTagDefinition systemIncludeTag = {
        .startingTag = "<",
        .closingTag = ">",
        .headerType = HeaderFileType::System
    };

    void ExpandHeaderInclude(vector<string> &fileContent, const HeaderFile &headerFile, const string &workingDirectory, const u64 lineIndex, u64 &linesOffset)  {
        vector<string> headerContent = GetHeaderContent(headerFile, workingDirectory);
        const u64 headerContentSize = headerContent.size();
        if (headerContentSize == 0)
            return;

        int copiedLinesCount = 0;
        for (u64 i = 0; i < headerContentSize; i++) {
            auto nextLinePosition = fileContent.begin() + lineIndex + copiedLinesCount;
            const u64 nextLineIndex = distance(fileContent.begin(), nextLinePosition);
            if (nextLineIndex >= fileContent.size())
                nextLinePosition = fileContent.end();

            const long currentLineNumber = i + 1;
            string &currentLine = headerContent[i];
            if (HeaderToken token; TryGetHeaderToken(currentLine, currentLineNumber, token))
                continue;

            if (string pragmaValue; TryGetPrgramaDirective(currentLine, currentLineNumber, pragmaValue)) {
                if (pragmaValue.compare("once") == 0)
                    continue;
            }
                
            fileContent.insert(nextLinePosition, std::move(currentLine));
            copiedLinesCount += 1;
        }

        linesOffset += copiedLinesCount;
    }

    const vector<string> ExpandHeaderIncludes(const string &sourceFile, vector<HeaderFile> headerFiles, const string &workingDirectory) {
        u64 lineOffset = 0;
        const vector<HeaderToken> headerTokens = GetTokensFromFile(sourceFile);
        if (headerTokens.size() == 0)
            return vector<string>();

        vector<string> sourceFileContent = ReadFileByLines(sourceFile);
        long expansionStartLineIndex = -1;

        for (const auto &headerToken : headerTokens) {
            if (headerToken.headerType == HeaderFileType::System)
                continue;

            const long lineIndex = headerToken.lineNumber - lineOffset -1;
            if (headerToken.headerType == HeaderFileType::Local && expansionStartLineIndex == -1)
                expansionStartLineIndex = lineIndex;

            const auto linePosition = sourceFileContent.begin() + lineIndex;
            sourceFileContent.erase(linePosition);
            lineOffset += 1;
        }

        lineOffset = 0;
        for (const auto &headerFile : headerFiles)
            ExpandHeaderInclude(sourceFileContent, headerFile, workingDirectory, expansionStartLineIndex + lineOffset, lineOffset);

        return std::move(sourceFileContent);
    }

    const vector<HeaderToken> GetTokensFromFile(const string &filePath) {
        vector<HeaderToken> foundTokens;
        vector<string> fileContentByLines = ReadFileByLines(filePath);

        for (u64 i = 0; i < fileContentByLines.size(); i++) {
            string &currentLine = fileContentByLines[i];
            
            HeaderToken foundHeaderToken;
            if (!TryGetHeaderToken(currentLine, i + 1, foundHeaderToken))
                continue;

            foundTokens.emplace_back(foundHeaderToken);
        }

        return std::move(foundTokens);
    }

    const vector<string> GetHeaderContent(const HeaderFile &headerFile, const string &workingDirectory) {
        const string includeDirectory = workingDirectory + "/include";
        vector<string> headerContent; 
        path includePath(includeDirectory);
        if (!exists(includePath))
            return std::move(headerContent);
        
        const string relativeHeaderFilePath = includeDirectory + "/" + headerFile.fileName;
        const path headerFilePath(relativeHeaderFilePath);
        if (!exists(headerFilePath))
            return std::move(headerContent);
        
        const vector<string> fileContent = ReadFileByLines(relativeHeaderFilePath);
        if (fileContent.size() == 0)
            return std::move(headerContent);

        headerContent = fileContent; 
        return std::move(headerContent);
    }

    const bool TryGetHeaderToken(const string &line, const u64 lineNumber, HeaderToken &foundHeaderToken) {
        const u64 includePosition = FindIncludeMacro(line);
        if (includePosition == string::npos)
            return false;

        optional<IncludeTag> startingTagResult = FindIncludeStartingTag(line, includePosition);
        if (!startingTagResult)
            return false;

        const IncludeTag startingTag = startingTagResult.value();
        optional<IncludeTag> closingTagResult = FindIncludeClosingTag(line, startingTag.position + 1);
        if (!closingTagResult)
            return false;

        const IncludeTag closingTag = closingTagResult.value();
        if (startingTag.position >= closingTag.position || startingTag.headerType != closingTag.headerType)
            return false;

        const long headerFileNameLength = (closingTag.position - 1) - startingTag.position;
        const string headerFileName = line.substr(startingTag.position + 1, headerFileNameLength);

        foundHeaderToken = HeaderToken(headerFileName, closingTag.headerType, lineNumber);
        return true;
    }

    const bool TryGetPrgramaDirective(const std::string &line, const u64 lineNumber, std::string &foundDirective) {
        const string pragmaMacroStatement = "#pragma";
        const u64 pragmaMacroPosition = line.find(pragmaMacroStatement);

        if (pragmaMacroPosition == string::npos)
            return false;

        const u64 pragmaStatementSize = pragmaMacroStatement.size();
        if (line.size() == pragmaStatementSize)
            return false;

        const u64 pragmaValueSize = line.size() - 1 - pragmaStatementSize;
        foundDirective = line.substr(pragmaStatementSize + 1, pragmaValueSize);
        return true;
    }

    const u64 FindIncludeMacro(const string &line) {
        const string includeMacroStatement = "#include";
        const u64 includeMacroPosition = line.find(includeMacroStatement);
        return includeMacroPosition;
    }

    const optional<IncludeTag> FindIncludeStartingTag(const string &line, const u64 startPosition) {   
        if (const u64 localStartingTag = FindTagPosition(line, localIncludeTag.startingTag, startPosition); localStartingTag != string::npos) {
            return IncludeTag {
                .position = localStartingTag,
                .headerType = localIncludeTag.headerType,
            };
        }

        if (const u64 externalStartingTag = FindTagPosition(line, systemIncludeTag.startingTag, startPosition); externalStartingTag != string::npos) {
            return IncludeTag {
                .position = externalStartingTag,
                .headerType = systemIncludeTag.headerType,
            };
        }

        return nullopt;
    }

    const optional<IncludeTag> FindIncludeClosingTag(const string &line, const u64 startPosition) {   
        if (const u64 localClosingTagPosition = FindTagPosition(line, localIncludeTag.closingTag, startPosition); localClosingTagPosition != string::npos) {
            return IncludeTag {
                .position = localClosingTagPosition,
                .headerType = localIncludeTag.headerType,
            };
        }

        if (const u64 externalClosingTagPosition = FindTagPosition(line, systemIncludeTag.closingTag, startPosition); externalClosingTagPosition != string::npos) {
            return IncludeTag {
                .position = externalClosingTagPosition,
                .headerType = systemIncludeTag.headerType,
            };
        }

        return nullopt;
    }

    const u64 FindTagPosition(const string &line, const string& tag, const u64 startPosition) {
        const u64 tagPosition = line.find(tag, startPosition);
        return tagPosition;
    }
}