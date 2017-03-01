#include "gamecontrol.h"
#include <QDebug>

GameControl::GameControl()
{
    pbox = new PokerLayoutComboBox();
    pvbox = new PokerLayoutValueComboBox();
    bbutton = new GameControlBlefButton();
    checkbutton = new GameControlBlefButton();

    pbox->insertItems(0,mainLayout);

    bbutton->setText("Zablefuj");
    checkbutton->setText("Sprawdź");

    this->addRow("Wybierz układ",pbox);
    this->addRow("Wybierz wartośc",pvbox);
    this->addRow("",bbutton);
    this->addRow("",checkbutton);

    connect(pbox,SIGNAL(currentTextChanged(QString)),this,SLOT(changePVBox()));

}

GameControl::~GameControl()
{
    delete checkbutton;
    delete bbutton;
    delete pvbox;
    delete pbox;
}

const GameControlBlefButton * GameControl::getBButton() const
{
    return bbutton;
}

const GameControlBlefButton * GameControl::getCheckButton() const
{
    return checkbutton;
}

const PokerLayoutComboBox * GameControl::getPBox() const
{
    return pbox;
}

const PokerLayoutValueComboBox * GameControl::getPVBox() const
{
    return pvbox;
}


void GameControl::changePVBox()
{
    qDebug() << pbox->currentText();
    for (int i=0; i<mainLayout.size(); i++)
    {
        qDebug() << mainLayout[i];
        if(pbox->currentText() == mainLayout[i])
        {
            switch(i)
            {
            case 0:
                if(!pvbox->isEnabled())
                    pvbox->setEnabled(true);
                pvbox->clear();
                pvbox->insertItems(0,oneCard);
                break;
            case 1:
                if(!pvbox->isEnabled())
                    pvbox->setEnabled(true);
                pvbox->clear();
                pvbox->insertItems(0,onePair);
                break;
            case 2:
                if(!pvbox->isEnabled())
                    pvbox->setEnabled(true);
                pvbox->clear();
                pvbox->insertItems(0,twoPairs);
                break;
            case 3:
                if(!pvbox->isEnabled())
                    pvbox->setEnabled(true);
                pvbox->clear();
                pvbox->insertItems(0,threeOfAKind);
                break;
            case 4:
                pvbox->clear();
                pvbox->setEnabled(false);
                break;
            case 5:
                pvbox->clear();
                pvbox->setEnabled(false);
                break;
            case 6:
                if(!pvbox->isEnabled())
                    pvbox->setEnabled(true);
                pvbox->clear();
                pvbox->insertItems(0,flush);
                break;
            case 7:
                if(!pvbox->isEnabled())
                    pvbox->setEnabled(true);
                pvbox->clear();
                pvbox->insertItems(0,fullHouse);
                break;
            case 8:
                if(!pvbox->isEnabled())
                    pvbox->setEnabled(true);
                pvbox->clear();
                pvbox->insertItems(0,fourOfAKind);
                break;
            case 9:
                if(!pvbox->isEnabled())
                    pvbox->setEnabled(true);
                pvbox->clear();
                pvbox->insertItems(0,smallStraightFlush);
                break;
            case 10:
                if(!pvbox->isEnabled())
                    pvbox->setEnabled(true);
                pvbox->clear();
                pvbox->insertItems(0,bigStraightFlush);
                break;
            }
        }
    }
    return;
}

