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

pair<float, int> AI::Minimax(State<7, 6>& board, int depth, float alpha, float beta) {
    int state = Board::WhoWins(board);
    if (board.moves == board.size || state != 0 || depth == 0)
        return { state, -1 };

    vector<Move> moves = Board::GetMoves(board);

    if (board.isRedTurn) {
        float maxEval = -1300;
        int xMove = -1;
        for (size_t i = 0; i < moves.size(); i++)
        {


            State<7, 6> simBoard = board;
            Board::MakeMove(simBoard, moves[i]);

            float eval = Minimax(simBoard, depth - 1, alpha, beta).first;
            eval /= pow(2, depth);
            if (eval > maxEval) {
                maxEval = eval;
                xMove = moves[i].x;
            }
            alpha = max(alpha, eval);

            // Alpha-beta pruning
            if (alpha >= beta)
                break;
        }
        return { maxEval, xMove };
    }
    else {
        float minEval = 1300;
        int xMove = -1;
        for (size_t i = 0; i < moves.size(); i++)
        {

            State<7, 6> simBoard = board;
            Board::MakeMove(simBoard, moves[i]);

            float eval = Minimax(simBoard, depth - 1, alpha, beta).first; // Negate the evaluation for opponent
            eval /= depth;

            if (eval < minEval) {
                minEval = eval;
                xMove = moves[i].x;
            }
            beta = min(beta, eval);

            // Alpha-beta pruning
            if (alpha >= beta)
                break;
        }
        return { minEval, xMove }; // Return -1 as the move, as we are not returning the best move
    }
}
