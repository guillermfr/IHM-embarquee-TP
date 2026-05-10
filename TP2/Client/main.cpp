#include "mainwindow.h"
#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Client client;

    QObject::connect(&client, &Client::messageReceived,
                     &w, &MainWindow::updateGraph);

    client.start("127.0.0.1", 1234);

    w.show();

    return a.exec();
}