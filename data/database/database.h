#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDir>
#include <QtConcurrent>

#include "../../entity/item.h"

class DatabaseManager : public QThread
{
    Q_OBJECT

public:
    void run() override;
    static DatabaseManager *getInstance();
    ~DatabaseManager();
    bool registerItem(QString id, QString nome, unsigned int categoria, long double preco, int quantidade);
    QList<Item> getItens();
    void addItem();
    int size();

private:
    DatabaseManager();
    void openDatabase();
    void createEstoqueTable();
    void throwError(QSqlQuery *query);

    QSqlDatabase m_database;
    static DatabaseManager *m_databaseManager;

    QMutex estoqueMutex;

    const QString REGISTER_ITEM_QUERY = "INSERT INTO estoque("
                                        "id, nome, categoria, preco, quantidade) "
                                        "VALUES(:id, :nome, :categoria, :preco, :quantidade);";

    const QString GET_ITENS_QUERY = "SELECT * FROM estoque;";

};

#endif // DATABASE_H
