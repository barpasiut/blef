#include "listofpokerslayouts.h"

ListOfPokersLayouts::ListOfPokersLayouts()
{
    mainLayout << "Karta" << "Para" << "Dwie Pary" << "Trójka" << "Mały Strit" << "Duży Strit" << "Kolor" << "Full" << "Kareta" << "Mały Poker" << "Duży Poker";
    oneCard << "Dziewiątka" << "Dziesiątka" << "Walet" << "Dama" << "Król" << "As";
    onePair << "Dziewiątek" << "Dziesiątek" << "Waletów" << "Dam" << "Króli" << "Asów";
    for(int i=0;i < oneCard.size();i++)
    {
        for(int j=i+1;j<oneCard.size();j++)
        {
            if(i != j)
                twoPairs << (oneCard[i] + " i " + oneCard[j]);
        }
    }
    threeOfAKind << "Dziewiątek" << "Dziesiątek" << "Waletów" << "Dam" << "Króli" << "Asów";
    flush << "Trefl" << "Karo" << "Kier" << "Pik";
    QStringList list;
    list << "Dziewiątki" << "Dziesiątki" << "Walety" << "Damy" << "Króle" << "Asy";
    for(int i=0;i < list.size();i++)
    {
        for(int j=0;j<list.size();j++)
        {
            if(i != j)
                fullHouse << ("3 " + list[i] + " i 2 " + list[j]);
        }
    }
    fourOfAKind << "Dziewiątek" << "Dziesiątek" << "Waletów" << "Dam" << "Króli" << "Asów";
    smallStraightFlush << "Trefl" << "Karo" << "Kier" << "Pik";
    bigStraightFlush << "Trefl" << "Karo" << "Kier" << "Pik";

    for (int i=0; i <mainLayout.size(); i++)
    {
        if(i == 0)
        {
            list.clear();
            list << "Dziewiątka" << "Dziesiątka" << "Walet" << "Dama" << "Król" << "As";
            mainLayoutValue.append(list);
        }
        if(i == 1 || i == 3 || i == 6)
        {
            list.clear();
            list << "Dziewiątek" << "Dziesiątek" << "Waletów" << "Dam" << "Króli" << "Asów";
            mainLayoutValue.append(list);
        }
        if(i == 2)
        {
            list.clear();
            for(int j=0;j < mainLayoutValue[0].size();j++)
            {
                for(int k=j+1;k< mainLayoutValue[0].size();k++)
                {
                    if(i != j)
                        list << (mainLayoutValue[0][i] + " i " + mainLayoutValue[0][j]);
                }
            }
            mainLayoutValue.append(list);
        }
        if(i == 4 || i == 7 || i == 8)
        {
            list.clear();
            list << "Trefl" << "Karo" << "Kier" << "Pik";
            mainLayoutValue.append(list);
        }
        if(i == 5)
        {
            QStringList list2;
            list.clear();
            list << "Dziewiątki" << "Dziesiątki" << "Walety" << "Damy" << "Króle" << "Asy";
            for(int j=0;j < list.size();j++)
            {
                for(int k=0;k<list.size();k++)
                {
                    if(j != k)
                        list2 << ("3 " + list[i] + " i 2 " + list[j]);
                }
            }
            mainLayoutValue.append(list2);
        }
    }
}

ListOfPokersLayouts::~ListOfPokersLayouts()
{

}
