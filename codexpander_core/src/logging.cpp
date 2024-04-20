#include <iostream>
#include <string>
#include "logging.h"
#include "color_builder.h"

using std::vector, std::string, std::cout;

namespace CodEXpander::Core {
    auto infoColor = Color().Cyan();
    auto errorColor = Color().Red();
    auto warningColor = Color().Yellow();

    void Logger::PrintLineInfoMessage(const string message) {
        PrintLineMessage(message, infoColor);
    }

    void Logger::PrintInfoMessage(const string message) {
        PrintMessage(message, infoColor);
    }

    void Logger::PrintLineErrorMessage(const string message) {
        PrintLineMessage(message, errorColor);
    }

    void Logger::PrintErrorMessage(const string message) {
        PrintMessage(message, errorColor);
    }

    void Logger::PrintLineWarningMessage(const string message) {
        PrintLineMessage(message, warningColor);
    }

    void Logger::PrintWarningMessage(const string message) {
        PrintMessage(message, warningColor);
    }

    void Logger::PrintLineMessage(const string message, const Color color) {
        string newLineMessage = message + "\n";
        PrintMessage(newLineMessage, color);
    }

    void Logger::PrintMessage(const string message, const Color color) {
        outputLogs.emplace_back(message);
        cout << color.colorEscapeCharacter << message;
    }
}