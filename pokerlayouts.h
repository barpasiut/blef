#ifndef POKERLAYOUTS_H
#define POKERLAYOUTS_H

#include <QStringList>

class MainPokerLayouts : public QStringList
{
public:
    MainPokerLayouts(const QString &, const QString &, const QString &, const QString &, const QString &, const QString &, const QString &, const QString &, const QString &, const QString &, const QString &);
    ~MainPokerLayouts();
};

class OneCard : public QStringList
{
public:
    OneCard(const QString &, const QString &, const QString &, const QString &, const QString &,const QString &);
    ~OneCard();
};

QStringList MainPokerLayouts;
QStringList OneCard;
QStringList OnePair;
QStringList TwoPairs;
QStringList ThreeOfAKind;
QStringList SmallStraight;
QStringList BigStraight;
QStringList Flush;
QStringList FullHouse;
QStringList FourOfKind;
QStringList StraightFlush;
QStringList RoyalFlush;

//MainPokerLayouts


#endif // POKERLAYOUTS_H
