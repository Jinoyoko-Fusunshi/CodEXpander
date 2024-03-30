#include "color_builder.h"

namespace CodEXpander::Core {
    ColorBuilder& ColorBuilder::ForeGround() {
        AddParameter("38");
        AddParameter("2");
        return *this;
    }

    ColorBuilder& ColorBuilder::BackGround() {
        AddParameter("48");
        AddParameter("2");
        return *this;
    }

    ColorBuilder& ColorBuilder::SetRed(u8 redValue) {
        AddParameter(std::to_string(redValue));
        return *this;
    }

    ColorBuilder& ColorBuilder::SetGreen(u8 greenValue) {
        AddParameter(std::to_string(greenValue));
        return *this;
    }

    ColorBuilder& ColorBuilder::SetBlue(u8 blueValue) {
        AddParameter(std::to_string(blueValue));
        return *this;
    }

    Color ColorBuilder::Build() {
        colorEscapeCharacter += "m";
        return Color(colorEscapeCharacter);
    }

    void ColorBuilder::AddParameter(std::string value) {
        if (hasArguments)
            colorEscapeCharacter += ";";
        else
            hasArguments = true;

        colorEscapeCharacter += value;
    }
}

