#include "estoquemodel.h"

EstoqueModel::EstoqueModel(GetEstoqueUseCase *getEstoqueUseCase, QObject *parent) : QAbstractListModel(parent)
{
    connect(getEstoqueUseCase, &GetEstoqueUseCase::success, this, &EstoqueModel::setItens);
    getEstoqueUseCase->execute();
}

int EstoqueModel::rowCount(const QModelIndex &parent) const
{
    return this->itens.count();
}

QVariant EstoqueModel::data(const QModelIndex &index, int role) const
{
    QVariant data;

    Item item = itens.at(index.row());
    switch (role) {
    case Nome:
        data = item.getNome();
        break;

    case Categoria:
        data = item.getCategoria();
        break;

    case Preco:
        data = double(item.getPreco());
        break;

    case Quantidade:
        data = item.getQuantidade();
        break;

    default:
        break;
    }

    return data;
}

QHash<int, QByteArray> EstoqueModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Id] = "id";
    roles[Nome] = "nome";
    roles[Categoria] = "categoria";
    roles[Preco] = "preco";
    roles[Quantidade] = "quantidade";
    return roles;
}

void EstoqueModel::setItens(QList<Item> itens)
{
    this->itens = itens;
}
