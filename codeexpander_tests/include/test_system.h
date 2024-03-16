#pragma once

#include <string>
#include <vector>
#include "assertion_exception.h"

namespace CodEXpander::Tests {
    struct TestMethod {
        std::string testName;
        void (*callback)();
    };

    TestMethod CreateTestMethod(std::string name, void (*callback)());

    void RunTests(std::vector<TestMethod> tests);

    void PrintLineInfoMessage(std::vector<std::string> messageTraceLogs, std::string message);

    void PrintInfoMessage(std::vector<std::string> messageTraceLogs, std::string message);

    void PrintLineErrorMessage(std::vector<std::string> messageTraceLogs, std::string message);

    void PrintErrorMessage(std::vector<std::string> messageTraceLogs, std::string message);

    void PrintLineWarningMessage(std::vector<std::string> messageTraceLogs, std::string message);

    void PrintLineWarningMessage(std::vector<std::string> messageTraceLogs, std::string message);

    void PrintWarningMessage(std::vector<std::string> messageTraceLogs, std::string message);

    void PrintLineMessage(std::vector<std::string> messageTraceLogs, std::string message, std::string colorEscapeCode);

    void PrintMessage(std::vector<std::string> messageTraceLogs, std::string message, std::string colorEscapeCode);
}