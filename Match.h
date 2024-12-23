#pragma once
#ifndef MATCH_H
#define MATCH_H

#include <string>
using namespace std;
class Match 
{
private:
    string player1;
    string player2;
    string result;
    string dateTime;

public:
    Match(const string& player1, const string& player2, const string& result, const string& dateTime);

    // Getters
    string getPlayer1() const;
    string getPlayer2() const;
    string getResult() const;
    string getDateTime() const;
};

#endif

