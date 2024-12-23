#pragma once


#include "Match.h"
#include <vector>
#include <string>
using namespace std;
class MatchHistory 
{
public:
    void saveMatch(const Match& match);
    vector<Match> getMatchesBetween(const string& player1, const string& player2) const;

private:
    const string fileName = "match_history.txt";
    void writeToFile(const Match& match) const;
    vector<Match> readFromFile() const;
};




