#include "socket.h"

Socket::Socket(qintptr sd, QObject *parent) : QTcpSocket(parent)
{
    setSocketDescriptor(sd);
    connect(this, &Socket::readyRead, [&]()
    {
        emit SocketReadyRead(this);
    });

    connect(this, &Socket::stateChanged, [&](int sock)
    {
        emit StateChanged(this, sock);
    });
}

Socket::~Socket()
{

}
