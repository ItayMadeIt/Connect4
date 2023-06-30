#include "AI.h"

MinimaxResult AI::CalculateBestMove(State<7, 6> board, int depth)
{
    Color won = Board::WhoWins(board);
    if (depth == 0 || won != None) {
        MinimaxResult result = {};
        result.bestEval = won;
        result.move = {};
        cout << "depth == 0:" << (depth == 0) << " won != None:" << (won != None) << endl;
        return result;
    }

    vector<Move> moves = Board::GetMoves(board);
    

    if (moves.size() == 0) {
        MinimaxResult result = {};
        result.bestEval = None;
        result.move = {};
        return result;
    }
    
    
    vector<MinimaxResult> results;
    for (size_t i = 0; i < moves.size(); i++)
    {
        State<7, 6> simBoard = board;
        Board::MakeMove(simBoard, moves[i]);
        // If no one won, and you should check more moves (depth > 0) then calculate best move after this one
        results.push_back(CalculateBestMove(simBoard, depth-1));
        
    }
    MinimaxResult result = {};
    int maxValue = INT_MIN;
    int minValue = INT_MAX;
    for (size_t i = 0; i < results.size(); i++)
    {
        if (result.bestEval > maxValue && board.isRedTurn) {
            result = results[i];
            maxValue = result.bestEval;
        }
        else if (result.bestEval < minValue && !board.isRedTurn) {
            result = results[i];
            minValue = result.bestEval;
        }
    }
    return result;
}