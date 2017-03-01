#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QWidget>
#include <QFormLayout>
#include "pokerlayoutcombobox.h"
#include "pokerlayoutvaluecombobox.h"
#include "gamecontrolblefbutton.h"
#include "listofpokerslayouts.h"

class GameControl : public QFormLayout, public ListOfPokersLayouts
{
    Q_OBJECT
public:
    GameControl();
    ~GameControl();
    void setBlefChoice(const QString &, int, const QString &s2 = 0, int i2= 0); // s1 = pbox choice , i = index of pbox, s2 = pvbox choice, i2 = index of pvbox
    const GameControlBlefButton * getBButton() const;
    const GameControlBlefButton * getCheckButton() const;
    const PokerLayoutComboBox * getPBox() const;
    const PokerLayoutValueComboBox * getPVBox() const;
    const QString & getBlefChoice() const;
private:
    PokerLayoutComboBox *pbox;
    PokerLayoutValueComboBox *pvbox;
    GameControlBlefButton *bbutton;
    GameControlBlefButton *checkbutton;
signals:

public slots:
    void changePVBox();
};

#endif // GAMECONTROL_H
