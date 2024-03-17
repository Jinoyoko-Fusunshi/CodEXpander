#include <iostream>
#include "test_system.h"
#include "assertion_exception.h"

using std::string, std::vector, std::cout, std::to_string;

namespace CodEXpander::Tests {
    TestMethod CreateTestMethod(const string name, void (*callback)()) {
        TestMethod testmethod = {
            .testName = std::move(name),
            .callback = callback
        };

        return testmethod;
    }

    void RunTests(vector<TestMethod> tests) {
        vector<TestMethod> failedTests;
        vector<TestMethod> passedTests; 
        vector<string> outputLogs;

        PrintMessage(outputLogs, "Running tests: ", "\033[1;37m");
        PrintLineInfoMessage(outputLogs, to_string(tests.size()));
        PrintLineMessage(outputLogs, "========================================================", "\033[1;37m");

        for (const auto& test : tests) {
            PrintMessage(outputLogs, string(">> "), "\033[1;37m");
            PrintMessage(outputLogs, test.testName, "\033[0;36m");
            PrintLineMessage(outputLogs, string(":"), "\033[1;37m");

            string resultMessage;
            string colorCode;
            try {
                test.callback();
                resultMessage = "\tPASSED";
                colorCode = "\033[0;32m";
                passedTests.emplace_back(std::move(test));
            } catch (AssertionException ex) {
                resultMessage = string("\tFAILED:") + string("\n\t\t") + ex.GetMessage();
                colorCode = "\033[0;31m";
                failedTests.emplace_back(std::move(test));
            }

            PrintLineMessage(outputLogs, resultMessage, colorCode);
            PrintLineInfoMessage(outputLogs, " ");
        }

        PrintLineInfoMessage(outputLogs, "");
        PrintMessage(outputLogs, "Finished running tests:\n", "\033[0;32m");
        PrintMessage(outputLogs, "========================================================\n", "\033[1;37m");
        PrintMessage(outputLogs, "Passed Tests: ", "\033[0;32m");
        PrintInfoMessage(outputLogs, to_string(passedTests.size()));
        PrintMessage(outputLogs, " of ", "\033[1;37m");
        PrintInfoMessage(outputLogs, to_string(tests.size()));

        PrintMessage(outputLogs, "\n\nFailed Tests: ", "\033[0;31m");
        PrintInfoMessage(outputLogs, to_string(failedTests.size()));
        PrintMessage(outputLogs, " of ", "\033[1;37m");
        PrintInfoMessage(outputLogs, to_string(tests.size()));
        PrintLineMessage(outputLogs, "", "\033[0m");
    }

    void AssertStringsAreEqual(const std::string &expectedValue, const std::string &actualValue) {
        auto valueMatches = expectedValue == actualValue;
        if (!valueMatches) {
            std::string message = std::string("Assertion failed:") + std::string("\n\t\t\texpected value: ")
                + expectedValue + std::string("\n\t\t\tactual value: \t") + actualValue;

            throw AssertionException(message);
        }
    }

    void PrintLineInfoMessage(vector<string> messageTraceLogs, string message) {
        PrintLineMessage(messageTraceLogs, message, "\033[0;36m");
    }

    void PrintInfoMessage(vector<string> messageTraceLogs, string message) {
        PrintMessage(messageTraceLogs, message, "\033[0;36m");
    }

    void PrintLineErrorMessage(vector<string> messageTraceLogs, string message) {
        PrintLineMessage(messageTraceLogs, message, "\033[0;31m");
    }

    void PrintErrorMessage(vector<string> messageTraceLogs, string message) {
        PrintMessage(messageTraceLogs, message, "\033[0;31m");
    }

    void PrintLineWarningMessage(vector<string> messageTraceLogs, string message) {
        PrintLineMessage(messageTraceLogs, message, "\033[1;33m");
    }

    void PrintWarningMessage(vector<string> messageTraceLogs, string message) {
        PrintMessage(messageTraceLogs, message, "\033[1;33m");
    }

    void PrintLineMessage(vector<string> messageTraceLogs, string message, string colorEscapeCode) {
        string newLineMessage = message + "\n";
        PrintMessage(messageTraceLogs, newLineMessage, colorEscapeCode);
    }

    void PrintMessage(vector<string> messageTraceLogs, string message, string colorEscapeCode) {
        messageTraceLogs.emplace_back(message);
        cout << colorEscapeCode << message;
    }
}