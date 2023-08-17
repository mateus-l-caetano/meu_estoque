#ifndef ESTOQUEDATASOURCE_H
#define ESTOQUEDATASOURCE_H

#include <QUuid>
#include <QHash>
#include <QObject>

#include "../../entity/item.h"
#include "../database/database.h"

class EstoqueDataSource : public QObject
{
    Q_OBJECT

public:
    EstoqueDataSource(DatabaseManager *estoque);

signals:
    void successfullyRegisteredItem();
    void getItensSuccess(QList<Item> itens);
    void error(QVariant response);

public slots:
    void cadastrarItem(Item novoItem);
    void adicionarItem(int indiceDoItemASerAdicionado, unsigned int quantidadeDeItensASeremAdicionados = 1);
    void removerItem(QString idDoitemASerRemovido, unsigned int quantidadeDeItensASeremRemovidos = 1);
    void getItens();

private:
    void carregarItensPadrao();
    DatabaseManager *estoque = nullptr;
};

#endif // ESTOQUEDATASOURCE_H
