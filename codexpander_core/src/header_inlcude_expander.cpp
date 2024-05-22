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

    optional<IncludeEntry> FindIncludeStartingTag(const string &line, const u64 startPosition);

    optional<IncludeEntry> FindIncludeClosingTag(const string &line, const u64 startPosition);

    IncludeEntry FindTag(const string &line, const string& tag, u64 startPosition,
        HeaderFileType headerType, IncludeTagType tagType);

    vector<string> ExpandHeaderIncludes(const string &sourceFile, vector<HeaderFile> headerFiles, const string &workingDirectory) {
        u64 lineOffset = 0;
        const vector<HeaderToken> headerTokens = GetTokensFromFile(sourceFile);
        if (headerTokens.size() == 0)
            return vector<string>();

        auto sourceFileContent = ReadFileByLines(sourceFile);
        const auto firstHeaderIncludeIndex = headerTokens[0].lineNumber -1;
        for (const auto &headerInclude : headerTokens) {
            const auto lineIndex = headerInclude.lineNumber - lineOffset -1;
            const auto linePosition = sourceFileContent.begin() + lineIndex;

            sourceFileContent.erase(linePosition);
            lineOffset += 1;
        }

        lineOffset = 0;
        for (auto &headerFile : headerFiles)
            ExpandHeaderInclude(sourceFileContent, headerFile, workingDirectory, firstHeaderIncludeIndex + lineOffset, lineOffset);

        return std::move(sourceFileContent);
    }

    void ExpandHeaderInclude(vector<string> &fileContent, HeaderFile &headerFile, const string &workingDirectory, u64 lineIndex, u64 &linesOffset)  {
        vector<string> headerContent = GetHeaderContent(headerFile, workingDirectory);
        const auto headerContentSize = headerContent.size();
        if (headerContentSize == 0)
            return;

        auto copiedLinesCount = 0;
        for (u64 i = 0; i < headerContentSize; i++) {
            auto nextLinePosition = fileContent.begin() + lineIndex + copiedLinesCount;
            const u64 nextLineIndex = distance(fileContent.begin(), nextLinePosition);
            if (nextLineIndex >= fileContent.size())
                nextLinePosition = fileContent.end();

            const auto currentLineNumber = i + 1;
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

    vector<HeaderToken> GetTokensFromFile(const string &filePath) {
        vector<HeaderToken> foundTokens;
        vector<string> fileContentByLines = ReadFileByLines(filePath);

        for (u64 i = 0; i < fileContentByLines.size(); i++) {
            auto &currentLine = fileContentByLines[i];
            
            HeaderToken foundHeaderToken;
            if (!TryGetHeaderToken(currentLine, i + 1, foundHeaderToken))
                continue;

            foundTokens.emplace_back(foundHeaderToken);
        }

        return std::move(foundTokens);
    }

    bool TryGetHeaderToken(string &line, const u64 lineNumber, HeaderToken &foundHeaderToken) {
        const u64 includePosition = FindIncludeMacro(line);
        if (includePosition == string::npos)
            return false;

        optional<IncludeEntry> startingTagResult = FindIncludeStartingTag(line, includePosition);
        if (!startingTagResult)
            return false;

        const auto startingTag = startingTagResult.value();
        optional<IncludeEntry> closingTagResult = FindIncludeClosingTag(line, startingTag.position + 1);
        if (!closingTagResult)
            return false;

        const auto closingTag = closingTagResult.value();
        if (startingTag.position >= closingTag.position || startingTag.headerType != closingTag.headerType)
            return false;

        const auto headerFileNameLength = (closingTag.position - 1) - startingTag.position;
        const auto headerFileName = line.substr(startingTag.position + 1, headerFileNameLength);

        foundHeaderToken = HeaderToken(headerFileName, closingTag.headerType, lineNumber);
        return true;
    }

    bool TryGetPrgramaDirective(std::string &line, const u64 lineNumber, std::string &foundDirective) {
        const string pragmaMacroStatement = "#pragma";
        const u64 pragmaMacroPosition = line.find(pragmaMacroStatement);

        if (pragmaMacroPosition == string::npos)
            return false;

        auto pragmaStatementSize = pragmaMacroStatement.size();
        if (line.size() == pragmaStatementSize)
            return false;

        u64 pragmaValueSize = line.size() - 1 - pragmaStatementSize;
        foundDirective = line.substr(pragmaStatementSize + 1, pragmaValueSize);
        return true;
    }

    vector<string> GetHeaderContent(const HeaderFile &headerFile, const string &workingDirectory) {
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

    u64 FindIncludeMacro(const string &line) {
        const string includeMacroStatement = "#include";
        const u64 includeMacroPosition = line.find(includeMacroStatement);
        return includeMacroPosition;
    }

    optional<IncludeEntry> FindIncludeStartingTag(const string &line, const u64 startPosition) {
        const string localIncludeStartTag = "\"";
        const string externalIncludeStartTag = "<";
        const IncludeEntry localStartingTag = FindTag(line, localIncludeStartTag, startPosition, HeaderFileType::Local, IncludeTagType::Start);
        const IncludeEntry externalStartingTag = FindTag(line, externalIncludeStartTag, startPosition, HeaderFileType::External, IncludeTagType::Start);

        if (localStartingTag.position != string::npos)
            return { localStartingTag };

        if (externalStartingTag.position != string::npos)
            return { externalStartingTag };

        return nullopt;
    }

    optional<IncludeEntry> FindIncludeClosingTag(const string &line, const u64 startPosition) {
        const string localIncludeClosingTag = "\"";
        const string externalIncludeClosingTag = ">";
        const IncludeEntry localClosingTag = FindTag(line, localIncludeClosingTag, startPosition, HeaderFileType::Local, IncludeTagType::End);
        const IncludeEntry externalClosingTag = FindTag(line, externalIncludeClosingTag, startPosition, HeaderFileType::External, IncludeTagType::End);

        if (localClosingTag.position != string::npos)
            return { localClosingTag };

        if (externalClosingTag.position != string::npos)
            return { externalClosingTag };

        return nullopt;
    }

    IncludeEntry FindTag(const string &line, const string& tag, const u64 startPosition, const HeaderFileType headerType, const IncludeTagType tagType) {
        const u64 tagPosition = line.find(tag, startPosition);
        return IncludeEntry {
            .position = tagPosition,
            .headerType = headerType,
            .tagType = tagType
        };
    } 
}