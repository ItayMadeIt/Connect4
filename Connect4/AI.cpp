#include "AI.h"


pair<int, int> AI::Minimax(Position& board, int depth, float alpha, float beta) {
    assert(alpha < beta);
    
    if (board.nbMoves() == board.SIZE) {
        return { 0, -1 };
    }

    for (size_t column = 0; column < board.WIDTH; column++)
    {
        if (board.canPlay(column) && board.isWinningMove(column)) {
            return { (board.SIZE + 1 - board.nbMoves()) / 2 , column };
        }
    }

    if (depth == 0) {
        return { 0, -1 };
    }
    
    int max = (board.SIZE - 1 - board.nbMoves()) / 2;
    if (beta > max) {
        beta = max;
        if (alpha >= beta) return { beta, -1 };
    }

    for (size_t column = 0; column < board.WIDTH; column++)
    {
        if (board.canPlay(ColumnOrder()[column])) {
            Position simBoard(board);

            simBoard.play(ColumnOrder()[column]);

            int score = -Minimax(simBoard,depth-1, -beta, -alpha).first;

            if (score >= beta) return { score, ColumnOrder()[column] };
            if (score > alpha) alpha = score;
        }
    }

    return { alpha, -2 };

}

pair<int, int> AI::Minimax(State<7, 6> board, int depth, float alpha, float beta) {
    assert(alpha < beta);
    if (board.moves == board.size || depth == 0)
        return {0, -1 };
     
    vector<int> moves = Board::GetMoves(board);
    
    int max = (board.size - 1 - board.moves) / 2;
    int xMove = moves[0];
    if (beta > max) {
        beta = max;
        if (alpha >= beta) return { beta, -1 };
    }

    for (size_t i = 0; i < moves.size(); i++)
    {

        State<7, 6> simBoard = board;
        if (Board::MakeMove(simBoard, moves[i]) != 0) {
            return { (board.size + 1 - board.moves) / 2 , moves[i]};
        }

        float eval = -Minimax(simBoard, depth - 1, -beta, -alpha).first;

        if (eval >= beta) return { eval, moves[i]};
        if (eval > alpha) alpha = eval;
    }
    return { alpha, xMove };
}
