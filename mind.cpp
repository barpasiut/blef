#include "mind.h"
#include <QDebug>

Mind::Mind() : countCardsForPoker{} , maxCountCardsColor{} , maxCountCardsNr {}, secondMaxCountCardsNr {}, allCards(QList<QString> ()), allCardsNr (QList<int> ()), allCardsColor(QList<QString> ()), countCardsNr(QList<int> ()), countCardsColor(QList<int> ())
{
    blefMainNr = 0;
    blefValueNr = 0;
    priorityBlef = 0;
    priorityMaxCards = 0;
    maxCountCardsForPoker = 0;
    check = false;
}

Mind::~Mind()
{

}

int Mind::priorityWithKind(int countMain, int countValue, int secondCountMain, int secondCountValue)
{
    int priority = 0;
    if(countMain == 1)
        priority = countValue;
    else if(countMain == 2)
    {
        if(secondCountMain != 2)
            priority = 6 + countValue;
        else
        {
            int fHelp = 0;
            for(int i =0; i< 5; i++)
            {
                for(int j=0; j< 5-i; j++)
                {
                    if(i == secondCountValue &&  i+j+1 == countValue)
                        priority = 12 + fHelp + j;
                    if(j == 5-i-1)
                        fHelp += j+1;
                }
            }
        }
    }
    else if(countMain == 3)
    {
        if(secondCountMain >= 2)
            priority = 39 + countValue*5 + secondCountValue;
        else
            priority = 27 + countValue;
    }
    else if(countMain == 4)
    {
        priority = 69 + countValue;
    }
    return priority;
}


int Mind::priorityWithFlush(int countMain ,int countValue)
{
    int priority = 0;
    if(countMain == 5)
        priority = 35 + countValue;
    return priority;
}

int Mind::priorityWithStraight(const QList<int> &countCards)
{
    int priority = 0;
    for(int i=1; i< countCards.size() - 1; i++)
    {
        if(countCards[i] == 0)
            return priority;
    }
    if(countCards[0] != 0)
        priority =33;
    if(countCards[5] != 0)
        priority =34;
    return priority;
}

int Mind::priorityWithStraightFlush(int countMain, int countValue, const QList<int> &countCards)
{
    int priority = 0;
    int fHelp = 0;
    if(priorityWithFlush(countMain,countValue))
    {
        for(int i=0 ; i<5; i++)
        {
            if(countCardsForPoker[countValue][i] == 0)
                fHelp++;
        }
        if(fHelp == 5)
            priority = 73 + countValue;
        fHelp = 0;
        for(int i=1 ; i<6; i++)
        {
            if(countCardsForPoker[countValue][i] == 0)
                fHelp++;
        }
        if(fHelp == 5)
            priority = 77 + countValue;
    }
    return priority;
}

int Mind::getPriorityCards(int countMainKind, int countValueKind, int secondCountMainKind, int secondCountValueKind, int countMainColor, int countValueColor, QList<int> &countCards)
{
    int prioritySF = priorityWithStraightFlush(countMainColor,countValueColor,countCards);
    int priorityKind = priorityWithKind(countMainKind,countValueKind,secondCountMainKind,secondCountValueKind);
    int priorityFlush = priorityWithFlush(countMainColor,countValueColor);
    int priorityStraight = priorityWithStraight(countCards);
    int priorityCards = getMaxValue(prioritySF,priorityKind,priorityFlush,priorityStraight);
    return priorityCards;
}

int Mind::getMaxValue(int a, int b, int c, int d)
{
    int *p = new int(4);
    *p = a;
    *(p+1) = b;
    *(p+2) = c;
    *(p+3) = d;
    int max = 0;
    for(int i=0;i<4;i++)
    {
        if(p[i] > max)
            max = p[i];
    }
    return max;
}

void Mind::setPriorityBlef(int blefMain, int blefValue)
{
    if(blefMain == 0  || blefMain == 1)
        priorityBlef = blefMain * factorValue + blefValue;
    if(blefMain == 2)
        priorityBlef = blefMain * factorValue + blefValue;
    if(blefMain == 3)
        priorityBlef = (blefMain-1) * factorValue + factorBlefTwoPairs + blefValue;
    if(blefMain == 4)
        priorityBlef = (blefMain-1) * factorValue + factorBlefTwoPairs + 1;
    if(blefMain == 5)
        priorityBlef = (blefMain-2) * factorValue + factorBlefTwoPairs + 2;
    if(blefMain == 6)
        priorityBlef = (blefMain-3) * factorValue + factorBlefTwoPairs + 2 + blefValue;
    if(blefMain == 7)
        priorityBlef = (blefMain-4) * factorValue + factorBlefTwoPairs + 2 + 4 + blefValue;
    if(blefMain == 8)
        priorityBlef = (blefMain-5) * factorValue + factorBlefTwoPairs + 2 + 4 + factorBlefFullOfHouse + blefValue;
    if(blefMain == 9)
        priorityBlef = (blefMain-5) * factorValue + factorBlefTwoPairs + 2 + 3 + factorBlefFullOfHouse + blefValue;
    if(blefMain == 10)
        priorityBlef = (blefMain-6) * factorValue + factorBlefTwoPairs + 2 + 3 + factorBlefFullOfHouse + 4 + blefValue;
}



