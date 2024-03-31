#include "Server.h"
#include <QRegularExpression>

Server::Server(QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);
    if(server->listen(QHostAddress::Any, 44333)){
        qDebug() << "listening";
    }

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(this, SIGNAL(newMessage(QTcpSocket*, QString)), this, SLOT(onNewMessage(QTcpSocket*, QString)));
}

void Server::newConnection()
{
    auto socket = server->nextPendingConnection();
    if(socket == nullptr)
        return;
    qDebug() << "new connection";
    sockets.append(socket);
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Server::onReadyRead()
{
    auto client = (QTcpSocket*)sender();
    if(client == nullptr)
        return;

    QString data = client->readAll();
    data = getAnswer(data);
    emit newMessage(client, data);
}

void Server::onNewMessage(QTcpSocket *socket, const QString &message)
{
    socket->write(message.toUtf8());
}

void Server::disconnected(){
    const auto client = (QTcpSocket*)(sender());
    if(client == nullptr)
        return;

    sockets.removeIf([=](QTcpSocket* sock){
        return sock == client;
    });
    qDebug() << "client disconnected";
}

QString Server::getAnswer(QString message)
{
    //прописать ответы на запросы пользователя
    if(isLogin(message)){
        QRegularExpression exp("LOGIN:([a-zA-Z0-9_]+) PASSWORD:([a-zA-Z0-9_]+)");
        QRegularExpressionMatch match = exp.match(message);
        QString login = match.captured(1);
        QString password = match.captured(2);
        qDebug() << login << " " << password;
        return "ans";
    }
    else if(isRegistration(message)){
        QRegularExpression exp("LOGIN:([a-zA-Z0-9_]+) PASSWORD:([a-zA-Z0-9_]+)");
        QRegularExpressionMatch match = exp.match(message);
        QString login = match.captured(1);
        QString password = match.captured(2);
        qDebug() << login << " " << password;
        // добавить проверку на содержание в бд и если нет, то добавить
        return "ans";
    }

    qDebug() << "regular don't work";
    return "";
}

void Server::loginUser(const QString &login, const QString &password)
{

}

void Server::registrationUser(const QString &login, const QString &password)
{

}

bool Server::isLogin(const QString &message)
{
    //QRegularExpression exp("LOGIN:([a-zA-Z0-9_]+) PASSWORD:([a-zA-Z0-9_]+)");
    return std::find(message.begin(), message.end(), "_LOGIN_") != message.end(); //exp.match(message).hasMatch();
}

bool Server::isRegistration(const QString &message)
{
    return std::find(message.begin(), message.end(), "_REGISTRATION_") != message.end();
}

bool Server::isQuizlet(const QString &message) //проверка для добавления пользователем quizlet-a
{
    return std::find(message.begin(), message.end(), "_QUIZLET_") != message.end();
}
