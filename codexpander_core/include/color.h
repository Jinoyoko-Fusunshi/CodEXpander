#pragma once

#include <string>

namespace CodEXpander::Core {
    class Color {
    public:
        std::string colorEscapeCharacter;

    public:
        Color() = default;
        explicit Color(std::string colorEscapeCharacter);
        ~Color() = default;

        static Color White();
        static Color Cyan();
        static Color Red();
        static Color Yellow();
        static Color Green(); 
    };
}