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
	int height = (Helper::FileMasks()[move] & board.mask).count();

	board.position ^= board.mask;
	
	board.mask.set(height * 7 + move);

	Color didWon = (Board::Check4Alignment((board.mask ^ board.position).to_ullong())) ? (board.isRedTurn ? Red : Blue) : None;


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
	if (Check4Alignment( (board.mask ^ board.position).to_ullong() ) ) {
		return (!board.isRedTurn ? Red : Blue);
	}
	return None;
	
}

bool Board::Check4Alignment(uint64_t board)
{
	// Horizontal
	uint64_t hor = board & (board >> 1);
	if ((hor & (hor >> 2)))
		return true;


	// Vertical
	uint64_t ver = board & (board >> 7);
	if ((ver & (ver >> 14)))
		return true;


	// Diagonal Right-Up
	uint64_t digUp = board & (board >> 8);
	if ((digUp & (digUp >> 16)))
		return true;


	// Diagonal Right-Down
	uint64_t digDown = board & (board >> 6);
	if ((digDown & (digDown >> 12)))
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
