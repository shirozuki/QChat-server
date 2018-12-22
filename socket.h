#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>

class Socket : public QTcpSocket
{
    Q_OBJECT
public:
    Socket(qintptr sd, QObject *parent = 0);
    ~Socket();
signals:
    void SocketReadyRead(Socket *);
    void StateChanged(Socket *, int);
};

#endif // SOCKET_H
