#include "publisher.h"

Publisher::Publisher(QObject *parent)
    : QObject{parent}, socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &Publisher::onConnected);
}

// Connexion au breaker
void Publisher::connectToBroker(const QString &host, int port)
{
    socket->connectToHost(host, port);
    if(!socket->waitForConnected(5000)) {
        qDebug() << "TCP Connection failed: " << socket->errorString();
    }
}

// Message à afficher lors de la connexion
void Publisher::onConnected()
{
    qDebug() << "Publisher Connected to broker";
}

// Envoi d'une valeur aléatoire sur le topic "TEMP"
// On pourrait créer une enum avec tous les topics existant pour rendre le code plus scalable
void Publisher::publishTemperature(float temperature)
{
    QString message = "PUBLISH:TEMP:" + QString::number(temperature) + "\n";
    socket->write(message.toUtf8());
    socket->flush();
    qDebug() << "Publisher published " << message;
}