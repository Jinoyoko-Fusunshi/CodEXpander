#include "command_parser.h"
#include "test_system.hpp"
#include "test_system.h"
#include "declarations.h"

using namespace CodEXpander::Core;
using std::string, std::vector;

namespace CodEXpander::Tests {
    void TestCommandParser_ParseArguments_StringIsEmpty_NoArguments() {
        const u64 expectedArgumentCount = 0;   
        string command[] = {""};
        
        auto arguments = ParseArguments(0, command);
        u64 argumentCount = arguments.size();

        AssertAreEqual(expectedArgumentCount, argumentCount);
    }

    void TestCommandParser_ParseArguments_ArgumentWithOnePrexifSymbol_ReturnsNoArguments() {
        const u64 expectedArgumentCount = 0;     
        string command[] = {"command", "-test_argument=test"};

        auto arguments = ParseArguments(2, command);
        u64 argumentCount = arguments.size();

        AssertAreEqual(expectedArgumentCount, argumentCount);
    }

    void TestCommandParser_ParseArguments_ArgumentWithBothPrefixSymbol_ReturnsOneArgument() {
        const u64 expectedArgumentCount = 1;
        string command[] = {"command", "--test_argument=test"};

        auto arguments = ParseArguments(2, command);
        u64 argumentCount = arguments.size();

        auto argument = arguments[0];
        AssertAreEqual(expectedArgumentCount, argumentCount);
        AssertStringsAreEqual("test_argument", argument.name);
        AssertStringsAreEqual("test", argument.value);
    }

    void TestCommandParser_ParseArguments_TwoArgumentsPresent_ReturnsTwoArguments() {
        const u64 expectedArgumentCount = 2;
        string command[] = {"command", "--first_argument=first", "--second_argument=second"};

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
}