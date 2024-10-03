#include "player.h"
#include <QFile>
#include <QTextStream>
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;

Player::Player(const QString& name, int level, int score)
    : name(name), level(level), score(score) {}

// 파일에서 Player 정보를 불러오는 함수
std::vector<Player> Player::loadFromFile() {
    std::vector<Player> players;
    QFile file("player_info.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() == 3) {
                QString name = fields[0];
                int level = fields[1].toInt();
                int score = fields[2].toInt();
                players.emplace_back(name, level, score);
            }
        }
        file.close();
    }

    return players;
}

// 랭킹을 파일에 저장하는 함수
void Player::saveRankingToFile(const std::vector<Player>& players) {
    QFile file("player_info.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto& player : players) {
            out << player.getName() << "," << player.getLevel() << "," << player.getScore() << "\n";
        }
        file.close();
    }
}

// 콘솔에 랭킹을 출력하는 함수
void Player::printRanking(const std::vector<Player>& players) {
    std::cout << "==== Ranking ====" << std::endl;
    for (const auto& player : players) {
        std::cout << "Player: " << player.getName().toStdString()
                  << ", Level: " << player.getLevel()
                  << ", Score: " << player.getScore() << std::endl;
    }
}
