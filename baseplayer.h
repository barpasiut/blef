#ifndef BASEPLAYER_H
#define BASEPLAYER_H

#include <QList>
#include "card.h"

class BasePlayer : public QList<Card *>
{
public:
    BasePlayer();
    ~BasePlayer();
    virtual void appendCard(Card *);
    virtual void appendCard(Card *c, int n);
    const QList<QString> & getPlayerCards() const;
    const QString & getBlefChoice() const;
    int getNrCards() const;
    int incrementNrCards();
    void setPlayerCards(const QString &, int); // int = 0 REPLACE ALL | int = 1 INSERT
    virtual void setBlefChoice(const QString &, int, const QString &s2 = 0, int i2= 0); // s1 = pbox choice , i = index of pbox, s2 = pvbox choice, i2 = index of pvbox
    virtual void setBlefChoice(const QString &);
private:
    QList<QString> playerCards;
    QString blefChoice;
    int nrCards;
};

#endif // BASEPLAYER_H
