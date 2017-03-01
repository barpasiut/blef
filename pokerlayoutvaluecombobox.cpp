#include "pokerlayoutvaluecombobox.h"

PokerLayoutValueComboBox::PokerLayoutValueComboBox()
{
    options = new QStringList();

}

PokerLayoutValueComboBox::~PokerLayoutValueComboBox()
{
    delete options;
}
