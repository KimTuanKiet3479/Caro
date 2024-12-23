#include "AIController.h"
#include <limits>
#include<vector>

AIController::AIController(int difficulty) : m_difficulty(difficulty) {}

node AIController::getBestMove(vector<vector<int>>& board) 
{
    int bestValue = -10000;
    node bestMove;

    for (auto& move : getAvailableMoves(board)) 
    {
        makeMove(board, move, 2);  // 2 là AI
        int moveValue = minimax(board, m_difficulty - 1, false, -1000, 1000);
        undoMove(board, move);

        if (moveValue > bestValue) 
        {
            bestMove = move;
            bestValue = moveValue;
        }
    }
    return bestMove;
}

int AIController::minimax(vector<vector<int>>& board, int depth, bool isMaximizingPlayer, int alpha, int beta) 
{
    
    if (depth == 0) return evaluateBoard(board);

    if (isMaximizingPlayer) 
    {
        int maxEval = -1000;
        for (auto& move : getAvailableMoves(board)) 
        {
            makeMove(board, move, 2);
            int eval = minimax(board, depth - 1, false, alpha, beta);
            undoMove(board, move);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) break;
        }
        return maxEval;
    }
    else {
        int minEval = 1000;
        for (auto& move : getAvailableMoves(board)) 
        {
            makeMove(board, move, 1);
            int eval = minimax(board, depth - 1, true, alpha, beta);
            undoMove(board, move);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}

vector<node> AIController::getAvailableMoves(const vector<vector<int>>& board) 
{
    vector<node> moves;
    for (int i = 0; i < board.size(); i++) 
    {
        for (int j = 0; j < board[0].size(); j++) 
        {
            if (board[i][j] == 0) 
            {
                moves.push_back(node( i, j, 0 ));
            }
        }
    }
    return moves;
}

void AIController::makeMove(vector<vector<int>>& board, node move, int player) 
{
    board[move.x][move.y] = player;
}

void AIController::undoMove(vector<vector<int>>& board, node move) 
{
    board[move.x][move.y] = 0;
}

int AIController::evaluateBoard(const vector<vector<int>>& board) 
{
    const int AI = 2;         // Quân cờ của AI
    const int PLAYER = 1;     // Quân cờ của người chơi
    const int WIN_SCORE = 500;   // Điểm số khi thắng
    const int LOSE_SCORE = -500; // Điểm số khi thua

    float score = 0;

    // Các hướng di chuyển: ngang, dọc, chéo chính, chéo phụ
    const int dx[] = { 0, 1, 1, 1 };
    const int dy[] = { 1, 0, 1, -1 };

    // Duyệt qua từng ô trên bàn cờ
    for (int i = 0; i < board.size(); i++) 
    {
        for (int j = 0; j < board[0].size(); j++) 
        {
            if (board[i][j] != 0) {  // Chỉ xét ô đã có quân cờ
                int player = board[i][j];

                // Xét tất cả các hướng
                for (int dir = 0; dir < 4; dir++)
                {
                    int count = 1;  // Số quân cờ liên tiếp
                    bool blockedStart = false, blockedEnd = false;

                    // Kiểm tra theo hướng chính
                    for (int step = 1; step < 5; ++step) 
                    {
                        int ni = i + step * dx[dir];
                        int nj = j + step * dy[dir];
                        if (ni < 0 || ni >= board.size() || nj < 0 || nj >= board[0].size()) 
                        {
                            blockedEnd = true;  // Bị chặn ở cuối
                            break;
                        }
                        if (board[ni][nj] == player) count++;
                        else if (board[ni][nj] != 0) 
                        {
                            blockedEnd = true;  // Bị chặn bởi quân đối phương
                            break;
                        }
                        else break;  // Ô trống
                    }

                    // Kiểm tra theo hướng ngược lại
                    for (int step = 1; step < 5; step++)
                    {
                        int ni = i - step * dx[dir];
                        int nj = j - step * dy[dir];
                        if (ni < 0 || ni >= board.size() || nj < 0 || nj >= board[0].size()) 
                        {
                            blockedStart = true;  // Bị chặn ở đầu
                            break;
                        }
                        if (board[ni][nj] == player) count++;
                        else if (board[ni][nj] != 0) 
                        {
                            blockedStart = true;  // Bị chặn bởi quân đối phương
                            break;
                        }
                        else break;  // Ô trống
                    }

                    // Tính điểm dựa trên số quân liên tiếp và tình trạng bị chặn
                    if (player == AI) 
                    {
                        if (count == 4 && !blockedStart && !blockedEnd) score += count * 6;
                        if (count >= 5) return WIN_SCORE;  // AI thắng
                        if (!blockedStart && !blockedEnd) score += count * 1;  // Hai đầu không bị chặn
                        else if (!blockedStart || !blockedEnd) score += count * 0.5;  // Một đầu bị chặn
                    }
                    else if (player == PLAYER) 
                    {
                        if(count == 4 && !blockedStart && !blockedEnd) score -= count * 7;
                        if(count == 4 && (!blockedStart || !blockedEnd)) score -= count * 5;
                        if(count == 3 && !blockedStart && !blockedEnd) score -= count * 3;
                        if (count >= 5) return LOSE_SCORE;  // Người chơi thắng
                        if (!blockedStart && !blockedEnd) score -= count * 1;  // Hai đầu không bị chặn
                        else if (!blockedStart || !blockedEnd) score -= count * 0.3;  // Một đầu bị chặn
                    }
                }
            }
        }
    }

    return score;  // Trả về điểm số tổng kết của bàn cờ
}

