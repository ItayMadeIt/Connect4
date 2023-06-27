#ifndef HELPER_HEADER
#define HELPER_HEADER

#include <vector>
#include <bitset>

using namespace std;
template<int Width, int Height>
struct StateHelper {
    static constexpr int Size = Width * Height;
};

template<int Width, int Height>
struct State {
    static constexpr int size = StateHelper<Width, Height>::Size;
    bitset<size> red;
    bitset<size> blue;
    bitset<size> board;
    bool isRedTurn;
    State(bool isRedStarts) {
        isRedTurn = isRedStarts;
        red = 0;
        blue = 0;
        board = 0;
    }
    State() : State(true) {}
};
enum Color {
    Red = 0,
    Blue = 1
};

struct Move {
    int x;
    Color c;
};
class Helper
{

};

#endif