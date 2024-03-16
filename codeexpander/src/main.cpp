#include "source_file_reader.h"

int main() {
    const auto filePath = std::string("./res/test_file.cpp");
    unsigned int linesCount = GetFileLinesCount(filePath);

    return 0;
}