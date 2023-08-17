#ifndef CADASTRODEITEMUSECASE_H
#define CADASTRODEITEMUSECASE_H

#include <QThread>
#include <QMutexLocker>

#include "../data/repository/estoquerepository.h"

class CadastroDeItemUseCase : public QObject
{
    Q_OBJECT

public:
    CadastroDeItemUseCase(EstoqueDataSource *estoqueDataSource);
    ~CadastroDeItemUseCase();
    void execute(Item item);

signals:
    void success();

private:
    EstoqueDataSource *estoqueDataSource = nullptr;
};

#endif // CADASTRODEITEMUSECASE_H
