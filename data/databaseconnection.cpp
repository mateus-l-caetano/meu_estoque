#include "databaseconnection.h"

DatabaseConnection *DatabaseConnection::m_databaseConnection = nullptr;

DatabaseConnection *DatabaseConnection::getInstance()
{
    if(m_databaseConnection == nullptr) {
        m_databaseConnection = new DatabaseConnection();
    }

    return m_databaseConnection;
}

DatabaseConnection::DatabaseConnection()
{
}

bool DatabaseConnection::openDatabaseConnection()
{
    QDir databasePath;
    QString path = databasePath.currentPath()+"/meu_estoque.db";

    this->m_database = QSqlDatabase::addDatabase("QSQLITE");
    this->m_database.setDatabaseName(path);

    if(!this->m_database.open()) {
        std::string databaseErrorMessage = this->m_database.lastError().text().toStdString();
        std::string errorMessage = "não foi possível acessar o banco de dados: " + databaseErrorMessage;

        throw std::runtime_error(errorMessage);
    } else {
        return true;
    }
}

void DatabaseConnection::closeDatabaseConnection()
{
    m_database.close();
}

QSqlDatabase *DatabaseConnection::database()
{
    return &m_database;
}
