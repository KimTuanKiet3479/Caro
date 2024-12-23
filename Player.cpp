#include "Player.h"
#include <iostream>

Player::Player(const string& name, int wins, int losses, int draws) : name(name), wins(wins), losses(losses), draws(draws) {}

string Player::getName() const { return name; }
void Player::setName(const string& name) { this->name = name; }

int Player::getWins() const { return wins; }
void Player::setWins(int wins) { this->wins = wins; }

int Player::getLosses() const { return losses; }
void Player::setLosses(int losses) { this->losses = losses; }

int Player::getDraws() const { return draws; }
void Player::setDraws(int draws) { this->draws = draws; }

void Player::incrementWins() { wins++; }
void Player::incrementLosses() { losses++; }
void Player::incrementDraws() { draws++; }

//void Player::saveToFile(const string& filename) const
//{
//    ofstream outFile(filename, ios::app); // Mở file ở chế độ thêm
//    if (!outFile)
//    {
//        cerr << "Error: Could not open file " << filename << endl;
//        return;
//    }
//    outFile << name << "," << wins << "," << losses << "," << draws << endl;
//    outFile.close();
//}

//Player Player::loadFromFile(const string& filename)
//{
//    ifstream inFile(filename);
//    if (!inFile)
//    {
//        cerr << "Error: Could not open file " << filename << endl;
//        return Player("", 0, 0, 0); // Trả về một Player rỗng
//    }
//
//    string line;
//    getline(inFile, line); // Đọc dòng đầu tiên
//
//    // Phân tách dữ liệu
//    size_t pos1 = line.find(',');
//    size_t pos2 = line.find(',', pos1 + 1);
//    size_t pos3 = line.find(',', pos2 + 1);
//
//    string name = line.substr(0, pos1);
//    int wins = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
//    int losses = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
//    int draws = stoi(line.substr(pos3 + 1));
//
//    inFile.close();
//    return Player(name, wins, losses, draws);
//}

void Player::displayAllPlayers(const string& filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    cout << "Player List:\n";
    cout << "---------------------------------------------------------\n";
    cout << "| Name\t\t\t\t| Wins | Losses | Draws |\n";
    cout << "---------------------------------------------------------\n";

    string line;
    while (getline(inFile, line))
    {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        string name = line.substr(0, pos1);
        int wins = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        int losses = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        int draws = stoi(line.substr(pos3 + 1));

        cout << "| " << name << "  \t\t| " << wins << "    | " << losses << "      | " << draws << "     |\n";
    }
    cout << "---------------------------------------------------------\n";

    inFile.close();
}


void Player::updateOrAddPlayer(const Player& player, const string& filename)
{
    ifstream inFile(filename);
    vector<string> lines;
    bool found = false;

    if (inFile)
    {
        string line;
        while (getline(inFile, line))
        {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            string name = line.substr(0, pos1);
            int wins = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            int losses = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            int draws = stoi(line.substr(pos3 + 1));

            if (name == player.getName())
            {
                // Cộng dồn thông tin
                found = true;
                wins += player.getWins();
                losses += player.getLosses();
                draws += player.getDraws();

                // Thêm vào danh sách cập nhật
                lines.push_back(player.getName() + "," +
                    to_string(wins) + "," +
                    to_string(losses) + "," +
                    to_string(draws));
            }
            else
            {
                lines.push_back(line); // Giữ nguyên người chơi khác
            }
        }
        inFile.close();
    }

    if (!found)
    {
        // Thêm người chơi mới nếu không tìm thấy
        lines.push_back(player.getName() + "," +
            to_string(player.getWins()) + "," +
            to_string(player.getLosses()) + "," +
            to_string(player.getDraws()));
    }

    ofstream outFile(filename, ios::trunc); // Ghi đè file
    for (const string& line : lines)
    {
        outFile << line << endl;
    }
    outFile.close();
}

