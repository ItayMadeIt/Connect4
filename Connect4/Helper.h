#ifndef HELPER_HEADER
#define HELPER_HEADER

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include "Color.h"

using namespace std;
template<int Width, int Height>
struct StateHelper {
    static constexpr int Size = Width * Height;
};

template<int Width, int Height>
struct State {
    static constexpr int size = StateHelper<Width, Height>::Size;

    bitset<size> position; // just the current player's disks
    bitset<size> mask; // all disks as ones 
    
    bool isRedTurn;
    
    State(bool isRedStarts) {
        isRedTurn = isRedStarts;
        moves = 0;
        mask = 0;
        position = 0;
    }
    int moves;
    State() : State(true) {}
};

class Helper
{
public:
    static void PrintBoard(bitset<42> b);
    static void PrintBoard(State<7, 6> state);

    static vector<bitset<42>> FileMasks();
    static vector<bitset<42>> fileMasks;
    
    // Those will be the opposite of what they should be
    // So a horizontal winning line can be for example this:
    // 1 1 1 1 1 1 1
    // 1 1 1 1 1 1 1
    // 1 1 1 1 1 1 1
    // 1 1 1 1 1 1 1
    // 1 1 0 0 0 0 1
    // 1 1 1 1 1 1 1
    // Basically ~ (not bitwise-operator) on the should be winning moves

    static vector<bitset<42>> HorizontalWins();
    static vector<bitset<42>> horizontalWins;
    static vector<bitset<42>> VerticalWins();
    static vector<bitset<42>> verticalWins;
    static vector<bitset<42>> UprightWins();
    static vector<bitset<42>> uprightWins;
    static vector<bitset<42>> DownrightWins();
    static vector<bitset<42>> downrightWins;
    
private:
};

#endif