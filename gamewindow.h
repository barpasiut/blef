#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QFormLayout>
#include "window.h"
#include "gamecontrol.h"

class GameWindow : public QWidget, public ListOfPokersLayouts
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    const QList<QString> & getPlayerCards(int) const; // int = 0 PLAYER1 | int = 1 PLAYER2 ...
    const QList<QString> & getCroupierCards() const;
    void delay(int);
    void checkGame(const QString &);
    void lost(Player &p, int nrPlayer);
    void lost(Cpu &p, int nrPlayer);
private:
    Window *w;
    QBoxLayout *game;
    GameControl *gameControl;
    QHBoxLayout *gameWindow;
signals:

public slots:
    void pressedBButton();
    void pressedCheckButton();
};

#endif // GAMEWINDOW_H
