#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QMetaType>

enum Categoria {
    CATEGORIA1 = 0, CATEGORIA2, CATEGORIA3, CATEGORIA4
};

class Item
{
public:
    Item() = default;
    ~Item() = default;
    Item(const Item &) = default;
    Item &operator=(const Item &) = default;

    Item(QString nome, Categoria categoria, long double preco, int quantidade);
    QString getId();
    void setId(QString id);
    QString getNome();
    int getCategoria();
    long double getPreco();
    int getQuantidade();
    void setQuantidade(int quantidade);

    bool operator == (Item item);

private:
    QString id;
    QString nome;
    Categoria categoria;
    long double preco;
    int quantidade;
};

Q_DECLARE_METATYPE(Item);

#endif // ITEM_H
