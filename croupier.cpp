#include "croupier.h"

Croupier::Croupier()
{
    numberOfCroupierCards = 4;
    mind = new CroupierMind;
}

Croupier::~Croupier()
{
    delete mind;
}

void Croupier::setNumberOfCroupierCards()
{
    if(Card::numberOfCardsInDeck - Card::getUnUsedCards().size() > 13)
        numberOfCroupierCards = 3;
    else if(Card::numberOfCardsInDeck - Card::getUnUsedCards().size() > 18)
        numberOfCroupierCards = 2;
    else if(Card::numberOfCardsInDeck - Card::getUnUsedCards().size() > 20)
        numberOfCroupierCards = 1;
    else if(Card::numberOfCardsInDeck - Card::getUnUsedCards().size() > 22)
        numberOfCroupierCards = 0;
}

void Croupier::setCroupierCards(const QString &s,int i)
{
    if(i == 0)
    {
        croupierCards.clear();
        croupierCards.append(s);
    }
    else if(i == 1)
        croupierCards.append(s);
}

int Croupier::getNumberOfCroupierCards() const
{
    return numberOfCroupierCards;
}

const QList<QString> & Croupier::getCroupierCards() const
{
    return croupierCards;
}

CroupierMind &Croupier::getCroupierMind()
{
    return *mind;
}

const CroupierMind &Croupier::getCroupierMind() const
{
    return *mind;
}

void Croupier::appendCard(Card *c)
{
    this->append(c);
    setCroupierCards(c->getNumberAndColor(),1);
}

void Croupier::appendCard(Card *c, int n)
{
    this->append(c);
    setCroupierCards(c->getNumberAndColor(),n);
}
