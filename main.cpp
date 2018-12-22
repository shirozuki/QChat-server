#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    quint16 port = 9090;
    QCoreApplication a(argc, argv);

    Server srv;
    if(!srv.startServer(port))
    {
        qDebug() << srv.errorString();
        exit(EXIT_FAILURE);
    }

    return a.exec();
}
