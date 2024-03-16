#include "source_file_reader.h"

using std::string;

int main() {
    const auto filePath = string("./res/test_file.cpp");
    unsigned int linesCount = GetFileLinesCount(filePath);

    return 0;
}