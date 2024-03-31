#pragma once

namespace CodEXpander::Tests {
    void TestCommandParser_ParseArguments_StringIsEmpty_NoArguments();
    void TestCommandParser_ParseArguments_ArgumentWithOnePrexifSymbol_ReturnsNoArguments();
    void TestCommandParser_ParseArguments_ArgumentWithBothPrefixSymbol_ReturnsOneArgument();
    void TestCommandParser_ParseArguments_TwoArgumentsPresent_ReturnsTwoArguments();
}