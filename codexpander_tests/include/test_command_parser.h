#pragma once

namespace CodEXpander::Tests {
    void TestCommandParser_ParseArguments_StringIsEmpty_NoArguments();
    void TestCommandParser_ParseArguments_ArgumentWithOnePrexifSymbol_ReturnsNoArguments();
    void TestCommandParser_TryGetArgument_NameIsEmpty_ReturnsFalse();
    void TestCommandParser_TryGetArgument_NameIsValid_ArgumentDoesNotExist_ReturnsFalse();
    void TestCommandParser_TryGetArgumentWithValue_ArgumentWithBothPrefixSymbol_ReturnsOneArgument();
    void TestCommandParser_TryGetArgumentWithValue_TwoArgumentsPresent_ReturnsTwoArguments();
    void TestCommandParser_TryGetArgumentWithValue_ArgumentHasNoValue_ReturnsArgumentHasNoValue();
}