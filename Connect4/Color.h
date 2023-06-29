#ifndef COLOR_HEADER
#define COLOR_HEADER

// This class exists just so I would be able to print the color values as string

#include <iostream>

enum Color {
    None = -1,
    Red = 0,
    Blue = 1
};
std::ostream& operator<<(std::ostream& os, const Color& value);

#endif