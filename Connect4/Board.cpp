#include "Board.h"

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
	if (simBoard.board.count() <= 6) // 3 for each side cannot have a winner
		return None;


	for (bitset<42> winningCheck : Helper::VerticalWins())
	{
		// Check if there are disks at the winning check
		// if not continue to the next one
		if ((simBoard.board & winningCheck).count() != 4)
			continue;
		
		// Blue won
		if ((winningCheck & simBoard.blue).count() == 4) {
			return Blue;
		}
		// Red won
		if ((winningCheck & simBoard.red).count() == 4) {
			return Red;
		}
	}

	for (bitset<42> winningCheck : Helper::HorizontalWins())
	{
		// Check if there are disks at the winning check
		// if not continue to the next one
		if ((simBoard.board & winningCheck).count() != 4)
			continue;


		// Blue won
		if ((winningCheck & simBoard.blue).count() == 4) {
			return Blue;
		}
		// Red won
		if ((winningCheck & simBoard.red).count() == 4) {
			return Red;
		}
	}

	for (bitset<42> winningCheck : Helper::UprightWins())
	{
		// Check if there are disks at the winning check
		// if not continue to the next one
		if ((simBoard.board & winningCheck).count() != 4)
			continue;


		// Blue won
		if ((winningCheck & simBoard.blue).count() == 4) {
			return Blue;
		}
		// Red won
		if ((winningCheck & simBoard.red).count() == 4) {
			return Red;
		}
	}

	for (bitset<42> winningCheck : Helper::DownrightWins())
	{
		// Check if there are disks at the winning check
		// if not continue to the next one
		if ((simBoard.board & winningCheck).count() != 4)
			continue;


		// Blue won
		if ((winningCheck & simBoard.blue).count() == 4) {
			return Blue;
		}
		// Red won
		if ((winningCheck & simBoard.red).count() == 4) {
			return Red;
		}
	}

	return None;
	
}
