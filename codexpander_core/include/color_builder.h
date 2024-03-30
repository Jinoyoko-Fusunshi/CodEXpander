#pragma once

#include "color.h"
#include "declarations.h"

namespace CodEXpander::Core {
    class ColorBuilder {
    private:
        std::string colorEscapeCharacter = "\033[";
        bool hasArguments = false;

        void AddParameter(std::string value);

    public:
        ColorBuilder() = default;
        ~ColorBuilder() = default;

        ColorBuilder& ForeGround();
        ColorBuilder& BackGround();
        ColorBuilder& SetRed(u8 redValue);
        ColorBuilder& SetGreen(u8 greenValue);
        ColorBuilder& SetBlue(u8 blueValue);
        Color Build();

        static Color White();
        static Color Cyan();
        static Color Red();
        static Color Yellow();
        static Color Green();    
    };
}