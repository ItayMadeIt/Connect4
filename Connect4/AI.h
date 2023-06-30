#ifndef AI_HEADER
#define AI_HEADER

#include "Board.h"

struct MinimaxResult {
	int bestEval;
	Move move;
};

class AI
{
public:
	static MinimaxResult CalculateBestMove(State<7, 6> board, int depth);
};

#endif AI_HEADER
