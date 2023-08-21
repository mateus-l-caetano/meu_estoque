#ifndef SETITEMVOLUMEUSECASE_H
#define SETITEMVOLUMEUSECASE_H

#include <QObject>

#include "../data/repository/estoquerepository.h"

class SetItemVolumeUseCase : public QObject
{
    Q_OBJECT
public:
    explicit SetItemVolumeUseCase(EstoqueRepository *estoqueRepository, QObject *parent = nullptr);
    void execute(int novaQuantidade, QString idDoItem);

signals:
    void successInUpdatingItemVolume();
    void errorWhenUpdatingItemVolume();

private:
    EstoqueRepository *estoqueRepository = nullptr;
};

#endif // SETITEMVOLUMEUSECASE_H
