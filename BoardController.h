#pragma once
#include"GraphicController.h"
#include "AIController.h"
#include<vector>
#include<iostream>
#include <thread>
#include <chrono>
#include"SafeInt.h"
#include "Player.h"

using namespace std;
class BoardController
{
	vector <node> n_nodes;
    vector<vector<int>> board = vector<vector<int>>(10, vector<int>(10, 0)); // Khởi tạo board 10x10 với giá trị 0
    vector<node> moveHistory; // Lưu lịch sử các nước đi
public:
	BoardController();
    void draw(GraphicController& graphic);
    int playerMove(SafeInt& player, Player& player1, Player& player2);     //2 người             // Hàm đánh cờ cho 2 người chơi
    bool checkWin(const node& lastMove);
    bool isPlayerAt(int x, int y, int player);
    bool isBoardFull();
    int move(SafeInt& player, int difficulty);          // Hàm đánh cờ cho người và máy
    


    void addMove(const node& move);  //thêm nước đi
    void saveGameHistory(const string& filename) const;
    void replayGame(const string& filename) ;

    void resetBoard();  //xóa bàn cờ

   
};

