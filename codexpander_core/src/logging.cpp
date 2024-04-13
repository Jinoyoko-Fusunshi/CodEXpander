#include <iostream>
#include <string>
#include "logging.h"
#include "color_builder.h"

using std::vector, std::string, std::cout;

namespace CodEXpander::Core {
    Color infoColor = Color().Cyan();
    Color errorColor = Color().Red();
    Color warningColor = Color().Yellow();

    void PrintLineInfoMessage(vector<string> &messageTraceLogs, const string message) {
        PrintLineMessage(messageTraceLogs, message, infoColor);
    }

    void PrintInfoMessage(vector<string> &messageTraceLogs,  const string message) {
        PrintMessage(messageTraceLogs, message, infoColor);
    }

    void PrintLineErrorMessage(vector<string> &messageTraceLogs, const string message) {
        PrintLineMessage(messageTraceLogs, message, errorColor);
    }

    void PrintErrorMessage(vector<string> &messageTraceLogs, const string message) {
        PrintMessage(messageTraceLogs, message, errorColor);
    }

    void PrintLineWarningMessage(vector<string> &messageTraceLogs, const string message) {
        PrintLineMessage(messageTraceLogs, message, warningColor);
    }

    void PrintWarningMessage(vector<string> &messageTraceLogs, const string message) {
        PrintMessage(messageTraceLogs, message, warningColor);
    }

    void PrintLineMessage(vector<string> &messageTraceLogs, const string message, const Color color) {
        string newLineMessage = message + "\n";
        PrintMessage(messageTraceLogs, newLineMessage, color);
    }

    void PrintMessage(vector<string> &messageTraceLogs, const string message, const Color color) {
        messageTraceLogs.emplace_back(message);
        cout << color.colorEscapeCharacter << message;
    }
}