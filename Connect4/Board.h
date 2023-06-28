#ifndef BOARD_HEADER
#define BOARD_HEADER

#include "Helper.h"
#include <bitset>
#include <vector>

using namespace std;


class Board {
public:

    Board();
    State<7, 6> board;

    vector<Move> GetMoves(State<7, 6>& simBoard);

    void MakeMove(State<7, 6>& simBoard, Move move);

    Color WhoWins(State<7, 6>& simBoard);
};


#endif
