#ifndef BOARD_HEADER
#define BOARD_HEADER

#include "Helper.h"
#include <bitset>
#include <vector>

using namespace std;


class Board {
public:

    static vector<Move> GetMoves(State<7, 6>& simBoard);

    static void MakeMove(State<7, 6>& simBoard, Move move);

    static Color WhoWins(State<7, 6>& simBoard);
};


#endif
