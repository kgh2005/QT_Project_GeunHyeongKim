#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <vector>

class Player {
private:
    QString name;
    int level;
    int score;
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
    static std::vector<Player> loadFile();

    // 랭킹을 파일에 저장하는 함수
    static void saveRankingFile(const std::vector<Player>& players);

    // 랭킹을 출력하는 함수
    static void printRanking(const std::vector<Player>& players);

    // 랭킹 정보를 문자열로 반환하는 함수
    QString getRankingString() const;  // 여기에 추가
};

#endif // PLAYER_H
