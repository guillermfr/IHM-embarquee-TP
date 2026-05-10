#include "mainwindow.h"

#include <QApplication>
#include "broker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    // Démarrage du broker sur le port 1234
    Broker broker;
    broker.start(1234);

    w.show();

    return QCoreApplication::exec();
}
