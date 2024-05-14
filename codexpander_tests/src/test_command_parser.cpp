#include "test_command_parser.h"
#include "command_parser.h"
#include "declarations.h"
#include "test_system.h"

using namespace CodEXpander::Core; 
using std::string, std::vector;

namespace CodEXpander::Tests {
    class TestCommand final : public Command {
    public:
        explicit TestCommand(Logger &logger)
            : Command(logger, vector<ValidArgument>(), "test") {}
        ~TestCommand() = default;

        void Execute() {}
    };

    void TestCommandParser_TryParseCommand_NoCommandsProvided_NoCommandFound() {
        const bool exptectedResult = false;
        Command* expectedCommand = nullptr;
        
        auto commandParser = CommandParser(vector<Command*>());
        Command* foundCommand = nullptr;
        auto commandExists = commandParser.TryParseCommand(vector<string>(), foundCommand);
    
        TestSystem::AssertValues(exptectedResult, commandExists);
        TestSystem::AssertObjects(expectedCommand, foundCommand);
    }

    void TestCommandParser_TryParseCommand_NoCommandsProvided_ArgumentsProvided_NoCommandFound() {
        const bool exptectedResult = false;
        Command* expectedCommand = nullptr;
        
        const vector<string> arguments = {"--first_argument=first"};
        auto commandParser = CommandParser(vector<Command*>());
        Command* foundCommand = nullptr;
        auto commandExists = commandParser.TryParseCommand(arguments, foundCommand);
    
        TestSystem::AssertValues(exptectedResult, commandExists);
        TestSystem::AssertObjects(expectedCommand, foundCommand);
    }

    void TestCommandParser_TryParseCommand_CommandAndArgumentsProvided_CommandNotExisting_CommandNotFound() {
        Logger logger;
        TestCommand testCommand(logger);
        const vector<Command*> availableCommands = {&testCommand};
        Command* expectedCommand = nullptr;
        const bool exptectedResult = false;
        
        const vector<string> arguments = {"codexpander_tests command --first_argument=first"};
        auto commandParser = CommandParser(vector<Command*>());
        Command* foundCommand = nullptr;
        auto commandExists = commandParser.TryParseCommand(arguments, foundCommand);
    
        TestSystem::AssertValues(exptectedResult, commandExists);
        TestSystem::AssertObjects(expectedCommand, foundCommand);
    }

    void TestCommandParser_TryParseCommand_CommandAndArgumentsProvided_CommandExist_CommandWasFound() {
        Logger logger;
        TestCommand testCommand(logger);
        const vector<Command*> availableCommands = {&testCommand};
        Command* expectedCommand = &testCommand;
        const bool exptectedResult = true;
        
        const vector<string> arguments = {"codexpander_tests", "test"};
        auto commandParser = CommandParser(availableCommands);
        Command* foundCommand = nullptr;
        auto commandExists = commandParser.TryParseCommand(arguments, foundCommand);
    
        TestSystem::AssertValues(exptectedResult, commandExists);
        TestSystem::AssertObjects(expectedCommand, foundCommand);
    }
}