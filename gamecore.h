#ifndef GAMECORE_H
#define GAMECORE_H

#include <QStringList>

class GameCore
{
    static const int nrOfPlayers = 4;
public:
    GameCore();
    ~GameCore();
    void playerTurn(const QStringList &, int, int, int); // 1 = List of blefed, 2 = index of blef pokerlayout , 3 = index of blef pokerlayout value, 4 = number of cards
private:
    static int turns = 0;
};

#endif // GAMECORE_H
