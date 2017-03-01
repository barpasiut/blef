#ifndef Window_H
#define Window_H
#include <QGraphicsView>
#include "game.h"

class Window : public QGraphicsView
{
public:
    Window();
    ~Window();
    Game * getGame() const;
private:
    Game *game;
};

#endif // Window_H
