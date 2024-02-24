#ifndef __COLORS_HPP__
#define __COLORS_HPP__

#include <iostream>


namespace colors
{
    enum class Color
    {
        BLACK = 30,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        RESET
    };

    enum class Style {
        NORMAL = 0,
        BOLD, 
        DIM,
        UNDERLINED,
        BLINK,
        REVERSE,
        HIDDEN

    };

    typedef struct { 
        Color color;
        Style style;
    } Font;
    
    std::ostream & operator << (std::ostream &os, Font font){
        if (font.style == Style::NORMAL) {
            os << "\033[" << static_cast<int>(font.color) << "m";
        }
        else {
            os << "\033[" << static_cast<int>(font.style) << ";" << static_cast<int>(font.color) << "m";
        }
        return os;
    };
}

#endif // __COLORS_HPP__
