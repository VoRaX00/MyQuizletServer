#include "Database.h"

Database::Database(QObject *parent)
    : QObject{parent}
{

}

bool Database::createConnection()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setUserName("postgres");
    db.setPassword("1324");
    db.setDatabaseName("Quizlet");

    if(!db.open()){
        qDebug() << "Error! Can't open database" << db.lastError().text();
        return false;
    }
    return true;
}

bool Database::insertIntoUsersTable(const QVariantList &data)
{
    QSqlQuery query;
    QString request = QString("INSERT INTO Users (email, password) "
                              "VALUES (%1, %2)").arg(data[0].toString()).arg(data[1].toString());

    if(!query.exec(request)){
        qWarning() << "Error insert into Users";
        return false;
    }
    return true;
}

bool Database::insertIntoTermsTable(const QVariantList &data)
{
    QSqlQuery query;
    QString request = QString("INSERT INTO Terms (term, definition, id_quizlet) "
                              "VALUES (%1, %2, %3)").arg(data[0].toString()).arg(data[1].toString()).arg(data[2].toUInt());

    if(!query.exec(request)){
        qWarning() << "Error insert into Terms";
        return false;
    }
    return true;
}

bool Database::insertIntoQuizletsSTable(const QVariantList &data)
{
    QSqlQuery query;
    QString request = QString("INSERT INTO Quizlets (name, id_user) "
                              "VALUES (%1, %2)").arg(data[0].toString()).arg(data[1].toString());

    if(!query.exec(request)){
        qWarning() << "Error insert into Quizlets";
        return false;
    }
    return true;
}

void Database::closeDataBase()
{
    db.close();
}

bool Database::createUsersTable()
{
    QStringList tables = db.tables();
    QString name = "Users";

    if(std::find(tables.begin(), tables.end(), name) != tables.end()){
        qDebug() << "Table Users created";
        return true;
    }

    QSqlQuery query;
    QString request = QString("CREATE TABLE %1 ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "email TEXT NOT NULL, "
                              "password TEXT NOT NULL );").arg(name);

    if(!query.exec(request)){
        qWarning() << "Table Users can't create";
        return false;
    }

    qDebug() << "Table Users create";
    return true;
}

bool Database::createTermsTable()
{
    QStringList tables = db.tables();
    QString name = "Terms";

    if(std::find(tables.begin(), tables.end(), name) != tables.end()){
        qDebug() << "Table Terms created";
        return true;
    }

    QSqlQuery query;
    QString request = QString("CREATE TABLE %1 ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "term TEXT NOT NULL, "
                              "definition TEXT NOT NULL,"
                              "id_quizlet INTEGER NOT NULL, );").arg(name);

    if(!query.exec(request)){
        qWarning() << "Table Terms can't create";
        return false;
    }

    qDebug() << "Table Terms create";
    return true;
}

bool Database::createQuizletsTable()
{
    QStringList tables = db.tables();
    QString name = "Quizlets";

    if(std::find(tables.begin(), tables.end(), name) != tables.end()){
        qDebug() << "Table Quizlets created";
        return true;
    }

    QSqlQuery query;
    QString request = QString("CREATE TABLE %1 ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "name TEXT NOT NULL, "
                              "id_user INTEGER NOT NULL, );").arg(name);

    if(!query.exec(request)){
        qWarning() << "Table Quizlets can't create";
        return false;
    }

    qDebug() << "Tables Quizlets create";
    return true;
}
