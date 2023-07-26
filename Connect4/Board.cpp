#include "Board.h"

vector<int> Board::GetMoves(State<7, 6>& simBoard)
{
	vector<int> moves = vector<int>();

	for (size_t i = 0; i < 7; i++)
	{
		int column = positionOrder()[i];

		if (!simBoard.mask.test(column + 35)) 
			moves.push_back(column);
	}
	return moves;
}

Color Board::MakeMove(State<7, 6>& board, int move) {

	// Changing the position to represent the opposing player 
	board.position ^= board.mask;

	board.mask |= (board.mask & Helper::FileMasks()[move]) >> 7;
	//board.mask |= board.mask.to_ulong() + (1ull << move);
	
	Color didWon = (Board::Check4Alignment(board.position)) ? (board.isRedTurn ? Red : Blue) : None;;

	board.isRedTurn = !board.isRedTurn;
	
	board.moves++;

	return didWon;
	
}

void Board::SetPosition(State<7, 6>& board, string position)
{
	for (int i = 0; i < position.size(); i++) {
		
		vector<int> moves = Board::GetMoves(board);
		
		int X = static_cast<int>(position[i]) - 49;

		for (size_t l = 0; l < moves.size(); l++)
		{

			if (moves[l] == X)
			{
				Board::MakeMove(board, moves[l]);
				break;
			}
		}

	}
}

Color Board::WhoWins(State<7, 6>& board)
{
	if (Check4Alignment(board.position))
		return (board.isRedTurn ? Red : Blue);

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
	vector<int> moves = Board::GetMoves(board);
	for (size_t i = 0; i < moves.size(); i++)
	{
		State<7, 6> simBoard = board;
		if (Board::MakeMove(simBoard, moves[i]) != 0){
			return true;
		}
	}
	return false;

}
