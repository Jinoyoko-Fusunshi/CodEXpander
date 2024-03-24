#include <fstream>
#include <iostream>
#include <filesystem>
#include <optional>
#include "source_file_reader.h"
#include "declarations.h"

using std::optional, std::string, std::nullopt, std::vector, std::ifstream, std::filesystem::path, std::filesystem::exists;

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

        for (u64 i = 0; i < fileContentByLines.size(); i++) {
            const string &currentLine = fileContentByLines[i];
            const u64 includePosition = FindIncludeMacro(currentLine);
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

    vector<string> GetHeaderContent(const HeaderToken headerToken, const string workingDirectory) {
        vector<string> headerContent; 
        if (headerToken.headerType == HeaderFileType::System)
            return std::move(headerContent);

        string includeDirectory = workingDirectory + string("/include");
        path includePath(includeDirectory);
        if (!exists(includePath))
            return std::move(headerContent);
        
        string headerFileName = includeDirectory + "/" + headerToken.fileName;
        path headerFilePath(headerFileName);
        if (!exists(headerFilePath))
            return std::move(headerContent);
        
        vector<string> fileContent = ReadFileByLines(headerFileName);
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
        IncludeEntry localStartingTag = FindTag(line, localIncludeStartTag, startPosition, HeaderFileType::Local, IncludeTagType::Start);
        IncludeEntry externalStartingTag = FindTag(line, externalIncludeStartTag, startPosition, HeaderFileType::External, IncludeTagType::Start);

        if (localStartingTag.position != string::npos)
            return { localStartingTag };

        if (externalStartingTag.position != string::npos)
            return { externalStartingTag };

        return nullopt;
    }

    optional<IncludeEntry> FindIncludeClosingTag(const string &line, const u64 startPosition) {
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

    IncludeEntry FindTag(const string &line, const string& tag, const u64 startPosition,
        const HeaderFileType headerType, const IncludeTagType tagType)
    {
        const u64 tagPosition = line.find(tag, startPosition);
        return IncludeEntry {
            .position = tagPosition,
            .headerType = headerType,
            .tagType = tagType
        };
    }
}