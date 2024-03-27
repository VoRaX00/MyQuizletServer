#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:
    void newMessage(QTcpSocket*, QString);
private slots:
    void newConnection();
    void onReadyRead();
    void onNewMessage(QTcpSocket* socket, const QString& message);

private:
    QString getAnswer(QString message);

private:
    QTcpServer* server;
    QList<QTcpSocket*>sockets;
};

#endif // SERVER_H
