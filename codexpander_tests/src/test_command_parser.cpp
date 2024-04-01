#include "test_command_parser.h"
#include "command_parser.h"
#include "declarations.h"
#include "test_system.hpp"
#include "test_system.h"

using namespace CodEXpander::Core;
using std::string, std::vector;

namespace CodEXpander::Tests {
    void TestCommandParser_ParseArguments_StringIsEmpty_NoArguments() {
        const u64 expectedArgumentCount = 0;   
        vector<string> command = {""};
        
        auto arguments = ParseArguments(0, command);
        u64 argumentCount = arguments.size();

        AssertAreEqual(expectedArgumentCount, argumentCount);
    }

    void TestCommandParser_ParseArguments_ArgumentWithOnePrexifSymbol_ReturnsNoArguments() {
        const u64 expectedArgumentCount = 0;     
        vector<string> command = {"command", "-test_argument=test"};

        auto arguments = ParseArguments(2, command);
        u64 argumentCount = arguments.size();

        AssertAreEqual(expectedArgumentCount, argumentCount);
    }

    void TestCommandParser_ParseArguments_ArgumentWithBothPrefixSymbol_ReturnsOneArgument() {
        const u64 expectedArgumentCount = 1;
        vector<string> command = {"command", "--test_argument=test"};

        auto arguments = ParseArguments(2, command);
        u64 argumentCount = arguments.size();

        auto argument = arguments[0];
        AssertAreEqual(expectedArgumentCount, argumentCount);
        AssertStringsAreEqual("test_argument", argument.name);
        AssertStringsAreEqual("test", argument.value);
    }

    void TestCommandParser_ParseArguments_TwoArgumentsPresent_ReturnsTwoArguments() {
        const u64 expectedArgumentCount = 2;
        vector<string> command = {"command", "--first_argument=first", "--second_argument=second"};

        auto arguments = ParseArguments(3, command);
        u64 argumentCount = arguments.size();

        auto first_argument = arguments[0];
        auto second_argument = arguments[1];
        AssertAreEqual(expectedArgumentCount, argumentCount);
        AssertStringsAreEqual("first_argument", first_argument.name);
        AssertStringsAreEqual("first", first_argument.value);
        AssertStringsAreEqual("second_argument", second_argument.name);
        AssertStringsAreEqual("second", second_argument.value);
    }

    void TestCommandParser_TryGetExistingArgument_NameIsEmpty_ReturnsFalse() {
        const bool expectedResult = false;
        vector<Argument> existingArguments = {
            { .name="first_argument", .value="first" }
        };

        Argument foundArgument;
        auto result = TryGetExistingArgument(existingArguments, "", foundArgument);

        AssertAreEqual<bool>(expectedResult, result);
    }

    void TestCommandParser_TryGetExistingArgument_NameIsValid_ArgumentDoesNotExist_ReturnsFalse() {
        const bool expectedResult = false;
        vector<Argument> existingArguments = {
            { .name="first_argument", .value="first" }
        };

        Argument foundArgument;
        auto result = TryGetExistingArgument(existingArguments, "test_argument", foundArgument);

        AssertAreEqual<bool>(expectedResult, result);
    }

    void TestCommandParser_TryGetExistingArgument_NameIsValid_ArgumentDoesExist_ReturnsArgument() {
        const bool expectedResult = true;
        const string expectedName = "first_argument";
        const string expectedValue = "first";
        vector<Argument> existingArguments = {
            { .name="first_argument", .value="first" }
        };

        Argument foundArgument;
        auto result = TryGetExistingArgument(existingArguments, "first_argument", foundArgument);

        AssertAreEqual<bool>(expectedResult, result);
        AssertStringsAreEqual(expectedName, foundArgument.name);
        AssertStringsAreEqual(expectedValue, foundArgument.value);
    }

    void TestCommandParser_TryGetExistingArgument_ArgumentDoesExist_ValueIsEmpty_ReturnsFalse() {
        const bool expectedResult = false;
        const string expectedName = "first_argument";
        const string expectedValue = "first";
        vector<Argument> existingArguments = {
            { .name="first_argument", .value="" }
        };

        Argument foundArgument;
        auto result = TryGetExistingArgument(existingArguments, "first_argument", foundArgument);

        AssertAreEqual<bool>(expectedResult, result);
    }
}