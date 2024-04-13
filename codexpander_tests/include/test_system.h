#pragma once

#include <string>
#include <vector>

namespace CodEXpander::Tests {
    struct TestMethod {
        std::string testName;
        void (*callback)();
    };

    TestMethod CreateTestMethod(const std::string name, void (*callback)());

    void RunTests(const std::vector<TestMethod> &tests);

    void AssertStringsAreEqual(const std::string &expectedValue, const std::string &actualValue);
}