#include <QCoreApplication>
#include <QTimer>

#include "capteur.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Capteur capteur;

    capteur.addCaptor("temperature", "red");
    capteur.addCaptor("humidity", "blue");
    capteur.addCaptor("pression", "green");

    capteur.connectToServer("127.0.0.1", 1234);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&capteur]() {
        capteur.sendData();
    });
    timer.start(80);

    return QCoreApplication::exec();
}
