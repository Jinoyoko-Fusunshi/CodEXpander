#include <chrono>
#include "logging.h"
#include "color_builder.h"
#include "test_system.h"
#include "assertion_exception.h"

using std::string, std::vector, std::to_string, std::chrono::steady_clock, std::chrono::duration;
using namespace CodEXpander::Core;

namespace CodEXpander::Tests {
    template void TestSystem::AssertAreEqual(u64 expectedValue, u64 actualValue);
    template void TestSystem::AssertAreEqual(int expectedValue, int actualValue);
    template void TestSystem::AssertAreEqual(bool expectedValue, bool actualValue);

    string GetElapsedTimeInSeconds(const steady_clock::time_point &start, const steady_clock::time_point &end);

    void TestSystem::AddTests(const std::vector<TestMethod> &tests) {
        for (auto &test : tests)
            AddTest(test);
    }

    void TestSystem::AddTest(const TestMethod &test) {
        registeredTests.emplace_back(std::move(test));
    }

    void TestSystem::RunTests() {
        vector<TestMethod> failedTests;
        vector<TestMethod> passedTests;

        Logger logger;
        logger.PrintMessage("Running tests: ", Color().Green());
        logger.PrintLineInfoMessage(to_string(registeredTests.size()));
        logger.PrintLineMessage("========================================================", Color().White());

        const auto testsStartTime = steady_clock::now();
        for (const auto& test : registeredTests) {
            logger.PrintMessage(string(">> "), Color().White());
            logger.PrintMessage(test.testName, Color().Cyan());
            logger.PrintLineMessage(string(":"), Color().White());

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

            logger.PrintMessage(resultMessage, color);
            logger.PrintMessage(": \n\t\t" + elapsedSecondsMessage + "\n\n", Color().White());
        }
        const auto testsEndTime = steady_clock::now();
        const string elapsedSecondsMessage = GetElapsedTimeInSeconds(testsStartTime, testsEndTime);

        logger.PrintLineInfoMessage("");
        logger.PrintMessage("Finished running tests: ", Color().Green());
        logger.PrintMessage(elapsedSecondsMessage, Color().Cyan());
        logger.PrintMessage("\n========================================================\n", Color().White());
        logger.PrintMessage("Passed Tests: ", Color().Green());
        logger.PrintInfoMessage(to_string(passedTests.size()));
        logger.PrintMessage(" of ", Color().White());
        logger.PrintInfoMessage(to_string(registeredTests.size()));

        logger.PrintMessage("\n\nFailed Tests: ", Color().Red());
        logger.PrintInfoMessage(to_string(failedTests.size()));
        logger.PrintMessage(" of ", Color().White());
        logger.PrintInfoMessage(to_string(registeredTests.size()));
        logger.PrintLineMessage("", Color().White());
    }

    void TestSystem::AssertStringsAreEqual(const std::string &expectedValue, const std::string &actualValue) {
        if (expectedValue != actualValue) {
            std::string message = std::string("Assertion failed:") + std::string("\n\t\t\texpected value: ")
                + expectedValue + std::string("\n\t\t\tactual value: \t") + actualValue;

            throw AssertionException(message);
        }
    }
    
    TestMethod TestSystem::CreateTestMethod(const std::string name, void (*callback)()) {
        return TestMethod {
            .testName = std::move(name),
            .callback = callback
        };       
    }

    template<typename T> void TestSystem::AssertAreEqual(T expectedValue, T actualValue) {
        auto valueMatches = expectedValue == actualValue;
        if (!valueMatches) {
            std::string message = std::string("Assertion failed:") + std::string("\n\t\t\texpected value: ")
                + std::to_string(expectedValue) + std::string("\n\t\t\tactual value: \t") + std::to_string(actualValue);

            throw AssertionException(message);
        }
    }

    string GetElapsedTimeInSeconds(const steady_clock::time_point &start, const steady_clock::time_point &end) {
        const auto elapsedSeconds = duration<double>(end - start);
        const auto elapsedSecondsMessage = to_string(elapsedSeconds.count()) + "s";
        return std::move(elapsedSecondsMessage);
    }
}