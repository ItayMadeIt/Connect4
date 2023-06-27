#include "Board.h"

Board::Board() {
	board = State<7, 6>(true);
}

vector<Move> Board::GetMoves(State<7, 6>& simBoard)
{
	vector<Move> moves = vector<Move>();
	Move move = Move();

	move.c = simBoard.isRedTurn ? Red : Blue;
	for (size_t i = 1; i <= 8; i++)
	{
		if (!simBoard.board.test(i * 7)) {
			move.x = i;
			moves.push_back(move);
		}
	}
}

void Board::MakeMove(State<7, 6>& simBoard, Move move) {
	int pos = move.x * 7;
	simBoard.board.set(pos);

	if (move.c) {
		simBoard.red.set(pos);
	}
	else {
		simBoard.blue.set(pos);
	}

}
