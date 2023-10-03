#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDir>

class DatabaseConnection
{
public:
    static DatabaseConnection *getInstance();
    bool openDatabaseConnection();
    void closeDatabaseConnection();
    QSqlDatabase *database();
private:
    DatabaseConnection();
    static DatabaseConnection *m_databaseConnection;

    QSqlDatabase m_database;
};

#endif // DATABASECONNECTION_H
