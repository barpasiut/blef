#include "game.h"
#include "time.h"
#include "stdlib.h"
#include <QDebug>

Game::Game()
{
    //scene settings
    this->setSceneRect(0,0,width,height);

    //attributes settings
    srand(time(NULL));

    label1 = new QGraphicsTextItem();
    this->addItem(label1);
    label2 = new QGraphicsTextItem();
    this->addItem(label2);
    label3 = new QGraphicsTextItem();
    this->addItem(label3);
    label4 = new QGraphicsTextItem();
    this->addItem(label4);

    for(int i=0;i<Game::numberOfCardsAtTheBeggining;i++)
    {
        player1.appendCard(new Card());
        player1.incrementNrCards();
        this->addItem(player1[i]);
        player2.appendCard(new Card());
        player2.incrementNrCards();
        this->addItem(player2[i]);
        player3.appendCard(new Card());
        player3.incrementNrCards();
        this->addItem(player3[i]);
        player4.appendCard(new Card());
        player4.incrementNrCards();
        this->addItem(player4[i]);
    }

    for(int i=0;i<croupier.getNumberOfCroupierCards();i++)
    {
        croupier.appendCard(new Card());
        addItem(croupier[i]);
    }

    setPlayersCardPosition();
    setCroupierCardPosition();
    setLabelsPosition();
}

Game::~Game()
{
    delete label4;
    delete label3;
    delete label2;
    delete label1;
}

qreal Game::scaleCardsFactor()
{
    return 0.15;
}

void Game::setPlayersCardPosition(int nrPlayer)
{
    switch(nrPlayer)
    {
    case 1:
        for(int i=0; i<player1.size();i++)
        {
            if(i == player1.size() - 1)
                player1[i]->setScaleCard(Game::scaleCardsFactor());
            player1[i]->setPos(Game::width/2 - player1[i]->getWidth()/2 + i*(Game::offsetBetweenPlayerCards/2),Game::height - Game::offsetNearSceneBorder - player1[i]->getHeight());
            for(int j=0; j<i; j++)
                player1[j]->setPos(player1[j]->x()- Game::offsetBetweenPlayerCards/2,player1[j]->y());
        }
    case 2:
        for(int i=0; i<player2.size();i++)
        {
            if(i == player2.size() - 1)
                player2[i]->setScaleCard(Game::scaleCardsFactor());
            player2[i]->setPos(Game::offsetNearSceneBorder,Game::height/2 - player2[i]->getHeight()/2 + i*(Game::offsetBetweenPlayerCards/2));
            for(int j=0; j<i; j++)
                player2[j]->setPos(player2[j]->x(),player2[j]->y() - Game::offsetBetweenPlayerCards/2);
        }
        break;
    case 3:
        for(int i=0; i<player3.size();i++)
        {
            if(i == player3.size() - 1)
                player3[i]->setScaleCard(Game::scaleCardsFactor());
            player3[i]->setPos(Game::width/2 - player3[i]->getWidth()/2 + i*(Game::offsetBetweenPlayerCards/2),Game::offsetNearSceneBorder);
            for(int j=0; j<i; j++)
                player3[j]->setPos(player3[j]->x()- Game::offsetBetweenPlayerCards/2,player3[j]->y());
        }
        break;
    case 4:
        for(int i=0; i<player4.size();i++)
        {
            if(i == player4.size() - 1)
                player4[i]->setScaleCard(Game::scaleCardsFactor());
            player4[i]->setPos(Game::width - player4[i]->getWidth() - Game::offsetNearSceneBorder,Game::height/2 - player4[i]->getHeight()/2 + i*(Game::offsetBetweenPlayerCards/2));
            for(int j=0; j<i; j++)
                player4[j]->setPos(player4[j]->x(),player4[j]->y() - Game::offsetBetweenPlayerCards/2);
        }
        break;
    default:
        break;
    }
}

void Game::setPlayersCardPosition()
{
    for(int i=0; i<player1.size();i++)
    {
        player1[i]->setScaleCard(Game::scaleCardsFactor());
        player1[i]->setPos(Game::width/2 - player1[i]->getWidth()/2 + i*(Game::offsetBetweenPlayerCards/2),Game::height - Game::offsetNearSceneBorder - player1[i]->getHeight());
        for(int j=0; j<i; j++)
            player1[j]->setPos(player1[j]->x()- Game::offsetBetweenPlayerCards/2,player1[j]->y());
    }

    for(int i=0; i<player2.size();i++)
    {
        player2[i]->setScaleCard(Game::scaleCardsFactor());
        player2[i]->setPos(Game::offsetNearSceneBorder,Game::height/2 - player2[i]->getHeight()/2 + i*(Game::offsetBetweenPlayerCards/2));
        for(int j=0; j<i; j++)
            player2[j]->setPos(player2[j]->x(),player2[j]->y() - Game::offsetBetweenPlayerCards/2);
    }

    for(int i=0; i<player3.size();i++)
    {
        player3[i]->setScaleCard(Game::scaleCardsFactor());
        player3[i]->setPos(Game::width/2 - player3[i]->getWidth()/2 + i*(Game::offsetBetweenPlayerCards/2),Game::offsetNearSceneBorder);
        for(int j=0; j<i; j++)
            player3[j]->setPos(player3[j]->x()- Game::offsetBetweenPlayerCards/2,player3[j]->y());
    }

    for(int i=0; i<player4.size();i++)
    {
        player4[i]->setScaleCard(Game::scaleCardsFactor());
        player4[i]->setPos(Game::width - player4[i]->getWidth() - Game::offsetNearSceneBorder,Game::height/2 - player4[i]->getHeight()/2 + i*(Game::offsetBetweenPlayerCards/2));
        for(int j=0; j<i; j++)
            player4[j]->setPos(player4[j]->x(),player4[j]->y() - Game::offsetBetweenPlayerCards/2);
    }
}

void Game::setCroupierCardPosition()
{
    for(int i=0; i<croupier.size();i++)
    {
        croupier[i]->setScaleCard(Game::scaleCardsFactor());
        croupier[i]->setPos(Game::width/2 + (i-1)*(croupier[i]->getWidth()/2) + i*Game::offsetBetweenCroupierCards/2,Game::height/2 - croupier[i]->getHeight()/2);
        for (int j=0; j<i; j++)
            croupier[j]->setPos(croupier[j]->x() - (croupier[j]->getWidth()/2 + Game::offsetBetweenPlayerCards/2), croupier[j]->y());
    }

}

void Game::setLabelsPosition()
{
    label1->setPos(width/2 - 20,height - 2 * offsetNearSceneBorder - player1[0]->getHeight() - 30);
    label2->setPos(2*offsetNearSceneBorder + player2[0]->getWidth(),height/2);
    label3->setPos(width/2,2 * offsetNearSceneBorder + player3[0]->getHeight() + 30);
    label4->setPos(width - 2*offsetNearSceneBorder - player4[0]->getWidth() - 130,height/2);
}

void Game::setLabel1(const QString &s)
{
    label1->setPlainText(s);
}

void Game::setLabel2(const QString &s)
{
    label2->setPlainText(s);
}

void Game::setLabel3(const QString &s)
{
    label3->setPlainText(s);
}

void Game::setLabel4(const QString &s)
{
    label4->setPlainText(s);
}

const Player &Game::getPlayer1() const
{
    return player1;
}

Player &Game::getPlayer1()
{
    return player1;
}

const Cpu &Game::getPlayer2() const
{
    return player2;
}

Cpu & Game::getPlayer2()
{
    return player2;
}

const Cpu & Game::getPlayer3() const
{
    return player3;
}

Cpu & Game::getPlayer3()
{
    return player3;
}

const Cpu & Game::getPlayer4() const
{
    return player4;
}

Cpu &Game::getPlayer4()
{
    return player4;
}

const Croupier &Game::getCroupier() const
{
    return croupier;
}

Croupier &Game::getCroupier()
{
    return croupier;
}

QGraphicsTextItem * Game::getLabel1()
{
    return label1;
}

const QGraphicsTextItem * Game::getLabel1() const
{
    return label1;
}

QGraphicsTextItem * Game::getLabel2()
{
    return label2;
}

const QGraphicsTextItem * Game::getLabel2() const
{
    return label2;
}

QGraphicsTextItem * Game::getLabel3()
{
    return label3;
}

const QGraphicsTextItem * Game::getLabel3() const
{
    return label3;
}

QGraphicsTextItem * Game::getLabel4()
{
    return label4;
}

const QGraphicsTextItem * Game::getLabel4() const
{
    return label4;
}

void Game::lost(Player &p, int nrPlayer)
{
    p.incrementNrCards();
}

void Game::lost(Cpu &p, int nrPlayer)
{
    p.incrementNrCards();
}

void Game::startReshuffle()
{
    player1[0]->setUnUsedCards(cardsList());
    player1.clear();
    player2.clear();
    player3.clear();
    player4.clear();
    croupier.clear();
    setLabel1(" ");
    setLabel2(" ");
    setLabel3(" ");
    setLabel4(" ");

    for(int i=0;i<player1.getNrCards();i++)
    {
        if(i == 0)
            player1.appendCard(new Card(),0);
        else
            player1.appendCard(new Card(),1);
        this->addItem(player1[i]);
    }
    for(int i=0;i<player2.getNrCards();i++)
    {
        if(i == 0)
            player2.appendCard(new Card(),0);
        else
            player2.appendCard(new Card(),1);
        this->addItem(player2[i]);
    }
    for(int i=0;i<player3.getNrCards();i++)
    {
        if(i == 0)
            player3.appendCard(new Card(),0);
        else
            player3.appendCard(new Card(),1);
        this->addItem(player3[i]);
    }
    for(int i=0;i<player4.getNrCards();i++)
    {
        if(i == 0)
            player4.appendCard(new Card(),0);
        else
            player4.appendCard(new Card(),1);
        this->addItem(player4[i]);
    }

    for(int i=0;i<croupier.getNumberOfCroupierCards();i++)
    {
        if(i == 0)
            croupier.appendCard(new Card(),0);
        else
            croupier.appendCard(new Card(),1);
        this->addItem(croupier[i]);
    }

    setPlayersCardPosition();
    setCroupierCardPosition();
}
