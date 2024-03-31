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
    QRegularExpression exp("^([A-Za-z0-9_]+)\:([A-Za-z0-9_]+)$");

    if(exp.match(message).hasMatch()){
        auto match = exp.match(message).captured(0);
        QString login = match.remove(match.indexOf(":"), match.indexOf(" "));
        QString password = match.remove(match.indexOf(":"), match.length()-1);
        qDebug() << login << " " << password;
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
