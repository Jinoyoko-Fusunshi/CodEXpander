#pragma once

#include <string>
#include <vector>
#include "color.h"

namespace CodEXpander::Core {
    void PrintLineInfoMessage(std::vector<std::string> &messageTraceLogs, const std::string message);

    void PrintInfoMessage(std::vector<std::string> &messageTraceLogs, const std::string message);

    void PrintLineErrorMessage(std::vector<std::string> &messageTraceLogs, const std::string message);

    void PrintErrorMessage(std::vector<std::string> &messageTraceLogs, const std::string message);

    void PrintLineWarningMessage(std::vector<std::string> &messageTraceLogs, const std::string message);

    void PrintLineWarningMessage(std::vector<std::string> &messageTraceLogs, const std::string message);

    void PrintWarningMessage(std::vector<std::string> &messageTraceLogs, const std::string message);

    void PrintLineMessage(std::vector<std::string> &messageTraceLogs, const std::string message, const Color color);

    void PrintMessage(std::vector<std::string> &messageTraceLogs, const std::string message, const Color color);
}