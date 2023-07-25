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
	static Move CalculateBestMove(State<7, 6>& board, int depth);
	static int Minimax(State<7, 6>& board, int depth, bool isMaximizingPlayer, int alpha, int beta);
	static pair<int, int> Negamax(State<7, 6>& board);
	static pair<int, int> Negamax(State<7, 6>& board, int depth, int alpha, int beta);
};
#endif AI_HEADER 
