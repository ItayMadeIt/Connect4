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
}
Move AI::CalculateBestMove(State<7, 6>& board, int depth) {
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

        int value = Minimax(newBoard, depth, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

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

pair<int,int> AI::Negamax(State<7, 6>& board) {
    if (board.moves == board.size)
        return { 0,-1 };

    vector<Move> moves = Board::GetMoves(board);
    for (size_t i = 0; i < moves.size(); i++)
    {
        State<7, 6> simBoard = board;
        Board::MakeMove(simBoard, moves[i]);
        if ((Board::WhoWins(simBoard) == 1 && board.isRedTurn) || (Board::WhoWins(simBoard) == -1 && !board.isRedTurn)) {
            return { (board.size + 1 - board.moves) / 2, moves[i].x };
        }
    }
    int xMove = moves[0].x;
    int bestScore = -board.size;

    for (size_t i = 0; i < moves.size(); i++)
    {
        State<7, 6> simBoard = board;
        Board::MakeMove(simBoard, moves[i]);
        int score = -Negamax(simBoard).first;
        if (score > bestScore) {
            bestScore = score;
            xMove = moves[i].x;
        }
    }

    return { bestScore, xMove };
}