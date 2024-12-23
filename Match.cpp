#include "Match.h"

Match::Match(const string& player1, const string& player2, const string& result, const string& dateTime) : player1(player1), player2(player2), result(result), dateTime(dateTime) {}

string Match::getPlayer1() const { return player1; }
string Match::getPlayer2() const { return player2; }
string Match::getResult() const { return result; }
string Match::getDateTime() const { return dateTime; }

