#include "getestoqueusecase.h"

GetEstoqueUseCase::GetEstoqueUseCase(EstoqueDataSource *estoqueDataSource)
{
    this->estoqueDataSource = estoqueDataSource;
}

GetEstoqueUseCase::~GetEstoqueUseCase()
{
}

void GetEstoqueUseCase::execute()
{
    qDebug() << "get estoque";
    connect(this->estoqueDataSource, &EstoqueDataSource::getItensSuccess, this, &GetEstoqueUseCase::success);
    connect(this->estoqueDataSource, &EstoqueDataSource::getItensSuccess, this, &GetEstoqueUseCase::printEstoque);
    this->estoqueDataSource->getItens();
}

void GetEstoqueUseCase::printEstoque(QList<Item> itens)
{
    qDebug() << "printEstoque";
    for(auto item : itens) {
        qDebug() << item.getNome();
    }
}
