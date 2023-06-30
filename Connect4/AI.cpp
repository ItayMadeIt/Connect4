#include "AI.h"

int AI::Minimax(State<7, 6>& board, int depth, bool isMaximizingPlayer, int alpha, int beta) {
    if (depth == 0 || Board::WhoWins(board) != None) {
        // Base case: return evaluation score
        //Helper::PrintBoard(board);
        return static_cast<int>(Board::WhoWins(board));
    }

    if (isMaximizingPlayer) {
        int bestValue = INT_MIN;
        vector<Move> moves = Board::GetMoves(board);

        for (const auto& move : moves) {
            State<7, 6> newBoard = board;
            Board::MakeMove(newBoard, move);
            int value = Minimax(newBoard, depth - 1, false, alpha, beta);
            bestValue = max(bestValue, value);
            alpha = max(alpha, bestValue);
            if (beta <= alpha) {
                break;  // Alpha-beta pruning
            }
        }
        return bestValue;
    }
    else {
        int bestValue = INT_MAX;
        vector<Move> moves = Board::GetMoves(board);

        for (const auto& move : moves) {
            State<7, 6> newBoard = board;
            Board::MakeMove(newBoard, move);
            int value = Minimax(newBoard, depth - 1, true, alpha, beta);
            bestValue = min(bestValue, value);
            beta = min(beta, bestValue);
            if (beta <= alpha) {
                break;  // Alpha-beta pruning
            }
        }
        return bestValue;
    }
}

Move AI::CalculateBestMove(State<7, 6>& board, int depth) {
    vector<Move> moves = Board::GetMoves(board);
    int bestValue = INT_MIN;
    Move bestMove = {};

    for (const auto& move : moves) {
        State<7, 6> newBoard = board;
        Board::MakeMove(newBoard, move);
        int value = Minimax(newBoard, depth, board.isRedTurn, INT_MIN, INT_MAX);

        if (value > bestValue) {
            bestValue = value;
            bestMove = move;
        }
    }

    return bestMove;
}