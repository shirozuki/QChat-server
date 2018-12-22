#include "server.h"
#include <QDebug>
#include "socket.h"
#include <QTextStream>

Server::Server(QObject *parent) : QTcpServer(parent)
{

}

Server::~Server()
{

}

bool Server::startServer(quint16 port)
{
    return listen(QHostAddress::Any, port);
}

void Server::incomingConnection(qintptr sd)
{
    auto socket = new Socket(sd, this);
    sockList << socket;

    connect(socket, &Socket::SocketReadyRead, [&](Socket *sock)
    {
        QTextStream textStream(sock);
        auto text = textStream.readAll();

        for(auto i: sockList)
        {
            QTextStream textStream2(i);
            textStream2 << text;
            i->flush();
        }
    });

    connect(socket, &Socket::StateChanged, [&](Socket *sock, int state)
    {
        if(state == QTcpSocket::UnconnectedState)
        {
            sockList.removeOne(sock);
        }
    });
}
