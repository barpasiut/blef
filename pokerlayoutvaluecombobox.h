#ifndef POKERLAYOUTVALUECOMBOBOX_H
#define POKERLAYOUTVALUECOMBOBOX_H

#include <QComboBox>

class PokerLayoutValueComboBox : public QComboBox
{
public:
    PokerLayoutValueComboBox();
    ~PokerLayoutValueComboBox();
private:
    QStringList *options;
};

#endif // POKERLAYOUTVALUECOMBOBOX_H
