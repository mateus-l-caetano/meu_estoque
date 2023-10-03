#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <QSqlRecord>
#include <QVariant>

#include "../../entity/item.h"

class ItemMapper
{
public:
    ItemMapper();
    Item toItem(QSqlRecord *itemRecord);
};

#endif // ITEMFACTORY_H
