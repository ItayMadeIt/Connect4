#ifndef AI_HEADER
#define AI_HEADER

#include "Board.h"

class AI
{
public:
	Move CalculateBestMove(State<7, 6> board);
private:
	Move Minimax(State<7, 6> simBoard);
};

#endif AI_HEADER
