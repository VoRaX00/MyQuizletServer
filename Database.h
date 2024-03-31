#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

    bool createConnection();
    bool insertIntoUsersTable(const QVariantList& data);
    bool insertIntoTermsTable(const QVariantList& data);
    bool insertIntoQuizletsSTable(const QVariantList& data);

signals:

private:
    void closeDataBase();
    bool createUsersTable();
    bool createTermsTable();
    bool createQuizletsTable();

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
