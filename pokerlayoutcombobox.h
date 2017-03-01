#ifndef POKERLAYOUTCOMBOBOX_H
#define POKERLAYOUTCOMBOBOX_H

#include <QComboBox>

class PokerLayoutComboBox : public QComboBox
{
public:
    PokerLayoutComboBox();
    ~PokerLayoutComboBox();
private:
    QStringList *options;
public slots:
};

#endif // POKERLAYOUTCOMBOBOX_H
