#pragma once

#include <vector>
#include "GraphicController.h"
using namespace std;

class AIController {

public:
    node getBestMove(vector<vector<int>>& board);
    AIController(int difficulty);
    int minimax(vector<vector<int>>& board, int depth, bool isMaximizingPlayer, int alpha, int beta);
    vector<node> getAvailableMoves(const vector<vector<int>>& board);
    int evaluateBoard(const vector<vector<int>>& board);
    static void makeMove(vector<vector<int>>& board, node move, int player);
    void undoMove(vector<vector<int>>& board, node move);

    int m_difficulty;
};

