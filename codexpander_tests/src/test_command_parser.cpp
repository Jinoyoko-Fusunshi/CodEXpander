#include "test_command_parser.h"
#include "command_parser.h"
#include "declarations.h"
#include "test_system.h"

using namespace CodEXpander::Core;
using std::string, std::vector;

namespace CodEXpander::Tests {
    void TestCommandParser_ParseArguments_StringIsEmpty_NoArguments() {
        const u64 expectedArgumentCount = 0;   
        vector<string> commands = {""};
        
        CommandParser commandParser(commands);
        u64 argumentCount = commandParser.GetArgumentCount();

        TestSystem::AssertAreEqual<u64>(expectedArgumentCount, argumentCount);
    }

    void TestCommandParser_ParseArguments_ArgumentWithOnePrexifSymbol_ReturnsNoArguments() {
        const u64 expectedArgumentCount = 0;     
        vector<string> commands = {"command", "-test_argument=test"};

        CommandParser commandParser(commands);
        u64 argumentCount = commandParser.GetArgumentCount();

        TestSystem::AssertAreEqual(expectedArgumentCount, argumentCount);
    }

    void TestCommandParser_TryGetArgument_NameIsEmpty_ReturnsFalse() {
        const bool expectedResult = false;
        vector<string> commands = {"--first_argument=first"};

        CommandParser commandParser(commands);
        Argument foundArgument;
        auto result = commandParser.TryGetArgument("", foundArgument);

        TestSystem::AssertAreEqual<bool>(expectedResult, result);
    }

    void TestCommandParser_TryGetArgument_NameIsValid_ArgumentDoesNotExist_ReturnsFalse() {
        const bool expectedResult = false;
        vector<string> commands = {"--first_argument=first"};

        CommandParser commandParser(commands);
        Argument foundArgument;
        auto result = commandParser.TryGetArgument("test_argument", foundArgument);

        TestSystem::AssertAreEqual<bool>(expectedResult, result);
    }

    void TestCommandParser_TryGetArgumentWithValue_ArgumentWithBothPrefixSymbol_ReturnsOneArgument() {
        const u64 expectedArgumentCount = 1;
        const bool expectedArgumentResult = true;
        vector<string> commands = {"command", "--test_argument=test"};

        CommandParser commandParser(commands);
        Argument argument; 
        auto foundArgument = commandParser.TryGetArgumentWithValue("test_argument", argument);

        TestSystem::AssertAreEqual(expectedArgumentResult, true);
        TestSystem::AssertStringsAreEqual("test_argument", argument.GetName());
        TestSystem::AssertStringsAreEqual("test", argument.GetValue());
    }

    void TestCommandParser_TryGetArgumentWithValue_TwoArgumentsPresent_ReturnsTwoArguments() {
        const u64 expectedArgumentCount = 2;
        vector<string> commands = {"command", "--first_argument=first", "--second_argument=second"};

        CommandParser commandParser(commands);
        u64 argumentCount = commandParser.GetArgumentCount();

        TestSystem::AssertAreEqual(expectedArgumentCount, argumentCount);

        const auto firstArgumentName = "first_argument";
        Argument firstArgument;
        commandParser.TryGetArgumentWithValue(firstArgumentName, firstArgument);
        TestSystem::AssertStringsAreEqual(firstArgumentName, firstArgument.GetName());
        TestSystem::AssertStringsAreEqual("first", firstArgument.GetValue());

        const auto secondArgumentName = "second_argument";
        Argument secondArgument;
        commandParser.TryGetArgumentWithValue(secondArgumentName, secondArgument);
        TestSystem::AssertStringsAreEqual(secondArgumentName, secondArgument.GetName());
        TestSystem::AssertStringsAreEqual("second", secondArgument.GetValue());
    }

    void TestCommandParser_TryGetArgumentWithValue_ArgumentHasNoValue_ReturnsArgumentHasNoValue() {
        const bool expectedResult = false;
        const string expectedName = "first_argument";
        vector<string> commands = {"--first_argument"};

        CommandParser commandParser(commands);
        Argument foundArgument;
        auto result = commandParser.TryGetArgumentWithValue("first_argument", foundArgument);

        TestSystem::AssertAreEqual<bool>(expectedResult, result);
        TestSystem::AssertStringsAreEqual(expectedName, foundArgument.GetName());
    }
}