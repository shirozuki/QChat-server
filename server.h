#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Socket;

class Server : public QTcpServer
{
public:
    Server(QObject *parent = 0);
    bool startServer(quint16 port);
    ~Server();

private:
    QList<Socket*> sockList;

protected:
    void incomingConnection(qintptr sd);
};

#endif // SERVER_H
