#include "cpumind.h"
#include "vector"
#include <QDebug>
#include <QtAlgorithms>

using namespace std;

CpuMind::CpuMind() : countCardsForPoker{} , maxCountCardsColor{} , maxCountCardsNr {}, secondMaxCountCardsNr {}, allCards(QList<QString> ()), allCardsNr (QList<int> ()), allCardsColor(QList<QString> ()), countCardsNr(QList<int> ()), countCardsColor(QList<int> ())
{
    blefMainNr = 0;
    blefValueNr = 0;
    priorityBlef = 0;
    priorityMaxCards = 0;
    maxCountCardsForPoker = 0;
    check = false;
}

CpuMind::~CpuMind()
{

}

void CpuMind::inicjalizeHelpAttributes(const QString &blef, const QList<QString> &croup, const QList<QString> &player)
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

    allCards.append(croup + player);
    for(auto x: allCards)
    {
        allCardsNr.append(x.split(".")[0].toInt());
        allCardsColor.append(x.split(".")[1]);
    }

    for(int i=9;i<15;i++)
        countCardsNr.append(allCardsNr.count(i));

    countCardsColor.append(allCardsColor.count("clubs"));
    countCardsColor.append(allCardsColor.count("diamonds"));
    countCardsColor.append(allCardsColor.count("hearts"));
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

void CpuMind::decisionFunction(const QString &blef, const QList<QString> &croup, const QList<QString> &player, int nrCards)
{
    inicjalizeHelpAttributes(blef,croup,player);
    float probBlef = probBlefPlayerBefore2(blef,croup,player,nrCards);
    qDebug() << probBlef;
    if(probBlef < 0.09)
        check = true;
    else if(isMaxLayoutPriUpperThanBlefPri(nrCards))
    {
        blefMainNr = getMaxBlefMainNr(priorityMaxCards);
        blefValueNr = getMaxBlefValueNr(priorityMaxCards);
        setBlefValueString();
    }
    else
    {
        makeBlef();
        setBlefValueString();
    }
    qDebug () << blefMainNr << "main" << blefValueNr << "value";
    qDebug() << probBlef;

}

void CpuMind::makeBlef()
{
    bool breakV = false;
    int iterat = 1;
    int loop = 4;
    int firstBlefValueNr = blefValueNr;
    int hBlefMainNr = blefMainNr;
    while(loop)
    {
        qDebug() << "break: " << breakV ;
        if(breakV)
            break;
        qDebug() << "blefNr: " << blefMainNr ;
        for(int i=blefMainNr; i<11; i++)
        {
            if(breakV)
                break;
            qDebug() << "blef: " << i ;
            if(i == 0 || i == 1 || i == 3 || i == 8)
            {
                if(hBlefMainNr !=i)
                    blefValueNr = 0;
                else
                    blefValueNr = firstBlefValueNr;
                qDebug() << "i:" << i;
                for(int j=blefValueNr + 1; j<6; j++)
                {
                    if(breakV)
                        break;
                    qDebug() << "j:" << j;
                    if((i == 0 && countCardsNr[j] > 0) || (i == 1 && countCardsNr[j] > 1-iterat) || (i == 3 && countCardsNr[j] > 2-iterat) || (i == 8 && countCardsNr[j] > 3-iterat))
                    {
                        blefMainNr = i;
                        blefValueNr = j;
                        breakV = true;
                    }
                }
            }
            else if(i == 2)
            {
                if(hBlefMainNr !=i)
                    blefValueNr = 0;
                else
                    blefValueNr = firstBlefValueNr;
                for(int j=blefValueNr +1;j<15;j++)
                {
                    if(breakV)
                        break;
                    qDebug() << "j:" << j;
                    int nrSecondL = j;
                    int k = 5;
                    int nrFirstL = 0;
                    while(nrSecondL/k != 0)
                    {
                        nrFirstL++;
                        nrSecondL = nrSecondL - k;
                        k--;
                    }
                    if(countCardsNr[nrFirstL] >= 2-iterat && countCardsNr[nrSecondL + nrFirstL + 1] >= 2)
                    {
                        blefMainNr = i;
                        blefValueNr = j;
                        breakV = true;
                    }
                }
            }
            else if(i == 7)
            {
                if(hBlefMainNr !=i)
                    blefValueNr = 0;
                else
                    blefValueNr = firstBlefValueNr;
                for(int j=blefValueNr +1;j<30;j++)
                {
                    if(breakV)
                        break;
                    qDebug() << "j:" << j;
                    int nrSecondL = 0;
                    int nrFirstL = j/5;
                    if(nrFirstL > j%5)
                        nrSecondL = j%5;
                    else
                        nrSecondL = j%5 +1;
                    if(countCardsNr[nrFirstL] >= 3-iterat && countCardsNr[nrSecondL] >= 2)
                    {
                        blefMainNr = i;
                        blefValueNr = j;
                        breakV = true;
                    }
                }
            }
            else if(i == 4)
            {
                if(hBlefMainNr !=i)
                    blefValueNr = 0;
                else
                    blefValueNr = firstBlefValueNr;
                if(breakV)
                    break;
                bool isAce = false;
                bool isNine = false;
                if(countCardsNr[0] != 0)
                    isNine = true;
                if(countCardsNr[5] != 0)
                    isAce = true;
                int count = 0;
                for(int j=0;j<countCardsNr.size();j++)
                {
                    if(countCardsNr[j] != 0)
                    count++;
                }
                if(count == 6-iterat-1 || (count == 5 && isAce && !isNine))
                {
                    blefMainNr = i+1;
                    breakV = true;
                }
            }
            else if(i == 5 || i == 6)
            {
                if(hBlefMainNr !=i)
                    blefValueNr = 0;
                else
                    blefValueNr = firstBlefValueNr;
                for(int j=blefValueNr +1;j<4;j++)
                {
                    if(breakV)
                        break;
                    qDebug() << "j:" << j;
                    if(countCardsColor[j] >= 5-iterat)
                    {
                        if(i == 5)
                            blefMainNr = i+1;
                        else
                            blefMainNr = i;
                        blefValueNr = j;
                        breakV = true;
                    }
                }
            }
            else if(i == 9 || i ==10)
            {
                if(hBlefMainNr !=i)
                    blefValueNr = 0;
                else
                    blefValueNr = firstBlefValueNr;
                bool isAce = false;
                if(countCardsNr[5] != 0)
                    isAce = true;
                bool isNine = false;
                if(countCardsNr[0] != 0)
                    isNine = true;

                int count = 0;
                for(int j=blefValueNr +1;j<4;j++)
                {
                    if(breakV)
                        break;
                    qDebug() << "j:" << j;
                    count = 0;
                    for(int k=0; k<6; k++)
                    {
                        if(countCardsForPoker[j][k] != 0)
                        {
                            count++;
                        }
                    }
                    if(count == 6-iterat || (count == 5-iterat && isNine && !isAce && i == 9) || (count == 5-iterat && isAce && !isNine && i == 10))
                    {
                        blefMainNr = i;
                        blefValueNr = j;
                        breakV = true;
                    }
                }

            }
        }
        loop--;
        iterat++;
    }
}

bool CpuMind::isMaxLayoutPriUpperThanBlefPri(int nrCards)
{
    if(maxCountCardsNr[0] != 0)
    {
        maxCountCardsNr[0] = 0;
        maxCountCardsNr[1] = 0;
    }

    if(secondMaxCountCardsNr[0] != 0)
    {
        secondMaxCountCardsNr[0] = 0;
        secondMaxCountCardsNr[1] = 0;
    }

    if(maxCountCardsColor[0] != 0)
    {
        maxCountCardsColor[0] = 0;
        maxCountCardsColor[1] = 0;
    }

    for(int i =0; i<countCardsNr.size();i++)
    {
        if(countCardsNr[i] >= maxCountCardsNr[0])
        {
            maxCountCardsNr[0] = countCardsNr[i];
            maxCountCardsNr[1] = i;
        }
    }

    for(int i =0; i<countCardsNr.size();i++)
    {
        if(countCardsNr[i] >= secondMaxCountCardsNr[0] && i != maxCountCardsNr[1])
        {
            secondMaxCountCardsNr[0] = countCardsNr[i];
            secondMaxCountCardsNr[1] = i;
        }
    }

    for(int i=0; i<countCardsColor.size();i++)
    {
        if(countCardsColor[i] >= maxCountCardsColor[0])
        {
            maxCountCardsColor[0] = countCardsColor[i];
            maxCountCardsColor[1] = i;
        }
    }

    qDebug() << "maxCountCardsNr[0]" << maxCountCardsNr[0] << "maxCountCardsNr[1]" << maxCountCardsNr[1];
    qDebug() << "secondmaxCountCardsNr[0]" << secondMaxCountCardsNr[0] << "secondmaxCountCardsNr[1]" << secondMaxCountCardsNr[1];
    qDebug() << "maxCountCardsColor[0]" << maxCountCardsColor[0] << "maxCountCardsColor[1]" << maxCountCardsColor[1];
    setPriorityBlef(blefMainNr, blefValueNr);
    priorityMaxCards = getPriorityCards(maxCountCardsNr[0],maxCountCardsNr[1],secondMaxCountCardsNr[0],secondMaxCountCardsNr[1],maxCountCardsColor[0],maxCountCardsColor[1],countCardsNr);
    qDebug() << "priorityBlef" << priorityBlef;
    qDebug() << "priorityMaxCards" << priorityMaxCards;
    if(priorityMaxCards > priorityBlef)
        return true;
    else
        return false;

}

float CpuMind::probBlefPlayerBefore2(const QString &blef, const QList<QString> &croup, const QList<QString> &player, int nrCards)
{
    float probability;
    if((blefMainNr >=0 && blefMainNr <= 5) || blefMainNr == 7 || blefMainNr == 8)
        probability = probKindOrColorLayoutsPlayerBefore(nrCards, player.size(), croup.size(), countCardsNr);
    else if(blefMainNr == 6)
        probability = probKindOrColorLayoutsPlayerBefore(nrCards, player.size(), croup.size(), countCardsColor);
    else if(blefMainNr == 9 || blefMainNr == 10)
        probability = probPokerLayoutsPlayerBefore(nrCards, player.size(), croup.size());
    return probability;
}

float CpuMind::probPokerLayoutsPlayerBefore(int nrCards, int playerSize, int croupSize)
{
    float probability = 0;
    int nrOfCardsKind = 0;
    int omega = combination(24 - playerSize - croupSize,nrCards - playerSize - croupSize);
    if(blefMainNr == 9 || blefMainNr == 10)
    {
        bool isAce = false;
        bool isNine = false;
        if(countCardsForPoker[blefValueNr][0] != 0)
            isNine = true;
        if(countCardsForPoker[blefValueNr][5] != 0)
            isAce = true;
        for(int j =0; j< 6; j++)
        {
            if(countCardsForPoker[blefValueNr][j] != 0)
                nrOfCardsKind++;
        }

        if(nrOfCardsKind == 6)
            probability = 1;
        else if(nrOfCardsKind == 5 && isAce == true && isNine == false && blefMainNr == 10)
            probability = 1;
        else if(nrOfCardsKind == 5 && isAce == false && isNine == true && blefMainNr == 9)
            probability = 1;
        else if(nrOfCardsKind == 5 && isAce == false && blefMainNr == 10 || (nrOfCardsKind == 5 && isNine == false && blefMainNr == 9) || (nrOfCardsKind == 5 && isNine == true && isAce == true) || (nrOfCardsKind == 4 && isAce == false && isNine == false) || (nrOfCardsKind == 4 && isAce == true && isNine == false && blefMainNr == 10 ) || (nrOfCardsKind == 4 && isNine == true && isAce == false && blefMainNr == 9))
        {
            int alfa = combination(24 - playerSize - croupSize - 1,nrCards - playerSize - croupSize - 1);
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 4 && isAce == false && isNine == true && blefMainNr == 10 || (nrOfCardsKind == 4 && isNine == false && isAce == true && blefMainNr == 9) || (nrOfCardsKind == 4 && isAce == true && isNine == true) || (nrOfCardsKind == 3 && isAce == false && isNine == false) || (nrOfCardsKind == 3 && isAce == true && isNine == false && blefMainNr == 10) || (nrOfCardsKind == 3 && isAce == false && isNine == true && blefMainNr == 9))
        {
            int alfa = combination(24 - playerSize - croupSize - 2,nrCards - playerSize - croupSize - 2);
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 3 && isAce == true && isNine == true || (nrOfCardsKind == 3 && isAce == true && isNine == false && blefMainNr == 9) || (nrOfCardsKind == 4 && isAce == false && isNine == true && blefMainNr == 10) || (nrOfCardsKind == 2 && isAce == false && isNine == false) || (nrOfCardsKind == 2 && isAce == false && isNine == true && blefMainNr == 9) || (nrOfCardsKind == 2 && isAce == true && isNine == false && blefMainNr == 10))
        {
            int alfa = combination(24 - playerSize - croupSize - 3,nrCards - playerSize - croupSize - 3);
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 2 && isAce == true && isNine == true || (nrOfCardsKind == 2 && isAce == false && isNine == true && blefMainNr == 10) || (nrOfCardsKind == 2 && isAce == true && isNine == false && blefMainNr == 9) || (nrOfCardsKind == 1 && isNine == true && blefMainNr == 9) || (nrOfCardsKind == 1 && isAce == true && blefMainNr == 10))
        {
            int alfa = combination(24 - playerSize - croupSize - 4,nrCards - playerSize - croupSize - 4);
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 1 && isAce == true && blefMainNr == 9 || (nrOfCardsKind == 0) || (nrOfCardsKind == 1 && isNine == true && blefMainNr == 10))
        {
            int alfa = combination(24 - playerSize - croupSize - 5,nrCards - playerSize - croupSize - 5);
            probability = float(alfa)/omega;
        }

    }

    return probability;

}

float CpuMind::probKindOrColorLayoutsPlayerBefore(int nrCards, int playerSize, int croupSize, const QList<int> & countCardsNrOrColor)
{
    float probability = 0;
    int nrOfCardsKind = 0;
    int omega = combination(24 - playerSize - croupSize,nrCards - playerSize - croupSize);
    if(blefMainNr == 0 || blefMainNr == 1 || blefMainNr == 3 || blefMainNr == 6 || blefMainNr == 8)
    {
        for(int i=0; i < countCardsNrOrColor.size(); i++)
        {
            if(blefValueNr == i)
                nrOfCardsKind = countCardsNrOrColor[i];
        }
        if(nrOfCardsKind >= blefMainNr + 1 && (blefMainNr == 0 || blefMainNr ==1))
            probability = 1;
        else if(nrOfCardsKind >= blefMainNr && blefMainNr == 3)
            probability = 1;
        else if(nrOfCardsKind == 4 && blefMainNr == 8)
            probability = 1;
        else if(nrOfCardsKind == 5 && blefMainNr == 6)
            probability = 1;
        else if(blefMainNr == 0 || (blefMainNr == 1 && nrOfCardsKind == 1) || (blefMainNr == 3 && nrOfCardsKind == 2) || (blefMainNr == 8 && nrOfCardsKind == 3))
        {
            int alfa = 0;
            for(int i=0; i<(4-nrOfCardsKind);i++)
                alfa += combination(4-nrOfCardsKind,i+1) * combination(24 - playerSize - croupSize - 4 + nrOfCardsKind ,nrCards - playerSize - croupSize - (i+1));
            probability = float(alfa)/omega;
        }
        else if(blefMainNr == 1 && nrOfCardsKind == 0 || (blefMainNr == 3 && nrOfCardsKind == 1) || (blefMainNr == 8 && nrOfCardsKind == 2))
        {
            int alfa = 0;
            for(int i=0; i<(4-nrOfCardsKind-1);i++)
                alfa += combination(4-nrOfCardsKind,i+2) * combination(24 - playerSize - croupSize - 4 + nrOfCardsKind,nrCards - playerSize - croupSize - (i+2));
            probability = float(alfa)/omega;
        }
        else if(blefMainNr == 3 && nrOfCardsKind == 0 || (blefMainNr == 8 && nrOfCardsKind == 1))
        {
            int alfa = 0;
            for(int i=0; i<(4-nrOfCardsKind-2);i++)
                alfa += combination(4-nrOfCardsKind,i+3) * combination(24 - playerSize - croupSize - 4 + nrOfCardsKind,nrCards - playerSize - croupSize - (i+3));
            probability = float(alfa)/omega;
        }
        else if(blefMainNr == 8 && nrOfCardsKind == 0)
        {
            int alfa = combination(4,4) * combination(24 - playerSize - croupSize - 4 + nrOfCardsKind,nrCards - playerSize - croupSize - 4);
            probability = float(alfa)/omega;
        }
        else if(blefMainNr == 6 && nrOfCardsKind == 4)
        {
            int alfa = 0;
            for(int i=0; i<(6-nrOfCardsKind);i++)
                alfa += combination(6-nrOfCardsKind,i+1) * combination(24 - playerSize - croupSize - 6 + nrOfCardsKind,nrCards - playerSize - croupSize - (i+1));
            probability = float(alfa)/omega;
        }
        else if(blefMainNr == 6 && nrOfCardsKind == 3)
        {
            int alfa = 0;
            for(int i=1; i<(6-nrOfCardsKind);i++)
                alfa += combination(6-nrOfCardsKind,i+1) * combination(24 - playerSize - croupSize - 6 + nrOfCardsKind,nrCards - playerSize - croupSize - (i+1));
            probability = float(alfa)/omega;
        }
        else if(blefMainNr == 6 && nrOfCardsKind == 2)
        {
            int alfa = 0;
            for(int i=2; i<(6-nrOfCardsKind);i++)
                alfa += combination(6-nrOfCardsKind,i+1) * combination(24 - playerSize - croupSize - 6 + nrOfCardsKind,nrCards - playerSize - croupSize - (i+1));
            probability = float(alfa)/omega;
        }
        else if(blefMainNr == 6 && nrOfCardsKind == 1)
        {
            int alfa = 0;
            for(int i=3; i<(6-nrOfCardsKind);i++)
                alfa += combination(6-nrOfCardsKind,i+1) * combination(24 - playerSize - croupSize - 6 + nrOfCardsKind,nrCards - playerSize - croupSize - (i+1));
            probability = float(alfa)/omega;
        }
        else if(blefMainNr == 6 && nrOfCardsKind == 0)
        {
            int alfa = 0;
            for(int i=4; i<(6-nrOfCardsKind);i++)
                alfa += combination(6-nrOfCardsKind,i+1) * combination(24 - playerSize - croupSize - 6 + nrOfCardsKind,nrCards - playerSize - croupSize - (i+1));
            probability = float(alfa)/omega;
        }
    }
    else if(blefMainNr == 2 || blefMainNr == 7)
    {
        int factor = 1;
        int factor2 = 0;
        int nrOfCardsKind2 = 0;
        if(blefMainNr == 2)
        {
            for(int i=0; i<6; i++)
            {
                for(int j=factor; j< 6; j++)
                {
                    if(blefValueNr == factor2)
                    {
                        nrOfCardsKind = countCardsNrOrColor[i];
                        nrOfCardsKind2 = countCardsNrOrColor[j];
                    }
                    factor2++;
                }
                factor++;
            }
        }
        else if(blefMainNr == 7)
        {
            for(int i=0; i<6; i++)
            {
                if(blefValueNr / 5 == i)
                {
                    nrOfCardsKind = countCardsNrOrColor[i];
                    for(int j=0; j< 5; j++)
                    {
                        if(j >= i && blefValueNr % 5 == j)
                            nrOfCardsKind2 = countCardsNrOrColor[j+1];
                        else if(j < i && blefValueNr % 5 == j)
                            nrOfCardsKind2 = countCardsNrOrColor[j];
                    }
                }
            }
        }

        if(nrOfCardsKind >= 3 && nrOfCardsKind2 >=2)
        {
            probability = 1;
        }
        else if(nrOfCardsKind == 2 && nrOfCardsKind2 >=2 && blefMainNr == 2)
        {
            probability = 1;
        }
        else if(nrOfCardsKind ==2 && nrOfCardsKind2 >=2 && blefMainNr == 7 || (nrOfCardsKind == 1 && nrOfCardsKind2 >= 2 && blefMainNr == 2))
        {
            int alfa = 0;
            for(int i=0; i<(4-nrOfCardsKind);i++)
                alfa += combination(4-nrOfCardsKind,i+1) * combination(24 - playerSize - croupSize - 4 + nrOfCardsKind,nrCards - playerSize - croupSize - (i+1));
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind >=2 && nrOfCardsKind2 == 1 && blefMainNr == 2 || (nrOfCardsKind >=3 && nrOfCardsKind2 == 1 && blefValueNr == 3))
        {
            int alfa = 0;
            for(int i=0; i<(4-nrOfCardsKind2);i++)
                alfa += combination(4-nrOfCardsKind2,i+1) * combination(24 - playerSize - croupSize - 4 + nrOfCardsKind2,nrCards - playerSize - croupSize - (i+1));
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 1 && nrOfCardsKind2 >=2 && blefMainNr == 7 || (nrOfCardsKind == 0 && nrOfCardsKind2 >=2 && blefMainNr == 2))
        {
            int alfa = 0;
            for(int i=1; i<(4-nrOfCardsKind);i++)
                alfa += combination(4-nrOfCardsKind,i+1) * combination(24 - playerSize - croupSize - 4 + nrOfCardsKind,nrCards - playerSize - croupSize - (i+1));
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind >= 3 && nrOfCardsKind2 == 0 && blefMainNr == 7 || (nrOfCardsKind >= 2 && nrOfCardsKind2 == 0 && blefMainNr == 2))
        {
            int alfa = 0;
            for(int i=1; i<(4-nrOfCardsKind2);i++)
                alfa += combination(4-nrOfCardsKind2,i+1) * combination(24 - playerSize - croupSize - 4 + nrOfCardsKind2,nrCards - playerSize - croupSize - (i+1));
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 2 && nrOfCardsKind2 == 1 && blefMainNr == 7)
        {
            int alfa = 0;
            for(int i=0; i<(4-nrOfCardsKind); i++)
            {
                for(int j=0; j<(4-nrOfCardsKind2);j++)
                    alfa += combination(4-nrOfCardsKind,i+1) * combination(4-nrOfCardsKind2,j+1) * combination(24 - playerSize - croupSize - (4-nrOfCardsKind + (4-nrOfCardsKind2)) + nrOfCardsKind2,nrCards - playerSize - croupSize - (j+2+i));

            }
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 1 && nrOfCardsKind == 1 && blefMainNr == 2)
        {
            int alfa = 0;
            for(int i=0; i<(4-nrOfCardsKind); i++)
            {
                for(int j=0; j<(4-nrOfCardsKind2);j++)
                    alfa += combination(4-nrOfCardsKind,i+1) * combination(4-nrOfCardsKind2,j+1) * combination(24 - playerSize - croupSize - (4-nrOfCardsKind + (4-nrOfCardsKind2)) + nrOfCardsKind2,nrCards - playerSize - croupSize - (j+2+i));

            }
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 0 && nrOfCardsKind2 >= 2 && blefMainNr == 7)
        {
            int alfa = 0;
            for(int i=2; i<(4-nrOfCardsKind);i++)
                alfa += combination(4-nrOfCardsKind,i+1) * combination(24 - playerSize - croupSize - 4 + nrOfCardsKind,nrCards - playerSize - croupSize - (i+1));
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 2 && nrOfCardsKind2 == 0 && blefMainNr == 7)
        {
            int alfa = 0;
            for(int i=0; i<(4-nrOfCardsKind); i++)
            {
                for(int j=1; j<(4-nrOfCardsKind2);j++)
                    alfa += combination(4-nrOfCardsKind,i+1) * combination(4-nrOfCardsKind2,j+1) * combination(24 - playerSize - croupSize - (4-nrOfCardsKind + (4-nrOfCardsKind2)) + nrOfCardsKind2,nrCards - playerSize - croupSize - (j+2+i));

            }
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 1 && nrOfCardsKind2 == 1 && blefMainNr == 7 )
        {
            int alfa = 0;
            for(int i=1; i<(4-nrOfCardsKind); i++)
            {
                for(int j=0; j<(4-nrOfCardsKind2);j++)
                    alfa += combination(4-nrOfCardsKind,i+1) * combination(4-nrOfCardsKind2,j+1) * combination(24 - playerSize - croupSize - (4-nrOfCardsKind + (4-nrOfCardsKind2)) + nrOfCardsKind2,nrCards - playerSize - croupSize - (j+2+i));

            }
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 0 && nrOfCardsKind2 == 1 && blefMainNr == 2 || (nrOfCardsKind ==1 && nrOfCardsKind2 == 0 && blefMainNr == 2))
        {
            int alfa = 0;
            for(int i=1; i<(4-nrOfCardsKind); i++)
            {
                for(int j=0; j<(4-nrOfCardsKind2);j++)
                    alfa += combination(4-nrOfCardsKind,i+1) * combination(4-nrOfCardsKind2,j+1) * combination(24 - playerSize - croupSize - (4-nrOfCardsKind + (4-nrOfCardsKind2)) + nrOfCardsKind2,nrCards - playerSize - croupSize - (j+2+i));

            }
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 0 && nrOfCardsKind2 == 0 && blefMainNr == 2 )
        {
            int alfa = 0;
            for(int i=1; i<(4-nrOfCardsKind); i++)
            {
                for(int j=1; j<(4-nrOfCardsKind2);j++)
                    alfa += combination(4-nrOfCardsKind,i+1) * combination(4-nrOfCardsKind2,j+1) * combination(24 - playerSize - croupSize - (4-nrOfCardsKind + (4-nrOfCardsKind2)) + nrOfCardsKind2,nrCards - playerSize - croupSize - (j+2+i));

            }
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 1 && nrOfCardsKind2 == 0 && blefMainNr == 7 || (nrOfCardsKind == 0 && nrOfCardsKind2 == 1 && blefMainNr == 7))
        {
            int alfa = 0;
            for(int i=1; i<(4-nrOfCardsKind); i++)
            {
                for(int j=1; j<(4-nrOfCardsKind2);j++)
                    alfa += combination(4-nrOfCardsKind,i+1) * combination(4-nrOfCardsKind2,j+1) * combination(24 - playerSize - croupSize - (4-nrOfCardsKind + (4-nrOfCardsKind2)) + nrOfCardsKind2,nrCards - playerSize - croupSize - (j+2+i));

            }
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 0 && nrOfCardsKind2 == 0 && blefMainNr == 7 )
        {
            int alfa = 0;
            for(int i=2; i<(4-nrOfCardsKind); i++)
            {
                for(int j=1; j<(4-nrOfCardsKind2);j++)
                    alfa += combination(4-nrOfCardsKind,i+1) * combination(4-nrOfCardsKind2,j+1) * combination(24 - playerSize - croupSize - (4-nrOfCardsKind + (4-nrOfCardsKind2)) + nrOfCardsKind2,nrCards - playerSize - croupSize - (j+2+i));

            }
            probability = float(alfa)/omega;
        }
    }
    else if(blefMainNr == 4 || blefMainNr == 5)
    {
        bool isAce = false;
        bool isNine = false;
        if(countCardsNrOrColor[0] != 0)
            isNine = true;
        if(countCardsNrOrColor[5] != 0)
            isAce = true;
        for(int i =0; i<countCardsNrOrColor.size(); i++)
        {
            if(countCardsNrOrColor[i] != 0)
                nrOfCardsKind++;
        }
        if(nrOfCardsKind == 6)
            probability = 1;
        else if(nrOfCardsKind == 5 && isAce == true  &&  isNine == false && blefMainNr == 5)
            probability = 1;
        else if(nrOfCardsKind == 5 && isAce == false && isNine == true && blefMainNr == 4)
            probability = 1;
        else if(nrOfCardsKind == 5 && isAce == false && blefMainNr == 5 || (nrOfCardsKind == 5 && isNine == false && blefMainNr == 4) || (nrOfCardsKind == 5 && isNine == true && isAce == true) || (nrOfCardsKind == 4 && isAce == false && isNine == false) || (nrOfCardsKind == 4 && isAce == true && isNine == false && blefMainNr == 5 ) || (nrOfCardsKind == 4 && isNine == true && isAce == false && blefMainNr == 4))
        {
            int alfa = 0;
            for(int i=0; i<4;i++)
            {
                alfa += combination(4,i+1) * combination(24 - playerSize - croupSize - 4 ,nrCards - playerSize - croupSize - (i+1));
            }
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 4 && isAce == false && isNine == true && blefMainNr == 5 || (nrOfCardsKind == 4 && isNine == false && isAce == true && blefMainNr == 4) || (nrOfCardsKind == 4 && isAce == true && isNine == true) || (nrOfCardsKind == 3 && isAce == false && isNine == false) || (nrOfCardsKind == 3 && isAce == true && isNine == false && blefMainNr == 5) || (nrOfCardsKind == 3 && isAce == false && isNine == true && blefMainNr == 4))
        {
            int alfa = 0;
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4;j++)
                {
                    if(i+j <= nrCards - playerSize - croupSize)
                        alfa += combination(4,i+1) * combination(4,j+1) * combination(24 - playerSize - croupSize - 8, nrCards - playerSize - croupSize - (j+2+i));
                }
            }
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 3 && isAce == true && isNine == true || (nrOfCardsKind == 3 && isAce == true && isNine == false && blefMainNr == 4) || (nrOfCardsKind == 4 && isAce == false && isNine == true && blefMainNr == 5) || (nrOfCardsKind == 2 && isAce == false && isNine == false) || (nrOfCardsKind == 2 && isAce == false && isNine == true && blefMainNr == 4) || (nrOfCardsKind == 2 && isAce == true && isNine == false && blefMainNr == 5))
        {
            int alfa = 0;
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4;j++)
                {
                    for(int k=0; j<4;k++)
                    {
                        if(i+j+k <= nrCards - playerSize - croupSize)
                            alfa += combination(4,i+1) * combination(4,j+1) * combination(4,k+1) * combination(24 - playerSize - croupSize - 12, nrCards - playerSize - croupSize - (j+2+i+k));
                    }
                }

            }
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 2 && isAce == true && isNine == true || (nrOfCardsKind == 2 && isAce == false && isNine == true && blefMainNr == 5) || (nrOfCardsKind == 2 && isAce == true && isNine == false && blefMainNr == 4) || (nrOfCardsKind == 1 && isNine == true && blefMainNr == 4) || (nrOfCardsKind == 1 && isAce == true && blefMainNr == 5))
        {
            int alfa = 0;
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4;j++)
                {
                    for(int k=0; j<4;k++)
                    {
                        for(int l=0; l<4;l++)
                        {
                            if(i+j+k+l <= nrCards - playerSize - croupSize)
                                alfa += combination(4,i+1) * combination(4,j+1) * combination(4,k+1) * combination(4,l+1) * combination(24 - playerSize - croupSize - 16, nrCards - playerSize - croupSize - (j+3+i+k+l));
                        }
                    }
                }

            }
            probability = float(alfa)/omega;
        }
        else if(nrOfCardsKind == 1 && isAce == true && blefMainNr == 4 || (nrOfCardsKind == 0) || (nrOfCardsKind == 1 && isNine == true && blefMainNr == 5))
        {
            int alfa = 0;
            for(int i=0; i<4; i++)
            {
                for(int j=0; j<4;j++)
                {
                    for(int k=0; j<4;k++)
                    {
                        for(int l=0; l<4;l++)
                        {
                            for(int m=0; m<4; m++)
                            {
                                if(i+j+k+l <= nrCards - playerSize - croupSize)
                                    alfa += combination(4,i+1) * combination(4,j+1) * combination(4,k+1) * combination(4,l+1) * combination(4,m+1) * combination(24 - playerSize - croupSize - 20, nrCards - playerSize - croupSize - (j+4+i+k+l+m));
                            }
                        }
                    }
                }

            }
            probability = float(alfa)/omega;
        }
    }
    return probability;
}

int CpuMind::priorityWithKind(int countMain, int countValue, int secondCountMain, int secondCountValue)
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

int CpuMind::getPriorityWithKind() const
{

}

int CpuMind::priorityWithFlush(int countMain ,int countValue)
{
    int priority = 0;
    if(countMain == 5)
        priority = 35 + countValue;
    return priority;
}

int CpuMind::priorityWithStraight(const QList<int> &countCards)
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

int CpuMind::priorityWithStraightFlush(int countMain, int countValue, const QList<int> &countCards)
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


void CpuMind::setPriorityBlef(int blefMain, int blefValue)
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

void CpuMind::setBlefValueString()
{
    ListOfPokersLayouts *a = new ListOfPokersLayouts;
    a->threeOfAKind.size();
    switch (blefMainNr) {
    case 0:
        blefValueString = a->oneCard[blefValueNr];
        break;
    case 1:
        blefValueString = a->onePair[blefValueNr];
        break;
    case 2:
        blefValueString = a->twoPairs[blefValueNr];
        break;
    case 3:
        blefValueString = a->threeOfAKind[blefValueNr];
        break;
    case 4:
        blefValueString = " ";
        break;
    case 5:
        blefValueString = " ";
        break;
    case 6:
        blefValueString = a->flush[blefValueNr];
        break;
    case 7:
        blefValueString = a->fullHouse[blefValueNr];
        break;
    case 8:
        blefValueString = a->fourOfAKind[blefValueNr];
        break;
    case 9:
        blefValueString = a->smallStraightFlush[blefValueNr];
        break;
    case 10:
        blefValueString = a->bigStraightFlush[blefValueNr];
        break;
    default:
        break;
    }
}

int CpuMind::getPriorityCards(int countMainKind, int countValueKind, int secondCountMainKind, int secondCountValueKind, int countMainColor, int countValueColor, QList<int> &countCards)
{
    int prioritySF = priorityWithStraightFlush(countMainColor,countValueColor,countCards);
    int priorityKind = priorityWithKind(countMainKind,countValueKind,secondCountMainKind,secondCountValueKind);
    int priorityFlush = priorityWithFlush(countMainColor,countValueColor);
    int priorityStraight = priorityWithStraight(countCards);
    int priorityCards = getMaxValue(prioritySF,priorityKind,priorityFlush,priorityStraight);
    return priorityCards;
}

int CpuMind::getMaxValue(int a, int b, int c, int d)
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

int CpuMind::getMaxBlefMainNr(int priority) const
{
    if(priority >= 0 && priority < 6)
        return 0;
    else if(priority >= 6 && priority < 12)
        return 1;
    else if(priority >= 12 && priority < 27)
        return 2;
    else if(priority >= 27 && priority < 33)
        return 3;
    else if(priority == 33)
        return 4;
    else if(priority == 34)
        return 5;
    else if(priority >= 35 && priority < 39)
        return 6;
    else if(priority >= 39 && priority < 69)
        return 7;
    else if(priority >= 69 && priority < 73)
        return 8;
    else if(priority >= 73 && priority < 77)
        return 9;
    else if(priority >= 77 && priority < 81)
        return 10;
    return -1;
}

int CpuMind::getMaxBlefValueNr(int priority) const
{
    int j = 0;
    if(priority >= 0 && priority < 6)
        return priority % 6;
    else if(priority >= (j = 6) && priority < 12)
        return (priority - j) % 6;
    else if(priority >= (j = 12) && priority < 27)
        return (priority - j) % 15;
    else if(priority >= (j = 27) && priority < 33)
        return (priority - j) % 6;
    else if(priority == 33)
        return -1;
    else if(priority == 34)
        return -1;
    else if(priority >= (j = 35) && priority < 39)
        return (priority - j) % 4;
    else if(priority >= (j = 39) && priority < 69)
    {
        qDebug() << "j" << j;
        return (priority - j) % 30;
    }
    else if(priority >= (j = 69) && priority < 73)
        return (priority - j) % 4;
    else if(priority >= (j = 73) && priority < 77)
        return (priority - j) % 4;
    else if(priority >= (j = 77) && priority < 81)
        return (priority - j) % 4;
    return -2;
}

int CpuMind::getBlefMainNr()
{
    return blefMainNr;
}

int CpuMind::getBlefValueNr()
{
    return blefValueNr;
}

const QString &CpuMind::getBlefValueString() const
{
    return blefValueString;
}

bool CpuMind::getCheck() const
{
    return check;
}

unsigned long CpuMind::combination(unsigned int n,unsigned int k)
{
    if(k > n )
        return 0;
    if(k == 0 || k == n)
        return 1;
    float comb = 1;
    for(unsigned int i=0;i<k;i++)
    {
        comb *= float((n - i))/(i+1);
    }
    return comb;
}
