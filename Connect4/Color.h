#ifndef COLOR_HEADER
#define COLOR_HEADER

// This class exists just so I would be able to print the color values as string

#include <iostream>

enum Color {
    Blue = -1,
    None =  0,
    Red  =  1
};
std::ostream& operator<<(std::ostream& os, const Color& value);

#endif