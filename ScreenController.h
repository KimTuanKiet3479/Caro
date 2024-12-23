#pragma once
#include<iostream>
#include<stack>
#include"SafeInt.h"
using namespace std;

enum SCREEN_ID
{
	MAIN_MENU,
	PLAY_WITH_BOT,
	BOARD_PLAYER,
	PLAYER_RESULT,
	REPLAY_LASTGAME,
	MAX
};
enum Difficulty
{
	EASY = 2,
	NORMAL = 3,
	HARD = 4
};

class ScreenController
{
	Difficulty m_currentDifficulty;
	SCREEN_ID m_currentScreen;
	stack <SCREEN_ID> m_screenStack;
	ScreenController();
	static ScreenController* m_instance;
public:
	static ScreenController* getInstance();
	void gotoScreen(SCREEN_ID);
	void back();
	void home();
	void displayMainMenu();
	void startGameForTwoPlayers();
	void startGameWithBot();
	void startBotGame(Difficulty difficulty);

	void replayLastGame();
};

