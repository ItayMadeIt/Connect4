#include "AI.h"

int AI::Minimax(State<7, 6>& board, int depth, bool isMaximizingPlayer, int alpha, int beta) {
    Color winState = Board::WhoWins(board);
    
    if (depth == 0 || winState != None) {
        return winState; 
    }

    if (isMaximizingPlayer) {
        int bestValue = std::numeric_limits<int>::min();
        std::vector<Move> moves = Board::GetMoves(board);

        for (const auto& move : moves) {
            State<7, 6> newBoard = board;
            Board::MakeMove(newBoard, move);
            int value = Minimax(newBoard, depth - 1, false, alpha, beta);
            bestValue = std::max(bestValue, value);
        }
        return bestValue;
    }
    else {
        int bestValue = std::numeric_limits<int>::max();
        std::vector<Move> moves = Board::GetMoves(board);

        for (const auto& move : moves) {
            State<7, 6> newBoard = board;
            Board::MakeMove(newBoard, move);
            int value = Minimax(newBoard, depth - 1, true, alpha, beta);
            bestValue = std::min(bestValue, value);
        }
        return bestValue;
    }
}Move AI::CalculateBestMove(State<7, 6>& board, int depth) {
    std::vector<Move> moves = Board::GetMoves(board);
    int bestValue = 0;
    if (board.isRedTurn)
        bestValue = std::numeric_limits<int>::min();
    if (!board.isRedTurn)
        bestValue = std::numeric_limits<int>::max();
    Move bestMove = {};

    for (const auto& move : moves) {
        State<7, 6> newBoard = board;
        Board::MakeMove(newBoard, move);

        // Check if the move results in an immediate win for the opponent
        if (Board::WhoWins(newBoard) != Color::None) {
            continue;
        }

        int value = Minimax(newBoard, depth, !board.isRedTurn, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

        if (board.isRedTurn) {
            if (value > bestValue) {
                bestValue = value;
                bestMove = move;
            }
        }
        else {
            if (value < bestValue) {
                bestValue = value;
                bestMove = move;
            }
        }
    }

    return bestMove;
}