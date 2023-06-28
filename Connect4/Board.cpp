#include "Board.h"

Board::Board() {
	board = State<7, 6>(true);
}

vector<Move> Board::GetMoves(State<7, 6>& simBoard)
{
	vector<Move> moves = vector<Move>();
	Move move = Move();

	move.c = simBoard.isRedTurn ? Red : Blue;
	for (size_t i = 0; i < 7; i++)
	{

		int height = (Helper::FileMasks()[i] & simBoard.board).count();
		if (height < 6) {
			move.x = i;
			move._RecievedHeight = height;
			moves.push_back(move);
		}
	}
	return moves;
}

void Board::MakeMove(State<7, 6>& simBoard, Move move) {
	int xPos = move.x;
	int height = move._RecievedHeight;

	int finalPos = height * 7 + xPos;

	simBoard.board.set(finalPos);

	if (move.c == Red) {
		simBoard.red.set(finalPos);
		simBoard.isRedTurn = false;
	}
	else {
		simBoard.blue.set(finalPos);
		simBoard.isRedTurn = true;
	}

}

Color Board::WhoWins(State<7, 6>& simBoard)
{
	Color winner = None;
	if (simBoard.board.count() <= 7)
		return winner;


	
}
