#include "color.h"
#include "color_builder.h"

namespace CodEXpander::Core {
    Color::Color(std::string colorEscapeCharacter) {
        this->colorEscapeCharacter = colorEscapeCharacter;
    }

    Color Color::White() {
        return ColorBuilder()
            .ForeGround() 
            .SetRed(229)
            .SetGreen(229)
            .SetBlue(229)
            .Build();
    }

    Color Color::Cyan() {
        return ColorBuilder() 
            .ForeGround() 
            .SetRed(17)
            .SetGreen(168)
            .SetBlue(205)
            .Build();
    }

    Color Color::Red() {
        return ColorBuilder() 
            .ForeGround()
            .SetRed(205)
            .SetGreen(49)
            .SetBlue(49)
            .Build();
    }

    Color Color::Yellow() {
        return ColorBuilder() 
            .ForeGround()
            .SetRed(229)
            .SetGreen(229)
            .SetBlue(16)
            .Build();
    }

    Color Color::Green() {
        return ColorBuilder() 
            .ForeGround()
            .SetRed(13)
            .SetGreen(188)
            .SetBlue(121)
            .Build();
    }
}