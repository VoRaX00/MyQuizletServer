#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQueryModel>

#include "Database.h"
#include "Server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool createConnection();

private slots:

private:
    void setupUsersModel(const QStringList& headers);
    void setupQuizletsModel(const QStringList& headers);
    void setupTermsModel(const QStringList& headers);
    void createUI();

private:
    Ui::MainWindow *ui;
    Database* db;
    Server* server;
    QSqlQueryModel* modelUsers;
    QSqlQueryModel* modelQuizlets;
    QSqlQueryModel* modelTerms;

};
#endif // MAINWINDOW_H
