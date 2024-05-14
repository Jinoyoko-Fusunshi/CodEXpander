#pragma once

#include <string>
#include <vector>
#include "declarations.h"
#include "assertion_exception.h"
#include "stringable.h"

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
        int RunTests();

        static TestMethod CreateTestMethod(const std::string name, void (*callback)()); 
        static void AssertStrings(const std::string &expectedValue, const std::string &actualValue);

        static void AssertObjects(CodEXpander::Core::Stringable *expectedValue, CodEXpander::Core::Stringable *actualValue);
        template<typename T> static void AssertValues(T expectedValue, T actualValue);
    };
}