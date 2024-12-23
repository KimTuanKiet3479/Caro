#include "MatchHistory.h"
#include <fstream>
#include <sstream>

void MatchHistory::saveMatch(const Match& match) 
{
    writeToFile(match);
}

vector<Match> MatchHistory::getMatchesBetween(const string& player1, const string& player2) const 
{
    vector<Match> allMatches = readFromFile();
    vector<Match> result;

    for (const auto& match : allMatches) 
    {
        if ((match.getPlayer1() == player1 && match.getPlayer2() == player2) ||
            (match.getPlayer1() == player2 && match.getPlayer2() == player1)) 
        {
            result.push_back(match);
        }
    }

    return result;
}

void MatchHistory::writeToFile(const Match& match) const 
{
    ofstream file(fileName, ios::app);
    if (file.is_open()) 
    {
        file << match.getPlayer1() << "," << match.getPlayer2() << ","
            << match.getResult() << "," << match.getDateTime() << "\n";
        file.close();
    }
}

vector<Match> MatchHistory::readFromFile() const 
{
    vector<Match> matches;
    ifstream file(fileName);

    if (file.is_open()) 
    {
        string line;
        while (getline(file, line)) 
        {
            istringstream iss(line);
            string p1, p2, result, dateTime;

            getline(iss, p1, ',');
            getline(iss, p2, ',');
            getline(iss, result, ',');
            getline(iss, dateTime);

            matches.emplace_back(p1, p2, result, dateTime);
        }
        file.close();
    }

    return matches;
}

