#include "getestoqueusecase.h"

GetEstoqueUseCase::GetEstoqueUseCase(EstoqueRepository *estoqueRepository)
{
    this->estoqueRepository = estoqueRepository;
}

GetEstoqueUseCase::~GetEstoqueUseCase()
{
}

void GetEstoqueUseCase::execute()
{
    qDebug() << "get estoque";
    connect(this->estoqueRepository, &EstoqueRepository::getItensSuccess, this, &GetEstoqueUseCase::success);
    connect(this->estoqueRepository, &EstoqueRepository::errorGetingItens, this, &GetEstoqueUseCase::fail);
    connect(this->estoqueRepository, &EstoqueRepository::dataSetChanged, this->estoqueRepository, &EstoqueRepository::getItens);
//    connect(this->estoqueRepository, &EstoqueRepository::getItensSuccess, this, &GetEstoqueUseCase::printEstoque);
    this->estoqueRepository->getItens();
}

void GetEstoqueUseCase::printEstoque(QList<Item> itens)
{
    qDebug() << "printEstoque";
    for(auto item : itens) {
        qDebug() << item.getNome();
    }
}
