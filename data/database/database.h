#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlRecord>
#include <QDir>
#include <QtConcurrent>

#include "../databaseconnection.h"
#include "../../entity/item.h"
#include "../mapper/itemmapper.h"

class DatabaseManager : public QThread
{
    Q_OBJECT

public:
    void run() override;
    static DatabaseManager *getInstance();
    ~DatabaseManager();
    bool registerItem(QString id, QString nome, unsigned int categoria, long double preco, int quantidade);
    QList<Item> getItens();
    bool setQuantidade(int novaQuantidade, QString IdDoItem);
    void addItem();
    int size();

private:
    DatabaseManager(DatabaseConnection *databaseConnection);

    void createEstoqueTable();
    void throwError(QSqlQuery *query);

    static DatabaseManager *m_databaseManager;

    DatabaseConnection *m_databaseConnetion = nullptr;
    QSqlDatabase *m_database;

    QMutex estoqueMutex;

    const QString CREATE_ESTOQUE_TABLE_QUERY = "CREATE TABLE estoque("
                                               "id TEXT NOT NULL PRIMARY KEY,"
                                               "nome TEXT NOT NULL,"
                                               "categoria INTEGER,"
                                               "preco REAL,"
                                               "quantidade INTEGER NOT NULL);";

    const QString REGISTER_ITEM_QUERY = "INSERT INTO estoque("
                                        "id, nome, categoria, preco, quantidade) "
                                        "VALUES(:id, :nome, :categoria, :preco, :quantidade);";

    const QString GET_ITENS_QUERY = "SELECT * FROM estoque;";

    const QString SET_QUANTIDADE_QUERY = "UPDATE estoque SET quantidade = :quantidade WHERE id = :id";

    const QString GET_SIZE_QUERY = "SELECT COUNT() FROM estoque;";

};

#endif // DATABASE_H
