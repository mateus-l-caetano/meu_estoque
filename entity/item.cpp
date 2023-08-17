#include "item.h"
#include<QUuid>
Item::Item(QString nome, Categoria categoria, long double preco, int quantidade)
{
    this->id = QUuid::createUuid().toString();
    this->nome = nome;
    this->categoria = categoria;
    this->preco = preco;
    this->quantidade = quantidade;
}

Item::Item(QString id, QString nome, Categoria categoria, long double preco, int quantidade)
{
    this->id = id;
    this->nome = nome;
    this->categoria = categoria;
    this->preco = preco;
    this->quantidade = quantidade;
}

QString Item::getId()
{
    return this->id;
}

QString Item::getNome()
{
    return this->nome;
}

int Item::getCategoria()
{
    return this->categoria;
}

long double Item::getPreco()
{
    return this->preco;
}

int Item::getQuantidade()
{
    return quantidade;
}

void Item::setQuantidade(int quantidade)
{
    this->quantidade = quantidade;
}

bool Item::operator ==(Item item)
{
    if((this->nome == item.nome)
        & (this->categoria == item.categoria)
        & (this->preco == item.preco)
        & (this->quantidade == item.quantidade)) {
        return true;
    }

    return false;
}
