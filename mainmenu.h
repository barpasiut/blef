#ifndef MAINMENU_H
#define MAINMENU_H
#include "QGraphicsScene"
#include "mainmenubutton.h"

class MainMenu : public QGraphicsScene
{
public:
    MainMenu();
    ~MainMenu();
private:
    MainMenuButton *start;
    MainMenuButton *exit;
};

#endif // MAINMENU_H
