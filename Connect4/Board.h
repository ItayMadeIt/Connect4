#ifndef BOARD_HEADER
#define BOARD_HEADER

#include "Helper.h"


using namespace std;


class Board {
public:
    static vector<int> positionOrder() { return { 3,2,4,5,1,6,0 }; };

    static vector<Move> GetMoves(State<7, 6>& simBoard);

    static void MakeMove(State<7, 6>& simBoard, Move move);

    static void SetPosition(State<7, 6>& board, string position);

    static Color WhoWins(State<7, 6>& simBoard);
};


#endif
