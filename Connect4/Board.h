#ifndef BOARD_HEADER
#define BOARD_HEADER

#include "Helper.h"


using namespace std;


class Board {
public:
    static vector<int> positionOrder() { return { 3,2,4,5,1,6,0 }; };

    // Moves as X
    static vector<int> GetMoves(State<7, 6>& simBoard);

    static Color MakeMove(State<7, 6>& simBoard, int move);

    static void SetPosition(State<7, 6>& board, string position);

    static Color WhoWins(State<7, 6>& board);

    static bool Check4Alignment(bitset<42> board);

    static bool CanWin(State<7, 6>& simBoard);
};


#endif
