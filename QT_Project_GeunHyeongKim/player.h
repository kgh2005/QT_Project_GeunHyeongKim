#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <vector>

class Player {
public:
    Player(const QString& name, int level, int score);

    QString getName() const { return name; }
    int getLevel() const { return level; }
    int getScore() const { return score; }

    // Player 정보를 출력하는 함수
    void printInfo() const;

    // 파일에 저장하는 함수
    void saveToFile() const;

    // 파일에서 Player 정보를 불러오는 함수
    static std::vector<Player> loadFromFile();

    // 랭킹을 파일에 저장하는 함수
    static void saveRankingToFile(const std::vector<Player>& players);

    // 랭킹을 출력하는 함수
    static void printRanking(const std::vector<Player>& players);

private:
    QString name;
    int level;
    int score;
};

#endif // PLAYER_H
