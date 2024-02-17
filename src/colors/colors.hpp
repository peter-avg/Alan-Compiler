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

    std::ostream &operator<<(std::ostream &os, Color color){
        return os << "\033[" << static_cast<int>(color) << "m";
    };
}

#endif // __COLORS_HPP__
