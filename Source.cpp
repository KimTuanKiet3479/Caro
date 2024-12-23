#include<iostream>
#include "GraphicController.h"
#include "ScreenController.h"
#include "BoardController.h"
using namespace std;
int main()
{
    
    ScreenController* screenController = ScreenController::getInstance();
    screenController->gotoScreen(SCREEN_ID::MAIN_MENU);
    return 0;
}

