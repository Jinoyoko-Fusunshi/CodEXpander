#include <fstream>
#include <iostream>
#include <filesystem>
#include <optional>
#include "file_manager.h"
#include "declarations.h"

using std::string, std::vector, std::ifstream, std::ofstream, std::endl;

namespace CodEXpander::Core {
    vector<string> ReadFileByLines(const string &filePath) {
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

     bool TryWriteToFile(string filePath, vector<string> &expandedFileContent) {
        if (expandedFileContent.size() == 0)
            return false;
        
        ofstream fileStream(filePath);
        if (!fileStream.is_open())
            return false;

        for (auto currentLine : expandedFileContent)
            fileStream << currentLine << endl;

        fileStream.close();
        return true;
    }
}