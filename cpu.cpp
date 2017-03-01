#include "cpu.h"

Cpu::Cpu()
{
    mind = new CpuMind;
}

Cpu::~Cpu()
{
    delete mind;
}


void Cpu::appendCard(Card *c)
{
//    QImage img;
//    img.load(":/img/red_joker.png");
//    c->setWidth(img.width());
//    c->setHeight(img.height());
//    c->setPixmapCard(QPixmap::fromImage(img));

    this->append(c);
    setPlayerCards(c->getNumberAndColor(),1);

}

void Cpu::appendCard(Card *c, int n)
{
//    QImage img;
//    img.load(":/img/red_joker.png");
//    c->setWidth(img.width());
//    c->setHeight(img.height());
//    c->setPixmapCard(QPixmap::fromImage(img));

    this->append(c);
    setPlayerCards(c->getNumberAndColor(),n);

}

CpuMind &Cpu::getCpuMind()
{
    return *mind;
}

const CpuMind &Cpu::getCpuMind() const
{
    return *mind;
}

void Cpu::setBlefChoice(int blefMainNr, QString blefMainString, int blefValueNr, QString blefValueString)
{
    setBlefChoice(blefMainString + "." + QString::number(blefMainNr) + "." + blefValueString + "." + QString::number(blefValueNr));
}

