#ifndef MIND_H
#define MIND_H
#include <QString>
#include <QList>

class Mind
{
    static const int factorValue = 6;
    static const int factorThreeOfKind = 3;
    static const int factorFourOfKind = 4;
    static const int factorBlefTwoPairs = 14;
    static const int factorBlefFullOfHouse = 30;
public:
    Mind();
    ~Mind();
    int priorityWithKind(int countMain, int countValue, int secondCountMain, int secondCountValue); // if 0 priotity from Cards, if 1 priority from Blef
    int priorityWithFlush(int CountMain, int countValue);
    int priorityWithStraight(const QList<int> &countCards);
    int priorityWithStraightFlush(int countMain, int countValue, const QList<int> &countCards);
    int getPriorityCards(int countMainKind, int countValueKind, int secondCountMainKind , int secondCountValueKind, int countMainColor, int countValueColor, QList<int> &countCards);
    int getMaxValue(int,int,int,int);
    void setPriorityBlef(int blefMain, int blefValue);

protected:
    int blefMainNr;
    int blefValueNr;
    QList<QString> allCards;
    QList<int> allCardsNr;
    QList<QString> allCardsColor;
    QList<int> countCardsNr; // [0]-> 9, [1] -> 10 ...
    QList<int> countCardsColor; // [0]-> clubs, [1]-> diamonds, [2]-> hearts, [3]-> spades
    int countCardsForPoker[4][6];
    int priorityBlef;
    int priorityMaxCards;
    bool check;
    int maxCountCardsNr[2]; // [0] -> maxvalue, [1]-> value card of maxvalue
    int secondMaxCountCardsNr[2];
    int maxCountCardsColor[2]; // [0] -> maxvalue, [1]-> value card of maxvalue
    int maxCountCardsForPoker;
};

#endif // MIND_H
