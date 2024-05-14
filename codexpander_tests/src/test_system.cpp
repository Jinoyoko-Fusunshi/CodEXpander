#include <chrono>
#include "logging.h"
#include "color_builder.h"
#include "test_system.h"
#include "assertion_exception.h"
#include "command.h"

using std::string, std::vector, std::to_string, std::chrono::steady_clock, std::chrono::duration;
using namespace CodEXpander::Core;

namespace CodEXpander::Tests {
    template void TestSystem::AssertValues(u64 expectedValue, u64 actualValue);
    template void TestSystem::AssertValues(int expectedValue, int actualValue);
    template void TestSystem::AssertValues(bool expectedValue, bool actualValue);

    string GetElapsedTimeInSeconds(const steady_clock::time_point &start, const steady_clock::time_point &end);

    void TestSystem::AddTests(const vector<TestMethod> &tests) {
        for (auto &test : tests)
            AddTest(test);
    }

    void TestSystem::AddTest(const TestMethod &test) {
        registeredTests.emplace_back(std::move(test));
    }

    int TestSystem::RunTests() {
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
                resultMessage = string("\tFAILED -> ") + ex.GetMessage();
                color = Color().Red();
                failedTests.emplace_back(std::move(test));
            }
            logger.PrintMessage(resultMessage, color);

            const auto testEndTime = steady_clock::now();
            const string elapsedSecondsMessage = GetElapsedTimeInSeconds(testStartTime, testEndTime);
            auto runtimeMessage = string("\n\t") +  "Runtime: " + elapsedSecondsMessage + "\n\n";
            logger.PrintMessage(runtimeMessage, Color::White());
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

        return failedTests.size() > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    void TestSystem::AssertStrings(const string &expectedValue, const string &actualValue) {
        if (expectedValue != actualValue) {
            string message = string("Assertion failed:") + string("\n\t\t\texpected value: ")
                + expectedValue + string("\n\t\t\tactual value: \t") + actualValue;

            throw AssertionException(message);
        }
    }
    
    TestMethod TestSystem::CreateTestMethod(const string name, void (*callback)()) {
        return TestMethod {
            .testName = std::move(name),
            .callback = callback
        };       
    }

    void TestSystem::AssertObjects(Stringable* expectedValue, Stringable* actualValue) {
        if (expectedValue == actualValue)
            return;

        auto valueOrDefault = [](Stringable* stringable) {
            return !stringable ? "NULL" : stringable->ToString();
        };

        string message = string("Assertion failed:") + string("\n\t\texpected value: \t") + valueOrDefault(expectedValue) 
            + string("\n\t\tactual value value: \t") + valueOrDefault(actualValue);

        throw AssertionException(message);
    }

    template<typename T> void TestSystem::AssertValues(T expectedValue, T actualValue) {
        if (expectedValue == actualValue)
            return;
        
        string message = string("Assertion failed:") + string("\n\t\t\texpected value: ")
            + to_string(expectedValue) + string("\n\t\t\tactual value: \t") + to_string(actualValue);

        throw AssertionException(message);
    }

    string GetElapsedTimeInSeconds(const steady_clock::time_point &start, const steady_clock::time_point &end) {
        const auto elapsedSeconds = duration<double>(end - start);
        const auto elapsedSecondsMessage = to_string(elapsedSeconds.count()) + "s";
        return std::move(elapsedSecondsMessage);
    }
}