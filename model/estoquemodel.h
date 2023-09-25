#ifndef ESTOQUEMODEL_H
#define ESTOQUEMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "../entity/item.h"
#include "../use_case/getestoqueusecase.h"

class EstoqueModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit EstoqueModel(GetEstoqueUseCase *getEstoqueUseCase, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    enum EstoqueRoles {
        Id = Qt::UserRole + 1,
        Nome,
        Categoria,
        Preco,
        Quantidade
    };

private:
    QList<Item> itens;
    void setItens(QList<Item> itens);
};

#endif // ESTOQUEMODEL_H
