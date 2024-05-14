#pragma once

namespace CodEXpander::Tests {
    void TestCommandParser_TryParseCommand_NoCommandsProvided_NoCommandFound();
    void TestCommandParser_TryParseCommand_NoCommandsProvided_ArgumentsProvided_NoCommandFound();
    void TestCommandParser_TryParseCommand_CommandAndArgumentsProvided_CommandNotExisting_CommandNotFound();
    void TestCommandParser_TryParseCommand_CommandAndArgumentsProvided_CommandExist_CommandWasFound();
}