#ifndef CPUMIND_H
#define CPUMIND_H
#include <QString>
#include "card.h"
#include "listofpokerslayouts.h"

class CpuMind {
    static const int factorValue = 6;
    static const int factorThreeOfKind = 3;
    static const int factorFourOfKind = 4;
    static const int factorBlefTwoPairs = 14;
    static const int factorBlefFullOfHouse = 30;
    static const int minProbabilityThreeshold = 0.09;
public:
    CpuMind();
    ~CpuMind();
    bool isTwoPairs();
    bool isMaxLayoutPriUpperThanBlefPri(int);
    float probBlefPlayerBefore2(const QString &, const QList<QString> &, const QList<QString> &,int);
    float probKindOrColorLayoutsPlayerBefore(int nrCards, int playerSize, int croupSize, const QList<int> &countCardsNrOrColor);
    int priorityWithKind(int countMain, int countValue, int secondCountMain, int secondCountValue); // if 0 priotity from Cards, if 1 priority from Blef
    int priorityWithFlush(int CountMain, int countValue);
    int priorityWithStraight(const QList<int> &countCards);
    int priorityWithStraightFlush(int countMain, int countValue, const QList<int> &countCards);
    void setPriorityBlef(int blefMain, int blefValue);
    void setBlefValueString();
    int getPriorityCards(int countMainKind, int countValueKind, int secondCountMainKind , int secondCountValueKind, int countMainColor, int countValueColor, QList<int> &countCards);
    int getMaxValue(int,int,int,int);
    int getMaxBlefMainNr(int priority) const;
    int getMaxBlefValueNr(int priority) const;
    int getBlefMainNr();
    int getBlefValueNr();
    const QString & getBlefValueString() const;
    bool getCheck() const;
    unsigned long combination(unsigned int, unsigned int); // 1 is n, 2 is k
    float probKindLayoutsPlayerBefore(int blefMainNr, int blefValueNr, const QList<int> &countCardsNr);
    float probPokerLayoutsPlayerBefore(int nrCards, int playerSize, int croupSize);
    void inicjalizeHelpAttributes(const QString &blef, const QList<QString> &croup, const QList<QString> &player);
    void decisionFunction(const QString &blef, const QList<QString> &croup, const QList<QString> &player, int nrCards);
    void makeBlef();
    int getPriorityWithKind() const;
private:
    int blefMainNr;
    int blefValueNr;
    QString blefValueString;
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

#endif // CPUMIND_H
