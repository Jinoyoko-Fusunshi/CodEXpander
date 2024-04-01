#pragma once

namespace CodEXpander::Tests {
    void TestCommandParser_ParseArguments_StringIsEmpty_NoArguments();
    void TestCommandParser_ParseArguments_ArgumentWithOnePrexifSymbol_ReturnsNoArguments();
    void TestCommandParser_ParseArguments_ArgumentWithBothPrefixSymbol_ReturnsOneArgument();
    void TestCommandParser_ParseArguments_TwoArgumentsPresent_ReturnsTwoArguments();
    void TestCommandParser_TryGetExistingArgument_NameIsEmpty_ReturnsFalse();
    void TestCommandParser_TryGetExistingArgument_NameIsValid_ArgumentDoesNotExist_ReturnsFalse();
    void TestCommandParser_TryGetExistingArgument_NameIsValid_ArgumentDoesExist_ReturnsArgument();
    void TestCommandParser_TryGetExistingArgument_ArgumentDoesExist_ValueIsEmpty_ReturnsFalse();
}