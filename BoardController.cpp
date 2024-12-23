#include "BoardController.h"
#include "AIController.h"
#include "Player.h"

BoardController::BoardController()
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            board[i][j] = 0;
}


void BoardController::addMove(const node& move) 
{
    for (const auto& existingNode : n_nodes)
    {
        if (existingNode.x == move.x && existingNode.y == move.y)
        {
            cout << "This cell is already taken. Please try again." << endl;
            return;
        }
    }
    moveHistory.push_back(move); // Lưu nước đi vào lịch sử
    n_nodes.push_back(move);
}


void BoardController::draw(GraphicController& graphic)
{
    graphic.drawBoard(n_nodes);
}

int BoardController::playerMove(SafeInt& player, Player &player1, Player& player2)
{
    int x, y;

    while (true) 
    {  // Lặp cho đến khi nhập nước đi hợp lệ
        cout << "Player " << (player == 1 ? "1 (X)" : "2 (O)") << "'s turn: ";
        cin >> x >> y;

        // Kiểm tra tọa độ hợp lệ
        if (x < 0 || x >= 10 || y < 0 || y >= 10) 
        {
            cout << "Invalid move. Please try again.\n";
            continue;
        }

        // Kiểm tra ô có trống không
        if (board[x][y] != 0) 
        {
            cout << "This cell is already taken. Please try again.\n";
            continue;
        }

        break;  // Nước đi hợp lệ, thoát vòng lặp
    }

    // Tạo node cho nước đi mới
    node newMove(x,y,player);
    

    // Thêm nước đi vào vector và cập nhật trạng thái bàn cờ
    addMove(newMove);
    board[x][y] = player;

    // Kiểm tra thắng thua
    if (checkWin(newMove)) 
    {
        if (player == 1)
        {
            cout << player1.getName() << " (X) wins!\n";
            player1.incrementWins();
            player2.incrementLosses();
        }
        else
        {
            cout << player2.getName() << " (O) wins!\n";
            player2.incrementWins();
            player1.incrementLosses();
        }
        return 0;
    }

    // Kiểm tra hòa
    if (isBoardFull()) 
    {
        cout << "It's a draw! No more moves left.\n";
        player1.incrementDraws();
        player2.incrementDraws();
        return 0;
    }
    player = (player == 1) ? 2 : 1;
}

bool BoardController::checkWin(const node& lastMove)
{
    // Lấy thông tin từ nước đi cuối cùng
    int x = lastMove.x;
    int y = lastMove.y;
    int player = lastMove.data;

    // Các hướng di chuyển: dọc, ngang, chéo chính, chéo phụ
    const int dx[] = { 0, 1, 1, 1 };
    const int dy[] = { 1, 0, 1, -1 };

    // Duyệt qua từng hướng
    for (int direction = 0; direction < 4; direction++)
    {
        int count = 1; // Bắt đầu với nước đi vừa thực hiện

        // Kiểm tra theo hướng chính
        for (int step = 1; step < 5; step++)
        {
            int nx = x + step * dx[direction];
            int ny = y + step * dy[direction];
            if (nx < 0 || nx >= 10 || ny < 0 || ny >= 10)
                break;

            // Kiểm tra ô tiếp theo có thuộc cùng người chơi không
            if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 &&
                isPlayerAt(nx, ny, player))
            {
                count++;
            }
            else
            {
                break;
            }
        }

        // Kiểm tra theo hướng ngược lại
        for (int step = 1; step < 5; step++)
        {
            int nx = x - step * dx[direction];
            int ny = y - step * dy[direction];
            if (nx < 0 || nx >= 10 || ny < 0 || ny >= 10)
                break;

            // Kiểm tra ô tiếp theo có thuộc cùng người chơi không
            if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 &&
                isPlayerAt(nx, ny, player))
            {
                count++;
            }
            else
            {
                break;
            }
        }

        // Nếu đếm đủ 5 ô liên tiếp thì thắng
        if (count >= 5)
        {
            return true;
        }
    }

    return false; // Không tìm thấy chuỗi 5 ô liên tiếp
}


bool BoardController::isPlayerAt(int x, int y, int player)
{
    for (const auto& n : n_nodes)
    {
        if (n.x == x && n.y == y && n.data == player)
        {
            return true;
        }
    }
    return false;
}

bool BoardController::isBoardFull()
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (board[i][j] == 0)  // Nếu còn ô trống
                return false;

    return true;  // Không còn ô trống
}


//void BoardController::botMove(int difficulty) 
//{
//    AIController ai(difficulty);
//    node bestMove = ai.getBestMove(board);
//
//    AIController::makeMove(board,bestMove, 2); // 2 là giá trị đại diện cho bot
//    board[bestMove.x][bestMove.y] = 2;
//
//    cout << "Bot placed at (" << bestMove.x << ", " << bestMove.y << ")\n";
//
//    if (checkWin(bestMove)) 
//    {
//        cout << "Bot wins!\n";
//        exit(0);
//    }
//
//    if (isBoardFull()) 
//    {
//        cout << "It's a draw!\n";
//        exit(0);
//    }
//}


int BoardController::move(SafeInt& player, int difficulty)
{
    SafeInt x, y;

    if (player == 1) // Nếu là lượt của người chơi
    {
        while (true)
        {  // Lặp cho đến khi nhập nước đi hợp lệ
            cout << "Player " << (player == 1 ? "1 (X)" : "2 (O)") << "'s turn: ";
            cin >> x >> y;

            // Kiểm tra tọa độ hợp lệ
            if (x < 0 || x >= 10 || y < 0 || y >= 10)
            {
                cout << "Invalid move. Please try again.\n";
                continue;
            }

            // Kiểm tra ô có trống không
            if (board[x][y] != 0)
            {
                cout << "This cell is already taken. Please try again.\n";
                continue;
            }

            break;  // Nước đi hợp lệ, thoát vòng lặp
        }

        // Tạo node cho nước đi mới
        node newMove(x, y, player);

        // Thêm nước đi vào vector và cập nhật trạng thái bàn cờ
        addMove(newMove);
        board[x][y] = player;

        cout << "Player " << (player == 1 ? "X" : "O") << " placed at (" << x << ", " << y << ")\n";

        // Kiểm tra thắng thua
        if (checkWin(newMove))
        {
            cout << "Player " << (player == 1 ? "X" : "O") << " wins!\n";
            return 0;
        }

        // Kiểm tra hòa
        if (isBoardFull())
        {
            cout << "It's a draw! No more moves left.\n";
            return 0;
        }

        // Chuyển lượt cho bot (player 2)
        player = 2;
    }
    else if (player == 2) // Nếu là lượt của bot
    {
        // AI di chuyển
        AIController ai( difficulty); // Điều chỉnh độ khó nếu cần, ở đây là 1
        node bestMove = ai.getBestMove(board);

        // Bot di chuyển
        AIController::makeMove(board, bestMove, 2); // 2 là giá trị đại diện cho bot


        

        // Thêm nước đi vào vector và cập nhật trạng thái bàn cờ
        addMove(bestMove);



        board[bestMove.x][bestMove.y] = player;

        cout << "Bot placed at (" << bestMove.x << ", " << bestMove.y << ")\n";

        // Kiểm tra kết quả
        if (checkWin(bestMove))
        {
            cout << "Bot wins!\n";
            return 0;
        }

        if (isBoardFull())
        {
            cout << "It's a draw!\n";
            return 0;
        }

        // Chuyển lượt cho người chơi (player 1)
        player = 1;
    }
}


void BoardController::saveGameHistory(const string& filename) const 
{
    ofstream outFile(filename);
    if (!outFile) 
    {
        cerr << "Error: Unable to save game history.\n";
        return;
    }

    for (const auto& move : moveHistory) 
    {
        outFile << move.x << "," << move.y << "," << move.data << "\n";
    }

    outFile.close();
    cout << "Game history saved to " << filename << ".\n";
}

void BoardController::replayGame(const string& filename) 
{
    GraphicController graphicCtrl;
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Unable to open game history file.\n";
        return;
    }

    cout << "Replaying game...\n";
    this->resetBoard(); // Xóa bàn cờ

    int x, y, player;
    char comma1, comma2;
    while (inFile >> x >> comma1 >> y >> comma2 >> player) 
    {
        if (comma1 != ',' || comma2 != ',') 
        {
            cerr << "Error: Invalid file format.\n";
            return;
        }
        n_nodes.emplace_back(node(x, y, player));

        this->board[x][y] = player;    // Đặt quân cờ
        this->draw(graphicCtrl);       // Vẽ lại bàn cờ
        this_thread::sleep_for(chrono::seconds(1)); // Tạm dừng
    }

    inFile.close();
    cout << "Replay finished.\n";
}
void BoardController::resetBoard() 
{
    for (int i = 0; i < 10; ++i) 
    {
        for (int j = 0; j < 10; ++j) 
        {
            board[i][j] = 0;
        }
    }
    moveHistory.clear();
}


