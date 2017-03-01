#include "card.h"
#include "time.h"
#include "stdlib.h"
#include <QImage>
#include <QDebug>

QList<QString> Card::unUsedCards = cardsList();

Card::Card()
{
    randCard("/img");
    QImage img;
    img.load(path);
    width = img.width();
    height = img.height();
    this->setPixmapCard(QPixmap::fromImage(img));
}

Card::~Card()
{

}

int Card::getNumber() const
{
    return number;
}

int Card::getWidth() const
{
    return width;
}

int Card::getHeight() const
{
    return height;
}

const QString & Card::getColor() const
{
    return color;
}

const QString & Card::getPath() const
{
    return path;
}

const QString & Card::getNumberAndColor() const
{
    return numberAndColor;
}

void Card::setNumber(int n)
{
    number = n;
}

void Card::setWidth(int w)
{
    width = w;
}

void Card::setHeight(int h)
{
    height = h;
}

void Card::setColor(const QString &c)
{
    color = c;
}

void Card::setPath(const QString &p)
{
    path = p;
}

void Card::setNumberAndColor(const QString &s)
{
    numberAndColor = s;
}

void Card::setScaleCard(qreal f)
{
    this->setScale(f);
    height *= f;
    width *= f;
}

void Card::setUnUsedCards()
{
    for(int i=0; i<Card::unUsedCards.size();i++){
        if(Card::unUsedCards[i] == numberAndColor)
            Card::unUsedCards.removeAt(i);

    }
}

void Card::setUnUsedCards(QList<QString> cList)
{
    Card::unUsedCards = cList;
}

QList<QString> & Card::getUnUsedCards()
{
    return Card::unUsedCards;
}

const int Card::getNumberOfCardsInDeck()
{
    return numberOfCardsInDeck;
}

void Card::randCard(const QString &s)
{
    int cardNr = rand()%Card::unUsedCards.size();
    numberAndColor = Card::unUsedCards[cardNr];
    QStringList list = numberAndColor.split(".");
    number = list[0].toInt();
    color = list[1];

    if(number < 11)
    {
        path = + ":" + s + "/" + QString::number(number) + "_of_" + color + ".png";
    }
    else if(number == 11)
        path = + ":" + s + "/jack_of_" + color + ".png";
    else if(number == 12)
        path = + ":" + s + "/queen_of_" + color + ".png";
    else if(number == 13)
        path = + ":" + s + "/king_of_" + color + ".png";
    else
        path = + ":" + s + "/ace_of_" + color + ".png";

}

void Card::setPixmapCard(const QPixmap &p)
{
    this->setPixmap(p);
    setUnUsedCards();
}


QList<QString> cardsList()
{
    QList<QString> list;
    for(int i=0;i<4;i++){
        for(int j=9;j<15;j++){
            switch(i)
            {
            case 0:
                list.append(QString::number(j) + "." + "clubs");
                break;
            case 1:
                list.append(QString::number(j) + "." + "diamonds");
                break;
            case 2:
                list.append(QString::number(j) + "." + "hearts");
                break;
            case 3:
                list.append(QString::number(j) + "." + "spades");
                break;
            }

        }

    }
    return list;
}
