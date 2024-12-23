#include "ScreenController.h"
#include "GraphicController.h"
#include "BoardController.h"
#include "Player.h"
ScreenController* ScreenController:: m_instance = nullptr;

ScreenController::ScreenController()
{

}
ScreenController* ScreenController:: getInstance()
{
	  if (m_instance == nullptr)
	  {
		  m_instance = new ScreenController();
	  }
	  return m_instance;
}

void ScreenController::startGameWithBot()
{
    cout << "\n=== Select Bot Difficulty ===\n";
    cout << "1. Easy\n";
    cout << "2. Normal\n";
    cout << "3. Hard\n";
    cout << "Enter your choice: ";
    SafeInt choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Starting game with Easy Bot...\n";
        startBotGame(Difficulty::EASY);
        break;
    case 2:
        cout << "Starting game with Normal Bot...\n";
        startBotGame(Difficulty::NORMAL);
        break;
    case 3:
        cout << "Starting game with Hard Bot...\n";
        startBotGame(Difficulty::HARD);
        break;
    default:
        cout << "Invalid choice! Returning to Main Menu.\n";
        gotoScreen(SCREEN_ID::MAIN_MENU);
        break;
    }
}


void ScreenController::gotoScreen(SCREEN_ID scr)
{
    m_screenStack.push(scr); // Lưu màn hình hiện tại vào stack
    m_currentScreen = scr;

    // Xử lý từng màn hình
    switch (scr)
    {
    case SCREEN_ID::MAIN_MENU:
        displayMainMenu();
        break;

    case SCREEN_ID::PLAY_WITH_BOT:
        startGameWithBot();
        break;

    case SCREEN_ID::BOARD_PLAYER:
        startGameForTwoPlayers();
        break;

    case SCREEN_ID::PLAYER_RESULT:
        Player::displayAllPlayers("players_data.txt");
        break;
    case SCREEN_ID::REPLAY_LASTGAME:
        replayLastGame();
        break;
    default:
        cout << "Invalid screen ID!" << endl;
        break;
    }
}


void ScreenController:: back()
{
	if (m_screenStack.empty())
	{
		home();
	}
	m_screenStack.pop();
	gotoScreen(m_screenStack.top());
}
void ScreenController:: home()
{
	while (!m_screenStack.empty())
	{
		m_screenStack.pop();
	}
	m_screenStack.push(SCREEN_ID::MAIN_MENU);
	gotoScreen(m_screenStack.top());
}


void ScreenController::displayMainMenu()
{
    cout << "=== Main Menu ===\n";
    cout << "1. Play with Bot\n";
    cout << "2. Two Player Mode\n";
    cout << "3. Player Result\n";
    cout << "4. Replay Last Game\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    SafeInt choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        gotoScreen(SCREEN_ID::PLAY_WITH_BOT);
        break;
    case 2:
        gotoScreen(SCREEN_ID::BOARD_PLAYER);
        break;
    case 3:
        gotoScreen(SCREEN_ID::PLAYER_RESULT);
        break;
    case 4:
        gotoScreen(SCREEN_ID::REPLAY_LASTGAME);
        break;
    case 5:
        cout << "Exiting game. Goodbye!\n";
        exit(0);
    default:
        cout << "Invalid choice! Returning to Main Menu.\n";
        gotoScreen(SCREEN_ID::MAIN_MENU);
        break;
    }
}


void ScreenController::startGameForTwoPlayers()
{
    BoardController boardCtrl;
    GraphicController graphicCtrl;
    string player1Name, player2Name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter name for Player 1 (X): ";
    getline(cin, player1Name); // Đọc cả dòng cho tên Player 1

    cout << "Enter name for Player 2 (O): ";
    getline(cin, player2Name); // Đọc cả dòng cho tên Player 2

    // Hiển thị lại để kiểm tra
    cout << "Player 1: " << player1Name << " (X)" << endl;
    cout << "Player 2: " << player2Name << " (O)" << endl;

    Player player1(player1Name, 0, 0, 0);  // Khởi tạo người chơi 1
    Player player2(player2Name, 0, 0, 0);  // Khởi tạo người chơi 2
    SafeInt currentPlayer = 1;// 1 là X, 2 là O
    
    int i = -1;
    do
    {

        boardCtrl.draw(graphicCtrl);


        i = boardCtrl.playerMove(currentPlayer, player1, player2);

    } while (i != 0);
    player1.updateOrAddPlayer(player1,"players_data.txt");
    player2.updateOrAddPlayer(player2,"players_data.txt");
    boardCtrl.saveGameHistory("game_history.txt");
    gotoScreen(SCREEN_ID::MAIN_MENU);
}



void ScreenController::startBotGame(Difficulty difficulty)
{
    // Khởi tạo BoardController và GraphicController
    BoardController boardController;
    GraphicController graphicController;
    SafeInt currentPlayer; // 1 là người chơi, 2 là bot
    

    cout << "Player first or Bot first?" << endl << "1. Player first" << endl << "2. Bot first" << endl;
    do
    {
        
        cin >> currentPlayer;
        if (currentPlayer != 1 && currentPlayer != 2) cout << "Invalid choice. Please try again (1: Player, 2: Bot): ";
    } while (currentPlayer != 1 && currentPlayer != 2);
    
    // Vẽ bàn cờ lần đầu tiên
    boardController.draw(graphicController);
    int i = -1;
    do
    {
        i = boardController.move(currentPlayer, difficulty);  // Gọi hàm move chung cho người và bot
        boardController.draw(graphicController);   // Vẽ lại bàn cờ
    } while (i != 0);
    

    // Trở về màn hình chính sau khi kết thúc trò chơi
    /*ScreenController* screenController = ScreenController::getInstance();
    screenController->gotoScreen(SCREEN_ID::MAIN_MENU);*/
    gotoScreen(SCREEN_ID::MAIN_MENU);
}


void ScreenController::replayLastGame()
{
    BoardController boardCtrl;
    
    boardCtrl.replayGame("game_history.txt");
}



