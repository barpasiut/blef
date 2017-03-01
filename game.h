#ifndef GAME_H
#define GAME_H
#include <QGraphicsScene>
#include <QList>
#include <QApplication>

#include "croupier.h"
#include "player.h"
#include "cpu.h"
#include <QGraphicsTextItem>

class Game : public QGraphicsScene
{
    static const int numberOfCardsAtTheBeggining = 1;
    static const int numberOfCardsToEndGame = 6;
    static const int offsetNearSceneBorder = 10;
    static const int offsetBetweenPlayerCards = 15;
    static const int offsetBetweenCroupierCards = 2;
public:
    enum {width = 800,height = 600};
    Game();
    ~Game();
    static qreal scaleCardsFactor();
    void setPlayersCardPosition(int nrPlayer); // nrPlayer 1,2,3,4
    void setPlayersCardPosition();
    void setCroupierCardPosition();
    void setLabelsPosition();
    void setLabel1(const QString &);
    void setLabel2(const QString &);
    void setLabel3(const QString &);
    void setLabel4(const QString &);
    const Player & getPlayer1() const;
    Player & getPlayer1();
    const Cpu & getPlayer2() const;
    Cpu & getPlayer2();
    const Cpu & getPlayer3() const;
    Cpu & getPlayer3();
    const Cpu & getPlayer4() const;
    Cpu & getPlayer4();
    const Croupier & getCroupier() const;
    Croupier & getCroupier();
    QGraphicsTextItem * getLabel1();
    const QGraphicsTextItem * getLabel1() const;
    QGraphicsTextItem * getLabel2();
    const QGraphicsTextItem * getLabel2() const;
    QGraphicsTextItem * getLabel3();
    const QGraphicsTextItem * getLabel3() const;
    QGraphicsTextItem * getLabel4();
    const QGraphicsTextItem * getLabel4() const;  
    void lost(Player &p, int nrPlayer);
    void lost(Cpu &p, int nrPlayer);
    void startReshuffle();
private:
    Player player1;
    Cpu player2;
    Cpu player3;
    Cpu player4;
    Croupier croupier;
    QGraphicsTextItem * label1;
    QGraphicsTextItem * label2;
    QGraphicsTextItem * label3;
    QGraphicsTextItem * label4;
};

#endif // GAME_H
