#pragma once

#include <string>
#include <vector>
#include "color.h"

namespace CodEXpander::Core {
    class Logger final {
    private:
        std::vector<std::string> outputLogs;

    public:
        Logger() = default;
        ~Logger() = default;

        void PrintLineInfoMessage(const std::string message);
        void PrintInfoMessage(const std::string message);
        void PrintLineErrorMessage(const std::string message);
        void PrintErrorMessage(const std::string message);
        void PrintLineWarningMessage(const std::string message);
        void PrintWarningMessage(const std::string message);
        void PrintLineMessage(const std::string message, const Color color);
        void PrintMessage(const std::string message, const Color color);
    };
}