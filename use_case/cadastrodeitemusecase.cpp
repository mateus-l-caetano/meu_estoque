#include "cadastrodeitemusecase.h"

CadastroDeItemUseCase::CadastroDeItemUseCase(EstoqueRepository *estoqueRepository) : QObject()
{
    this->estoqueRepository = estoqueRepository;
}

CadastroDeItemUseCase::~CadastroDeItemUseCase()
{
}

void CadastroDeItemUseCase::execute(Item item)
{
    qDebug() << "cadastra";
    connect(this->estoqueRepository, &EstoqueRepository::successfullyRegisteredItem, this, &CadastroDeItemUseCase::success);
    this->estoqueRepository->cadastrarItem(item);
    return;
}
