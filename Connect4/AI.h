#ifndef AI_HEADER
#define AI_HEADER
#include <cassert>

#include "Board.h"
#include "Position.hpp"

struct MinimaxResult {
	int bestEval;
	int move;
};

class AI
{
public:
	
	
	static int* ColumnOrder() {
		return new int[Position::WIDTH] { 3,2,4,1,5,0,6 };	
	}

	int NodeCount;
	static pair<int, int> Minimax(Position &board, int depth, float alpha, float beta);
	static pair<int, int> Minimax(State<7, 6> board, int depth, float alpha, float beta);
};
#endif AI_HEADER 
