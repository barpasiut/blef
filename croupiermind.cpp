#include "croupiermind.h"

CroupierMind::CroupierMind()
{

}

CroupierMind::~CroupierMind()
{

}

void CroupierMind::initializeHelpAttributes(const QString &blef, const QList<QString> &allUsedCards)
{
    blefMainNr = blef.split(".")[1].toInt();
    blefValueNr = blef.split(".")[3].toInt();

    allCards.clear();
    allCardsNr.clear();
    allCardsColor.clear();
    countCardsNr.clear();
    countCardsColor.clear();
    check = 0;

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<6; j++)
            countCardsForPoker[i][j] = 0;
    }

    for(auto x: allUsedCards)
    {
        allCardsNr.append(x.split(".")[0].toInt());
        allCardsColor.append(x.split(".")[1]);
    }

    for(int i=9;i<15;i++)
        countCardsNr.append(allCardsNr.count(i));

    countCardsColor.append(allCardsColor.count("clubs"));
    countCardsColor.append(allCardsColor.count("hearts"));
    countCardsColor.append(allCardsColor.count("diamonds"));
    countCardsColor.append(allCardsColor.count("spades"));

    for(int i=0;i<allCards.size();i++)
    {
        if(allCardsColor[i] == "clubs")
            countCardsForPoker[0][allCardsNr[i] - 9] = 1;
        if(allCardsColor[i] == "diamonds")
            countCardsForPoker[1][allCardsNr[i] - 9] = 1;
        if(allCardsColor[i] == "hearts")
            countCardsForPoker[2][allCardsNr[i] - 9] = 1;
        if(allCardsColor[i] == "spades")
            countCardsForPoker[3][allCardsNr[i] - 9] = 1;
    }
}

bool CroupierMind::isPlayerCheckWin(const QString &blef, const QList<QString> &allUsedCards)
{
    initializeHelpAttributes(blef,allUsedCards);
    if(isAllCardsLayoutPriEqualToBlefPri())
        return false;
    else
        return true;

}

bool CroupierMind::isAllCardsLayoutPriEqualToBlefPri()
{
    if(blefMainNr == 0)
    {
        for(int i=0; i<allCardsNr.size(); i++)
        {
            if(allCardsNr[i] - 9 == blefValueNr)
                return true;
        }
    }
    if(blefMainNr == 1 || blefMainNr == 3 || blefMainNr == 8)
    {
        for(int i=0; i<countCardsNr.size(); i++)
        {
            if(i == blefValueNr && countCardsNr[i] >= 2 && blefMainNr == 1)
                return true;
            if(i == blefValueNr && countCardsNr[i] >= 3 && blefMainNr == 3)
                return true;
            if(i == blefValueNr && countCardsNr[i] == 4 && blefMainNr == 8)
                return true;
        }
    }
    if(blefMainNr == 2)
    {
        int fHelp = 0;
        for(int i =0; i< 5; i++)
        {
            for(int j=i; j< 6; j++)
            {
                if(fHelp == blefValueNr)
                {
                    if(countCardsNr[i] >= 2 && countCardsNr[j+1] >= 2)
                        return true;
                }
                fHelp++;
            }
        }
    }
    if(blefMainNr == 4 || blefMainNr == 5)
    {
        int fHelp = 0;
        for(int i=1; i< countCardsNr.size() -1; i++)
        {
            if(countCardsNr[i] == 0)
                fHelp = 1;
        }
        if(fHelp == 0)
        {
            if(countCardsNr[0] != 0 && blefMainNr == 4)
                return true;
            if(countCardsNr[5] != 0 && blefMainNr == 5)
                return true;
        }
    }
    if(blefMainNr == 6)
    {
        for(int i=0; i < countCardsColor.size(); i++)
        {
            if(i == blefValueNr && countCardsColor[i] >= 5)
                return true;
        }
    }
    if(blefMainNr == 7)
    {
        int fHelp = 0;
        for(int i =0; i< 6; i++)
        {
            for(int j=0; j< 5; j++)
            {   if(i!=j)
                {
                    if(fHelp == blefValueNr)
                    {

                        if(countCardsNr[i] >= 3 && countCardsNr[j] >= 2)
                            return true;
                    }
                    fHelp++;
                }
            }
        }
    }
    if(blefMainNr == 9 || blefMainNr == 10)
    {
        int fHelp = 0;
        if(countCardsForPoker[blefValueNr][0] == 1 && blefMainNr == 9)
        {
            for(int i=1;i<5;i++)
            {
                if(countCardsForPoker[blefValueNr][i] != 1)
                    fHelp = 1;
            }
            if(fHelp == 0)
                return true;
        }
        if(countCardsForPoker[blefValueNr][5] == 1 && blefMainNr == 10)
        {
            for(int i=1;i<5;i++)
            {
                if(countCardsForPoker[blefValueNr][i] != 1)
                    fHelp = 1;
            }
            if(fHelp == 0)
                return true;
        }
    }
    return false;
}

