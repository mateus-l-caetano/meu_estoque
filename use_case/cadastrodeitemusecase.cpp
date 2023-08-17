#include "cadastrodeitemusecase.h"

CadastroDeItemUseCase::CadastroDeItemUseCase(EstoqueDataSource *estoqueDataSource) : QObject()
{
    this->estoqueDataSource = estoqueDataSource;
}

CadastroDeItemUseCase::~CadastroDeItemUseCase()
{
}

void CadastroDeItemUseCase::execute(Item item)
{
    qDebug() << "cadastra";
    connect(this->estoqueDataSource, &EstoqueDataSource::successfullyRegisteredItem, this, &CadastroDeItemUseCase::success);
    this->estoqueDataSource->cadastrarItem(item);
    return;
}
