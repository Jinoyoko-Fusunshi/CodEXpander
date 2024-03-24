#pragma once

namespace CodEXpander::Core {
    typedef char i8;
    typedef short int i16;
    typedef int  i32;
    typedef long long i64;

    typedef unsigned char u8;
    typedef unsigned short int u16;
    typedef unsigned int  u32;
    typedef unsigned long long u64;

    typedef char c8;
    typedef wchar_t c16;

    constexpr unsigned short int MaxStringSize = 256;
}