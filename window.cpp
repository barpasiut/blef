#include "window.h"

Window::Window()
{
    game = new Game();

    this->setScene(game);
    this->setFixedSize(Game::width,Game::height);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setBackgroundBrush(QBrush(Qt::gray, Qt::SolidPattern));
}

Window::~Window()
{
    delete game;
}

Game *Window::getGame() const
{
    return game;
}
