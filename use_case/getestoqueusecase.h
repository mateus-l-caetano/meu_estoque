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
    GetEstoqueUseCase(EstoqueRepository *estoqueRepository);
    ~GetEstoqueUseCase();
    void execute();

signals:
    void success(QList<Item> itens);
    void fail(QString message);

private:
    EstoqueRepository *estoqueRepository = nullptr;

private slots:
    void printEstoque(QList<Item> itens);
};

#endif // GETESTOQUEUSECASE_H
