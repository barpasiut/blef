#include "mainmenu.h"
#include <QGraphicsProxyWidget>
MainMenu::MainMenu()
{
    // attributes settings
    start = new MainMenuButton();
    exit = new MainMenuButton();
    QGraphicsProxyWidget *proxyStart = this->addWidget(start);
    QGraphicsProxyWidget *proxyExit = this->addWidget(exit);
    proxyStart->setPos(5,5);
    proxyExit->setPos(10,10);
    this->addItem(proxyStart);
    this->addItem(proxyExit);

    // scene settings
    this->setSceneRect(0,0,400,400);
}

MainMenu::~MainMenu()
{
    delete start;
    delete exit;
}
