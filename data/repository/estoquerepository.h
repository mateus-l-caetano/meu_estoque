#ifndef ESTOQUEDATASOURCE_H
#define ESTOQUEDATASOURCE_H

#include <QUuid>
#include <QHash>
#include <QObject>

#include "../../entity/item.h"
#include "../database/database.h"

class EstoqueRepository : public QObject
{
    Q_OBJECT

public:
    EstoqueRepository(DatabaseManager *estoque);

signals:
    void dataSetChanged();
    void successfullyRegisteredItem();
    void getItensSuccess(QList<Item> itens);
    void successInUpdatingItemVolume();
    void errorRegisteringItem(QString errorMessage);
    void errorGetingItens(QString errorMessage);
    void errorWhenUpdatingItemVolume(QString errorMessage);

public slots:
    void cadastrarItem(Item novoItem);
    void setQuantidade(int novaQuantidade, QString IdDoItem);
    void adicionarItem(int indiceDoItemASerAdicionado, unsigned int quantidadeDeItensASeremAdicionados = 1);
    void removerItem(QString idDoitemASerRemovido, unsigned int quantidadeDeItensASeremRemovidos = 1);
    void getItens();

private:
    void carregarItensPadrao();
    DatabaseManager *estoque = nullptr;
};

#endif // ESTOQUEDATASOURCE_H
