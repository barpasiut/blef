#include "pokerlayoutcombobox.h"
#include <QDebug>

PokerLayoutComboBox::PokerLayoutComboBox()
{
    options = new QStringList();
}

PokerLayoutComboBox::~PokerLayoutComboBox()
{
    delete options;
}
