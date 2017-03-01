#ifndef CROUPIER_H
#define CROUPIER_H

#include "card.h"
#include "croupiermind.h"

class Croupier : public QList<Card *>
{
public:
    Croupier();
    ~Croupier();
    void setNumberOfCroupierCards();
    void setCroupierCards(const QString &,int ); // int = 0 REPLACE ALL | int = 1 INSERT
    int getNumberOfCroupierCards() const;
    const QList<QString> & getCroupierCards() const;
    CroupierMind & getCroupierMind();
    const CroupierMind &getCroupierMind() const;
    void appendCard(Card *);
    void appendCard(Card *, int);
private:
    int numberOfCroupierCards;
    QList<QString> croupierCards;
    CroupierMind *mind;
};

#endif // CROUPIER_H
