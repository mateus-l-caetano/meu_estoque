#include "setitemvolumeusecase.h"

SetItemVolumeUseCase::SetItemVolumeUseCase(EstoqueRepository *estoqueRepository, QObject *parent)
    : QObject{parent}
{
    this->estoqueRepository = estoqueRepository;
}

void SetItemVolumeUseCase::execute(int novaQuantidade, QString idDoItem)
{
    qDebug() << "set item volume";
    connect(this->estoqueRepository, &EstoqueRepository::successInUpdatingItemVolume, this, &SetItemVolumeUseCase::successInUpdatingItemVolume);
    connect(this->estoqueRepository, &EstoqueRepository::errorWhenUpdatingItemVolume, this, &SetItemVolumeUseCase::errorWhenUpdatingItemVolume);
    this->estoqueRepository->setQuantidade(novaQuantidade, idDoItem);
}
