#ifndef LISTOFPOKERSLAYOUTS_H
#define LISTOFPOKERSLAYOUTS_H

#include <QStringList>
#include <QList>

class ListOfPokersLayouts
{
public:
    ListOfPokersLayouts();
    ~ListOfPokersLayouts();
    QStringList mainLayout;
    QList<QStringList> mainLayoutValue;
    QStringList oneCard;
    QStringList onePair;
    QStringList twoPairs;
    QStringList threeOfAKind;
    QStringList flush;
    QStringList fullHouse;
    QStringList fourOfAKind;
    QStringList smallStraightFlush;
    QStringList bigStraightFlush;
};

#endif // LISTOFPOKERSLAYOUTS_H
