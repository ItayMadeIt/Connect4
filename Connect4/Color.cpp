#include "Color.h"

std::ostream& operator<<(std::ostream& os, const Color& value) {
    switch (value) {
    case None:
        os << "None";
        break;
    case Red:
        os << "Red";
        break;
    case Blue:
        os << "Blue";
        break;
    default:
        break;
    }

    return os;
}