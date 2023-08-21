#include "estoquerepository.h"

EstoqueRepository::EstoqueRepository(DatabaseManager *estoque) : QObject()
{
    this->estoque = estoque;

//    this->carregarItensPadrao();
}

void EstoqueRepository::carregarItensPadrao()
{
    int categoriaRange = 1;
    for(int i = 0; i < 10; i++) {
        QString itemName = "item " + QString::fromStdString(std::to_string(i));
        Categoria categoria;
        long double preco = 4.50 + i;
        int quantidade = 10 * i;

        if(categoriaRange >= 4) categoriaRange = 1;
        else categoriaRange += 1;

        switch (categoriaRange) {
        case 1:
            categoria = CATEGORIA1;
            break;
        case 2:
            categoria = CATEGORIA2;
            break;
        case 3:
            categoria = CATEGORIA3;
            break;
        case 4:
            categoria = CATEGORIA4;
            break;
        default:
            categoria = CATEGORIA1;
            break;
        }

        Item item(itemName, categoria, preco, quantidade);

        cadastrarItem(item);
    }

    return;
}

void EstoqueRepository::cadastrarItem(Item novoItem)
{
    qDebug() << "cadastro repository";

    try {
        bool isSuccess = this->estoque->registerItem(
                    novoItem.getId(),
                    novoItem.getNome(),
                    novoItem.getCategoria(),
                    novoItem.getPreco(),
                    novoItem.getQuantidade());
        if(isSuccess) {
            emit successfullyRegisteredItem();
        }
    } catch (std::exception err) {
        QString errorMessage = "erro ao cadastrar item: " + QString::fromStdString(err.what());
        emit errorRegisteringItem(errorMessage);
    }
}

void EstoqueRepository::setQuantidade(int novaQuantidade, QString IdDoItem)
{
    qDebug() << "set quantidade repository";

    try {
        bool isSuccess = this->estoque->setQuantidade(novaQuantidade, IdDoItem);
        if(isSuccess) {
            emit successInUpdatingItemVolume();
        }
    } catch (std::exception err) {
        QString errorMessage = "erro ao alterar quantidade do item: " + QString::fromStdString(err.what());
        emit errorWhenUpdatingItemVolume(errorMessage);
    }
}

void EstoqueRepository::adicionarItem(int indiceDoItemASerAdicionado, unsigned int quantidadeDeItensASeremAdicionados)
{

}

void EstoqueRepository::removerItem(QString idDoitemASerRemovido, unsigned int quantidadeDeItensASeremRemovidos)
{

}

void EstoqueRepository::getItens()
{
    qDebug() << "getItens repository";

    try {
        QList<Item> itens = this->estoque->getItens();
        emit getItensSuccess(itens);
    } catch (std::exception err) {
        QString errorMessage = "erro ao recuperar itens: " + QString::fromStdString(err.what());
        emit errorGetingItens(errorMessage);
    }
}
