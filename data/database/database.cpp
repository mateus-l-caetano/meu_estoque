#include "database.h"

DatabaseManager *DatabaseManager::m_databaseManager = nullptr;

DatabaseManager::DatabaseManager() : QThread()
{
    this->openDatabase();
}

void DatabaseManager::openDatabase()
{
    qDebug() << "open database";

    QDir databasePath;
    QString path = databasePath.currentPath()+"/meu_estoque.db";
    qDebug() << "path do banco de dados" << path;

    this->m_database = QSqlDatabase::addDatabase("QSQLITE");
    this->m_database.setDatabaseName(path);

    if(!this->m_database.open()) {
        std::string databaseErrorMessage = this->m_database.lastError().text().toStdString();
        std::string errorMessage = "não foi possível acessar o banco de dados: " + databaseErrorMessage;

        throw std::runtime_error(errorMessage);
    } else if(!this->m_database.tables().contains("estoque")) {
        qDebug() << "banco aberto com sucesso";
        this->createEstoqueTable();
    } else {
        qDebug() << "banco pronto para uso";
    }
}

void DatabaseManager::createEstoqueTable()
{
    qDebug() << "create database";

    QSqlQuery createEstoqueTableQuery(m_database);
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
        m_databaseManager = new DatabaseManager();
    }

    return m_databaseManager;
}

DatabaseManager::~DatabaseManager()
{
    this->m_database.close();
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

    if(this->m_database.isOpen()){
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
    QSqlQuery getItensQuery(this->m_database);
    QSqlRecord currentItemRecord;
    ItemFactory itemFactory;

    getItensQuery.prepare(GET_ITENS_QUERY);
    if(getItensQuery.exec()) {
        while(getItensQuery.next()) {
            currentItemRecord = getItensQuery.record();
            currentItem = itemFactory.createItem(&currentItemRecord);

            itens.push_back(currentItem);
        }
    } else {
        throwError(&getItensQuery);
    }

    return itens;
}

void DatabaseManager::addItem()
{

}

int DatabaseManager::size()
{
    QSqlQuery sizeQuery(this->m_database);
    sizeQuery.prepare(GET_SIZE_QUERY);
    if(sizeQuery.exec()) {
        return sizeQuery.next();
    } else {
        this->throwError(&sizeQuery);
    }

    return 0;
}
