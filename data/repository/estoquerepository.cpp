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
    qDebug() << "cadastro data source";

    bool isSuccess = this->estoque->registerItem(
                novoItem.getId(),
                novoItem.getNome(),
                novoItem.getCategoria(),
                novoItem.getPreco(),
                novoItem.getQuantidade());
    if(isSuccess) {
        emit successfullyRegisteredItem();
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
    qDebug() << "getItens data source";

    QList<Item> itens = this->estoque->getItens();
    emit getItensSuccess(itens);
}
