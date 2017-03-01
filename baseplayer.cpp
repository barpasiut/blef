#include "baseplayer.h"

BasePlayer::BasePlayer()
{

}

BasePlayer::~BasePlayer()
{

}

void BasePlayer::appendCard(Card *c)
{
    this->append(c);
    setPlayerCards(c->getNumberAndColor(),1);
}

void BasePlayer::appendCard(Card *c, int n)
{
    this->append(c);
    setPlayerCards(c->getNumberAndColor(),n);
}

const QList<QString> & BasePlayer::getPlayerCards() const
{
    return playerCards;
}

const QString & BasePlayer::getBlefChoice() const
{
    return blefChoice;
}

int BasePlayer::getNrCards() const
{
    return nrCards;
}

int BasePlayer::incrementNrCards()
{
    nrCards++;
}

void BasePlayer::setPlayerCards(const QString &s,int i)
{
    if(i == 0)
    {
        playerCards.clear();
        playerCards.append(s);
    }
    else if(i == 1)
        playerCards.append(s);
}

void BasePlayer::setBlefChoice(const QString &s,int i,const QString &s2,int i2)
{
    blefChoice = s + "." + QString::number(i) + "." + s2 + "." + QString::number(i2);
}

void BasePlayer::setBlefChoice(const QString &b)
{
    blefChoice = b;
}

