#include <QCoreApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;

    server.start(1234, 1234);

    return QCoreApplication::exec();
}
