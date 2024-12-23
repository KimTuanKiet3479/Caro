#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class Player 
{
private:
    string name;
    int wins;
    int losses;
    int draws;

public:
    Player(const string& name = "", int wins = 0, int losses = 0, int draws = 0);

    
    string getName() const;
    void setName(const string& name);

    int getWins() const;
    void setWins(int wins);

    int getLosses() const;
    void setLosses(int losses);

    int getDraws() const;
    void setDraws(int draws);

    void incrementWins();
    void incrementLosses();
    void incrementDraws();


    //void saveToFile(const string& filename) const;
    //static Player loadFromFile(const string& filename);
    static void displayAllPlayers(const string& filename);
    void updateOrAddPlayer(const Player& player, const string& filename);
};



