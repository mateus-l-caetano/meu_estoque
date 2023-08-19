#ifndef CADASTRODEITEMUSECASE_H
#define CADASTRODEITEMUSECASE_H

#include <QThread>
#include <QMutexLocker>

#include "../data/repository/estoquerepository.h"

class CadastroDeItemUseCase : public QObject
{
    Q_OBJECT

public:
    CadastroDeItemUseCase(EstoqueRepository *estoqueRepository);
    ~CadastroDeItemUseCase();
    void execute(Item item);

signals:
    void success();
    void fail(QString message);

private:
    EstoqueRepository *estoqueRepository = nullptr;
};

#endif // CADASTRODEITEMUSECASE_H
