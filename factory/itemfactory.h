#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <QSqlRecord>
#include <QVariant>

#include "../entity/item.h"

class ItemFactory
{
public:
    ItemFactory();
    Item createItem(QSqlRecord *itemRecord);
};

#endif // ITEMFACTORY_H
