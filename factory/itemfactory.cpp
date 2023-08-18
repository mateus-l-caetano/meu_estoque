#include "itemfactory.h"

ItemFactory::ItemFactory()
{

}

Item ItemFactory::createItem(QSqlRecord *itemRecord)
{
    QString id = itemRecord->value("id").toString();
    QString nome = itemRecord->value("nome").toString();
    unsigned int categoria = itemRecord->value("categoria").toUInt();
    long double preco = qvariant_cast<long double>(itemRecord->value("preco"));
    unsigned int quantidade = itemRecord->value("quantidade").toUInt();
    Item item = Item(id, nome, Categoria(categoria), preco, quantidade);
    return item;
}
