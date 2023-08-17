#ifndef GETESTOQUEUSECASE_H
#define GETESTOQUEUSECASE_H

#include <QObject>
#include <QThread>
#include <QMutexLocker>

#include "../data/repository/estoquerepository.h"

class GetEstoqueUseCase : public QObject
{
    Q_OBJECT

public:
    GetEstoqueUseCase(EstoqueDataSource *estoqueDataSource);
    ~GetEstoqueUseCase();
    void execute();

signals:
    void success(QList<Item> itens);

private:
    EstoqueDataSource *estoqueDataSource = nullptr;

private slots:
    void printEstoque(QList<Item> itens);
};

#endif // GETESTOQUEUSECASE_H
