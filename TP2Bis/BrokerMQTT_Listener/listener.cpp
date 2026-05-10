#include "listener.h"

Listener::Listener(QObject *parent)
    : QObject{parent}, socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &Listener::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Listener::onReadyRead);
}

// Connexion au broker
void Listener::connectToBroker(const QString &host, int port)
{
    socket->connectToHost(host, port);
    if(!socket->waitForConnected(5000)) {
        qDebug() << "TCP Connection failed: " << socket->errorString();
    }
}

// Abonnement à un topic
void Listener::subscribeToTopic(QString topic)
{
    QString message = "SUBSCRIBE:" + topic + "\n";
    socket->write(message.toUtf8());
    socket->flush();
    qDebug() << "Subscriber subscribed " << message;
}

// Message affiché lors de la connexion
void Listener::onConnected()
{
    qDebug() << "Listener Connected to broker";
}

// Lorsqu'un message est reçu, on le parse proprement (dans le cas où plusieurs seraient arrivés en même temps) et on émet un signal
// pour l'afficher sur l'interface graphique
void Listener::onReadyRead()
{
    buffer.append(socket->readAll());

    qDebug() << "buffer: " << buffer;

    while (buffer.contains(':')) {
        int index = buffer.indexOf(':');

        QByteArray raw = buffer.left(index);
        buffer.remove(0, index + 1);

        QString msg = QString::fromUtf8(raw).trimmed();

        qDebug() << "Received data from MQTT Broker: " + msg;
        emit messageReceived(msg);
    }
}