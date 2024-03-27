#include "Server.h"

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
    qDebug() << data;

    emit newMessage(client, getAnswer(data));
}

void Server::onNewMessage(QTcpSocket *socket, const QString &message)
{
    socket->write(message.toUtf8());
}

QString Server::getAnswer(QString message)
{
    //прописать ответы на запросы пользователя
}
