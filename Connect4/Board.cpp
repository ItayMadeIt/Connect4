#include "Board.h"

vector<Move> Board::GetMoves(State<7, 6>& simBoard)
{
	vector<Move> moves = vector<Move>();
	Move move = Move();

	move.c = simBoard.isRedTurn ? Red : Blue;

	for (size_t i = 0; i < 7; i++)
	{
		int column = positionOrder()[i];
		if (!simBoard.board.test(column + 35)) {
			move.x = column;
			moves.push_back(move);
		}
	}
	return moves;
}

void Board::MakeMove(State<7, 6>& simBoard, Move move) {
	int xPos = move.x;
	int height = (Helper::FileMasks()[xPos] & simBoard.board).count();


	int finalPos = height * 7 + xPos;

	simBoard.board.set(finalPos);

	simBoard.moves++;

	if (move.c == Red) {
		simBoard.red.set(finalPos);
		simBoard.isRedTurn = false;
	}
	else {
		simBoard.blue.set(finalPos);
		simBoard.isRedTurn = true;
	}

}

void Board::SetPosition(State<7, 6>& board, string position)
{
	for (int i = 0; i < position.size(); i++) {
		
		vector<Move> moves = Board::GetMoves(board);
		
		int X = static_cast<int>(position[i]) - 49;

		for (size_t l = 0; l < moves.size(); l++)
		{

			if (moves[l].x == X)
			{
				Board::MakeMove(board, moves[l]);
				break;
			}
		}

	}
}

Color Board::WhoWins(State<7, 6>& simBoard)
{
	if (simBoard.moves <= 6) // 3 for each side cannot have a winner or if the number of moves is the number 
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
