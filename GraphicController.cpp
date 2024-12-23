#include "GraphicController.h"
#include<iostream>
#include<vector>

using namespace std;
GraphicController::GraphicController()
{
}

void GraphicController::drawBoard(vector<node> v)
{
    const int size = 10;
    cout << "    ";
    for (int j = 0; j < size; j++)
        cout << j << "   ";
    cout << endl;

    cout << "  ";
    for (int j = 0; j < size; j++)
        cout << "|---";
    cout << "|" << endl;

    for (int i = 0; i < size; i++)
    {
        cout << i << " ";
        for (int j = 0; j < size; j++)
        {
            bool filled = false;
            for (auto& n : v)
            {
                if (n.x == i && n.y == j)
                {
                    cout << "| " << (n.data == 1 ? 'X' : 'O') << " "; // In 'X' hoặc 'O'
                    filled = true;
                    break;
                }
            }
            if (!filled)
                cout << "|   ";
        }
        cout << "|" << endl;

        cout << "  ";
        for (int j = 0; j < size; j++)
            cout << "|---";
        cout << "|" << endl;
    }
}

