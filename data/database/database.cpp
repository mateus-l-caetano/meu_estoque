#include "database.h"

DatabaseManager *DatabaseManager::m_databaseManager = nullptr;

DatabaseManager::DatabaseManager(DatabaseConnection *databaseConnection) : QThread(), m_databaseConnetion(databaseConnection)
{
    try {
        this->m_databaseConnetion->openDatabaseConnection();

        this->m_database = m_databaseConnetion->database();

        if(!this->m_database->tables().contains("estoque")) {
            this->createEstoqueTable();
        }
    } catch (std::runtime_error error) {
        qDebug() << error.what();
    }
}

void DatabaseManager::createEstoqueTable()
{
    qDebug() << "create database";

    QSqlQuery createEstoqueTableQuery(*this->m_database);
    createEstoqueTableQuery.prepare(CREATE_ESTOQUE_TABLE_QUERY);

    if(createEstoqueTableQuery.exec()) {
        qDebug() << "tabela estoque criada com sucesso";
    } else {
        this->throwError(&createEstoqueTableQuery);
    }
}

void DatabaseManager::run()
{

}

DatabaseManager *DatabaseManager::getInstance()
{
    if(m_databaseManager == nullptr) {
        m_databaseManager = new DatabaseManager(DatabaseConnection::getInstance());
    }

    return m_databaseManager;
}

DatabaseManager::~DatabaseManager()
{
    this->m_databaseConnetion->closeDatabaseConnection();
}

void DatabaseManager::throwError(QSqlQuery *query)
{
    QString error = query->lastError().text();
    throw std::runtime_error(error.toStdString());
}

bool DatabaseManager::registerItem(QString id, QString nome, unsigned int categoria, long double preco, int quantidade)
{
    qDebug() << "register Item";

    QMutexLocker lock(&estoqueMutex);

    QSqlQuery registerItemQuery;
    registerItemQuery.prepare(REGISTER_ITEM_QUERY);
    registerItemQuery.bindValue(":id", id);
    registerItemQuery.bindValue(":nome", nome);
    registerItemQuery.bindValue(":categoria", categoria);
    registerItemQuery.bindValue(":preco", QVariant::fromValue(preco));
    registerItemQuery.bindValue(":quantidade", quantidade);

    if(this->m_database->isOpen()){
        if(registerItemQuery.exec()) {
            qDebug() << "item cadastrado com sucesso";
            return true;
        } else {
            this->throwError(&registerItemQuery);
            return false;
        }
    } else {
        qDebug() << "problema em acessar o banco de dados";
    }

    return false;
}

QList<Item> DatabaseManager::getItens()
{
    qDebug() << "get itens";

    QMutexLocker lock(&estoqueMutex);

    QList<Item> itens;
    Item currentItem;
    QSqlQuery getItensQuery(*this->m_database);
    QSqlRecord currentItemRecord;
    ItemMapper itemMapper;

    getItensQuery.prepare(GET_ITENS_QUERY);
    if(getItensQuery.exec()) {
        while(getItensQuery.next()) {
            currentItemRecord = getItensQuery.record();
            currentItem = itemMapper.toItem(&currentItemRecord);

            itens.push_back(currentItem);
        }
    } else {
        throwError(&getItensQuery);
    }

    return itens;
}

bool DatabaseManager::setQuantidade(int novaQuantidade, QString IdDoItem)
{
    qDebug() << "set quantidade";

    QMutexLocker lock(&estoqueMutex);

    QSqlQuery setQuantidadeQuery(*this->m_database);
    setQuantidadeQuery.prepare(SET_QUANTIDADE_QUERY);
    setQuantidadeQuery.bindValue(":quantidade", novaQuantidade);
    setQuantidadeQuery.bindValue(":id", IdDoItem);
    if(!setQuantidadeQuery.exec()) {
        throwError(&setQuantidadeQuery);
    } else {
        return true;
    }

    return false;
}

void DatabaseManager::addItem()
{

}

int DatabaseManager::size()
{
    QSqlQuery sizeQuery(*this->m_database);
    sizeQuery.prepare(GET_SIZE_QUERY);
    if(sizeQuery.exec()) {
        return sizeQuery.next();
    } else {
        this->throwError(&sizeQuery);
    }

    return 0;
}
