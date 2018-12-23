#include <QDebug>
#include <QTextStream>
#include "socket.h"
#include "server.h"

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
    qDebug() << "Klient nr" << sd << "polaczyl sie.";
    auto socket = new Socket(sd, this);
    sockList << socket;

    for(auto i: sockList)
    {
        QTextStream textStream(i);
        textStream << "Serwer: klient nr " << sd << " polaczyl sie.";
        i->flush();
    }

    connect(socket, &Socket::SocketReadyRead, [&](Socket *sock)
    {
        qDebug() << "Wiadomość przychodząca od" << sock->socketDescriptor();
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
        qDebug() << "Zmiana stanu połączenia klienta!";
        qDebug() << "Klient" << sock->socketDescriptor() << "rozłączył się.";
        if(state == QTcpSocket::UnconnectedState)
        {
            sockList.removeOne(sock);
            for(auto i: sockList)
            {
                QTextStream textStream(i);
                {
                    textStream << "Serwer: klient nr "
                               << sock->socketDescriptor()
                               << " rozlaczyl sie.";
                    i->flush();
                }
            }
        }
    });
}
