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

Color Board::MakeMove(State<7, 6>& simBoard, Move move) {
	int xPos = move.x;
	int height = (Helper::FileMasks()[xPos] & simBoard.board).count();


	int finalPos = height * 7 + xPos;

	simBoard.board.set(finalPos);

	simBoard.moves++;

	if (move.c == Red) {
		simBoard.red.set(finalPos);
		simBoard.isRedTurn = false;
		return (Board::Check4Alignment(simBoard.red)) ? Red : None;
	}
	else {
		simBoard.blue.set(finalPos);
		simBoard.isRedTurn = true;
		return (Board::Check4Alignment(simBoard.blue)) ? Blue : None;
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

Color Board::WhoWins(State<7, 6>& board)
{
	if (Check4Alignment(board.blue))
		return Blue;

	if (Check4Alignment(board.red))
		return Red;

	return None;
	
}

bool Board::Check4Alignment(bitset<42> board)
{
	// Horizontal
	bitset<42> hor = board & (board >> 1);
	if ((hor & (hor >> 2)) != 0)
		return true;


	// Vertical
	bitset<42> ver = board & (board >> 7);
	if ((ver & (ver >> 14)) != 0)
		return true;


	// Diagonal Right-Up
	bitset<42> digUp = board & (board >> 8);
	if ((digUp & (digUp >> 16)) != 0)
		return true;


	// Diagonal Right-Down
	bitset<42> digDown = board & (board >> 6);
	if ((digDown & (digDown >> 12)) != 0)
		return true;
	

	return false;
}


bool Board::CanWin(State<7, 6>& board)
{
	vector<Move> moves = Board::GetMoves(board);
	for (size_t i = 0; i < moves.size(); i++)
	{
		State<7, 6> simBoard = board;
		if (Board::MakeMove(simBoard, moves[i]) != 0){
			return true;
		}
	}
	return false;

}
