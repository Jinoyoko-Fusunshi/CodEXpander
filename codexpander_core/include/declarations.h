#pragma once

#include <cstdint>

namespace CodEXpander::Core {
    typedef int8_t i8;
    typedef int16_t i16;
    typedef int32_t  i32;
    typedef int64_t i64;

    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef int64_t u64;

    typedef char c8;
    typedef wchar_t c16;

    constexpr u8 MaxStringSize = static_cast<u8>(255);
}