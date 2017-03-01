#include "gamewindow.h"
#include <QDebug>
#include <limits>
#include <QTime>
#include <QMessageBox>


GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{
    srand(time(NULL));

    w = new Window();

    qDebug() << "heheh";
    game = new QBoxLayout(QBoxLayout::LeftToRight);
    game->addWidget(dynamic_cast<QWidget *>(w));

    qDebug() << "heheh";
    gameControl = new GameControl();
    qDebug() << "nono";
    gameWindow = new QHBoxLayout();
    gameWindow->addLayout(game);
    gameWindow->addLayout(gameControl);

    this->setLayout(gameWindow);

    connect(gameControl->getBButton(),SIGNAL(pressed()),this,SLOT(pressedBButton()));
    connect(gameControl->getCheckButton(),SIGNAL(pressed()),this,SLOT(pressedCheckButton()));

}

GameWindow::~GameWindow()
{
    delete gameWindow;
    delete gameControl;
    delete game;
    delete w;
}

const QList<QString> & GameWindow::getPlayerCards(int n) const
{
    if(n == 0)
        return w->getGame()->getPlayer1().getPlayerCards();
    else if (n == 1)
        return w->getGame()->getPlayer2().getPlayerCards();
    else if (n == 2)
        return w->getGame()->getPlayer3().getPlayerCards();
    else
        return w->getGame()->getPlayer4().getPlayerCards();
}

const QList<QString> & GameWindow::getCroupierCards() const
{
    return w->getGame()->getCroupier().getCroupierCards();
}

void GameWindow::pressedBButton()
{
    Game *handler;
    QMessageBox msg;

    handler = w->getGame();
    handler->getPlayer1().setBlefChoice(gameControl->getPBox()->currentText(),gameControl->getPBox()->currentIndex(),gameControl->getPVBox()->currentText(),gameControl->getPVBox()->currentIndex());
    handler->setLabel1(handler->getPlayer1().getBlefChoice());
    handler->getPlayer2().getCpuMind().decisionFunction(w->getGame()->getPlayer1().getBlefChoice(),w->getGame()->getCroupier().getCroupierCards(),w->getGame()->getPlayer2().getPlayerCards(),24 - handler->getPlayer2()[0]->getUnUsedCards().size());

    if(handler->getPlayer2().getCpuMind().getCheck() == true)
    {
        QList<QString> allCards;
        allCards.append(handler->getCroupier().getCroupierCards() + handler->getPlayer1().getPlayerCards() + handler->getPlayer2().getPlayerCards() + handler->getPlayer3().getPlayerCards() + handler->getPlayer4().getPlayerCards());
        if(handler->getCroupier().getCroupierMind().isPlayerCheckWin(handler->getPlayer1().getBlefChoice(),allCards))
        {
            handler->lost(handler->getPlayer1(),1);
            msg.setText("Wygrał gracz "+ QString::number(2));
        }
        else
        {
            handler->lost(handler->getPlayer2(),2);
            msg.setText("Wygrał gracz "+ QString::number(1));
        }
        msg.exec();
        handler->startReshuffle();
        return;
    }
    delay(3);
    handler->getPlayer2().setBlefChoice(handler->getPlayer2().getCpuMind().getBlefMainNr(),mainLayout[handler->getPlayer2().getCpuMind().getBlefMainNr()],handler->getPlayer2().getCpuMind().getBlefValueNr(),handler->getPlayer2().getCpuMind().getBlefValueString());
    handler->setLabel2(handler->getPlayer2().getBlefChoice());
    handler->getPlayer3().getCpuMind().decisionFunction(w->getGame()->getPlayer2().getBlefChoice(),w->getGame()->getCroupier().getCroupierCards(),w->getGame()->getPlayer3().getPlayerCards(),24 - handler->getPlayer3()[0]->getUnUsedCards().size());
    if(handler->getPlayer3().getCpuMind().getCheck() == true)
    {
        QList<QString> allCards;
        allCards.append(handler->getCroupier().getCroupierCards() + handler->getPlayer1().getPlayerCards() + handler->getPlayer2().getPlayerCards() + handler->getPlayer3().getPlayerCards() + handler->getPlayer4().getPlayerCards());
        if(handler->getCroupier().getCroupierMind().isPlayerCheckWin(handler->getPlayer2().getBlefChoice(),allCards))
        {
            handler->lost(handler->getPlayer2(),2);
            msg.setText("Wygrał gracz "+ QString::number(3));
        }
        else
        {
            handler->lost(handler->getPlayer3(),3);
            msg.setText("Wygrał gracz "+ QString::number(2));
        }
        msg.exec();
        handler->startReshuffle();
        return;
    }
    delay(3);
    handler->getPlayer3().setBlefChoice(handler->getPlayer3().getCpuMind().getBlefMainNr(),mainLayout[handler->getPlayer3().getCpuMind().getBlefMainNr()],handler->getPlayer3().getCpuMind().getBlefValueNr(),handler->getPlayer3().getCpuMind().getBlefValueString());
    handler->setLabel3(handler->getPlayer3().getBlefChoice());
    handler->getPlayer4().getCpuMind().decisionFunction(w->getGame()->getPlayer3().getBlefChoice(),w->getGame()->getCroupier().getCroupierCards(),w->getGame()->getPlayer4().getPlayerCards(),24 - handler->getPlayer4()[0]->getUnUsedCards().size());
    if(handler->getPlayer4().getCpuMind().getCheck() == true)
    {
        QList<QString> allCards;
        allCards.append(handler->getCroupier().getCroupierCards() + handler->getPlayer1().getPlayerCards() + handler->getPlayer2().getPlayerCards() + handler->getPlayer3().getPlayerCards() + handler->getPlayer4().getPlayerCards());
        if(handler->getCroupier().getCroupierMind().isPlayerCheckWin(handler->getPlayer3().getBlefChoice(),allCards))
        {
            handler->lost(handler->getPlayer3(),3);
            msg.setText("Wygrał gracz "+ QString::number(4));
        }
        else
        {
            handler->lost(handler->getPlayer4(),4);
            msg.setText("Wygrał gracz "+ QString::number(3));
        }
        msg.exec();
        handler->startReshuffle();
        return;
    }
    delay(3);
    handler->getPlayer4().setBlefChoice(handler->getPlayer4().getCpuMind().getBlefMainNr(),mainLayout[handler->getPlayer4().getCpuMind().getBlefMainNr()],handler->getPlayer4().getCpuMind().getBlefValueNr(),handler->getPlayer4().getCpuMind().getBlefValueString());
    handler->setLabel4(handler->getPlayer4().getBlefChoice());
    return;

}

void GameWindow::pressedCheckButton()
{
    QMessageBox msg;
    Game *handler = w->getGame();
    QList<QString> allCards;
    allCards.append(handler->getCroupier().getCroupierCards() + handler->getPlayer1().getPlayerCards() + handler->getPlayer2().getPlayerCards() + handler->getPlayer3().getPlayerCards() + handler->getPlayer4().getPlayerCards());
    if(handler->getCroupier().getCroupierMind().isPlayerCheckWin(handler->getPlayer4().getBlefChoice(),allCards))
    {
        handler->lost(handler->getPlayer4(),4);
        msg.setText("Wygrał gracz "+ QString::number(1));
    }
    else
    {
        handler->lost(handler->getPlayer1(),1);
        msg.setText("Wygrał gracz "+ QString::number(4));
    }
    msg.exec();
    handler->startReshuffle();
    return;
}

void GameWindow::delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void GameWindow::checkGame(const QString &blef)
{
    Game *handler;
    handler = w->getGame();

}

