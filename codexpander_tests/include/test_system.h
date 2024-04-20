#pragma once

#include <string>
#include <vector>
#include "declarations.h"
#include "assertion_exception.h"

namespace CodEXpander::Tests {
    struct TestMethod {
        std::string testName;
        void (*callback)();
    };

    class TestSystem final {
    private:
        std::vector<TestMethod> registeredTests;
        std::vector<std::string> outputLogs;

    public:
        TestSystem() = default;
        ~TestSystem() = default;

        void AddTests(const std::vector<TestMethod> &tests);
        void AddTest(const TestMethod &test);
        void RunTests();

        static TestMethod CreateTestMethod(const std::string name, void (*callback)()); 
        static void AssertStringsAreEqual(const std::string &expectedValue, const std::string &actualValue);

        template<typename T> static void AssertAreEqual(T expectedValue, T actualValue);
    };
}