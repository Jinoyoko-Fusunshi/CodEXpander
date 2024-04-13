#include <chrono>
#include "logging.h"
#include "color_builder.h"
#include "test_system.h"
#include "assertion_exception.h"

using std::string, std::vector, std::to_string, std::chrono::steady_clock, std::chrono::duration;
using namespace CodEXpander::Core;

namespace CodEXpander::Tests {
    string GetElapsedTimeInSeconds(const steady_clock::time_point &start, const steady_clock::time_point &end);

    TestMethod CreateTestMethod(const string name, void (*callback)()) {
        TestMethod testmethod = {
            .testName = std::move(name),
            .callback = callback
        };

        return testmethod;
    }

    void RunTests(const vector<TestMethod> &tests) {
        vector<TestMethod> failedTests;
        vector<TestMethod> passedTests; 
        vector<string> outputLogs;

        PrintMessage(outputLogs, "Running tests: ", Color().Green());
        PrintLineInfoMessage(outputLogs, to_string(tests.size()));
        PrintLineMessage(outputLogs, "========================================================", Color().White());

        const auto testsStartTime = steady_clock::now();
        for (const auto& test : tests) {
            PrintMessage(outputLogs, string(">> "), Color().White());
            PrintMessage(outputLogs, test.testName, Color().Cyan());
            PrintLineMessage(outputLogs, string(":"), Color().White());

            string resultMessage;
            Color color;
            const auto testStartTime = steady_clock::now();
            try {
                test.callback();
                resultMessage = "\tPASSED";
                color = Color().Green();
                passedTests.emplace_back(std::move(test));
            } catch (AssertionException ex) {
                resultMessage = string("\tFAILED:") + string("\n\t\t") + ex.GetMessage();
                color = Color().Red();
                failedTests.emplace_back(std::move(test));
            }
            const auto testEndTime = steady_clock::now();
            const string elapsedSecondsMessage = GetElapsedTimeInSeconds(testStartTime, testEndTime);

            PrintMessage(outputLogs, resultMessage, color);
            PrintMessage(outputLogs, ": \n\t\t" + elapsedSecondsMessage + "\n\n", Color().White());
        }
        const auto testsEndTime = steady_clock::now();
        const string elapsedSecondsMessage = GetElapsedTimeInSeconds(testsStartTime, testsEndTime);

        PrintLineInfoMessage(outputLogs, "");
        PrintMessage(outputLogs, "Finished running tests: ", Color().Green());
        PrintMessage(outputLogs, elapsedSecondsMessage, Color().Cyan());
        PrintMessage(outputLogs, "\n========================================================\n", Color().White());
        PrintMessage(outputLogs, "Passed Tests: ", Color().Green());
        PrintInfoMessage(outputLogs, to_string(passedTests.size()));
        PrintMessage(outputLogs, " of ", Color().White());
        PrintInfoMessage(outputLogs, to_string(tests.size()));

        PrintMessage(outputLogs, "\n\nFailed Tests: ", Color().Red());
        PrintInfoMessage(outputLogs, to_string(failedTests.size()));
        PrintMessage(outputLogs, " of ", Color().White());
        PrintInfoMessage(outputLogs, to_string(tests.size()));
        PrintLineMessage(outputLogs, "", Color().White());
    }

    void AssertStringsAreEqual(const std::string &expectedValue, const std::string &actualValue) {
        if (expectedValue != actualValue) {
            std::string message = std::string("Assertion failed:") + std::string("\n\t\t\texpected value: ")
                + expectedValue + std::string("\n\t\t\tactual value: \t") + actualValue;

            throw AssertionException(message);
        }
    }

    string GetElapsedTimeInSeconds(const steady_clock::time_point &start, const steady_clock::time_point &end) {
        const auto elapsedSeconds = duration<double>(end - start);
        const auto elapsedSecondsMessage = to_string(elapsedSeconds.count()) + "s";
        return std::move(elapsedSecondsMessage);
    }
}