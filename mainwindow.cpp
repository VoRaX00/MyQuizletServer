#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer(this);

    db = new Database();
    db->createConnection();

    setupUsersModel(QStringList() << "id" << "email" << "password");
    setupQuizletsModel(QStringList() << "id" << "name" << "id_user");
    setupTermsModel(QStringList() << "id" << "term" << "definition" << "id_quizlet");

    createUI();
}

void MainWindow::setupUsersModel(const QStringList &headers)
{
    modelUsers = new QSqlQueryModel(this);

    modelUsers->setQuery("SELECT * FROM Users");

    for(int i=0; i < modelUsers->columnCount(); i++){
        modelUsers->setHeaderData(i, Qt::Horizontal, headers[i]);
    }
}

void MainWindow::setupQuizletsModel(const QStringList& headers)
{
    modelQuizlets = new QSqlQueryModel(this);

    modelQuizlets->setQuery("SELECT * FROM Quizlets");

    for(int i=0; i < modelQuizlets->columnCount(); i++){
        modelQuizlets->setHeaderData(i, Qt::Horizontal, headers[i]);
    }
}

void MainWindow::setupTermsModel(const QStringList &headers)
{
    modelTerms = new QSqlQueryModel(this);

    modelTerms->setQuery("SELECT * FROM Terms");

    for(int i=0; i < modelTerms->columnCount(); i++){ //устанавливаем заголовки
        modelTerms->setHeaderData(i, Qt::Horizontal, headers[i]);
    }
}

void MainWindow::createUI()
{
    ui->tableViewUsers->setModel(modelUsers);
    ui->tableViewUsers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewUsers->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableViewUsers->resizeColumnsToContents();
    ui->tableViewUsers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewUsers->horizontalHeader()->setStretchLastSection(true);

    ui->tableViewQuizlets->setModel(modelQuizlets);
    ui->tableViewQuizlets->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewQuizlets->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableViewQuizlets->resizeColumnsToContents();
    ui->tableViewQuizlets->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewQuizlets->horizontalHeader()->setStretchLastSection(true);

    ui->tableViewTerms->setModel(modelTerms);
    ui->tableViewTerms->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewTerms->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableViewTerms->resizeColumnsToContents();
    ui->tableViewTerms->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewTerms->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
