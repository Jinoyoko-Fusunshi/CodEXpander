#include <fstream>
#include <iostream>
#include <optional>
#include "source_file_reader.h"

using std::optional, std::string, std::nullopt, std::vector, std::ifstream;

enum class IncludeTagType {
    None = 0,
    Start,
    End
};

struct IncludeEntry {
    size_t position;
    HeaderFileType headerType;
    IncludeTagType tagType;
};

size_t FindIncludeMacro(const string &line);

optional<IncludeEntry> FindIncludeStartingTag(const string &line, size_t startPosition);

optional<IncludeEntry> FindIncludeClosingTag(const string &line, size_t startPosition);

IncludeEntry FindTag(const string &line, const string& tag, size_t startPosition,
    HeaderFileType headerType, IncludeTagType tagType);

vector<string> ReadFileByLines(const string& filePath) {
    vector<string> fileLines;
    ifstream fileStream(filePath);
    if (!fileStream.is_open())
        return std::move(fileLines);

    unsigned int lineCount = 0;
    string currentLine;
    while (getline(fileStream, currentLine)) {
        lineCount++;
        fileLines.emplace_back(currentLine);
    }

    fileStream.close();

    return std::move(fileLines);
}

vector<HeaderToken> GetTokensFromFile(const string& filePath) {
    vector<HeaderToken> foundTokens;
    const vector<string> fileContentByLines = ReadFileByLines(filePath);

    for (size_t i = 0; i < fileContentByLines.size(); i++) {
        const string &currentLine = fileContentByLines[i];
        const size_t includePosition = FindIncludeMacro(currentLine);
        if (includePosition == string::npos)
            continue;

        optional<IncludeEntry> startingTagResult = FindIncludeStartingTag(currentLine, includePosition);
        if (!startingTagResult)
            continue;

        const auto startingTag = startingTagResult.value();
        optional<IncludeEntry> closingTagResult = FindIncludeClosingTag(currentLine, startingTag.position + 1);
        if (!closingTagResult)
            continue;

        const auto closingTag = closingTagResult.value();
        if (startingTag.position >= closingTag.position || startingTag.headerType != closingTag.headerType)
            continue;

        const auto headerFileNameLength = (closingTag.position - 1) - startingTag.position;
        const auto headerFileName = currentLine.substr(startingTag.position + 1, headerFileNameLength);

        HeaderToken token = {
            .fileName = headerFileName,
            .lineNumber = static_cast<unsigned int>(i) + 1,
            .headerType = closingTag.headerType
        };
        foundTokens.emplace_back(token);
    }

    return foundTokens;
}

size_t FindIncludeMacro(const string &line) {
    const string includeMacroStatement = "#include";
    const size_t includeMacroPosition = line.find(includeMacroStatement);

    return includeMacroPosition;
}

optional<IncludeEntry> FindIncludeStartingTag(const string &line, const size_t startPosition) {
    const string localIncludeStartTag = "\"";
    const string externalIncludeStartTag = "<";
    IncludeEntry localStartingTag = FindTag(line, localIncludeStartTag, startPosition, HeaderFileType::Local, IncludeTagType::Start);
    IncludeEntry externalStartingTag = FindTag(line, externalIncludeStartTag, startPosition, HeaderFileType::External, IncludeTagType::Start);

    if (localStartingTag.position != string::npos)
        return { localStartingTag };

    if (externalStartingTag.position != string::npos)
        return { externalStartingTag };

    return nullopt;
}

optional<IncludeEntry> FindIncludeClosingTag(const string &line, const size_t startPosition) {
    const string localIncludeClosingTag = "\"";
    const string externalIncludeClosingTag = ">";
    IncludeEntry localClosingTag = FindTag(line, localIncludeClosingTag, startPosition, HeaderFileType::Local, IncludeTagType::End);
    IncludeEntry externalClosingTag = FindTag(line, externalIncludeClosingTag, startPosition, HeaderFileType::External, IncludeTagType::End);

    if (localClosingTag.position != string::npos)
        return { localClosingTag };

    if (externalClosingTag.position != string::npos)
        return { externalClosingTag };

    return nullopt;
}

IncludeEntry FindTag(const string &line, const string& tag, const size_t startPosition,
    const HeaderFileType headerType, const IncludeTagType tagType)
{
    const size_t tagPosition = line.find(tag, startPosition);
    return IncludeEntry {
        .position = tagPosition,
        .headerType = headerType,
        .tagType = tagType
    };
}