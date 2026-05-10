#include "client.h"

#include <QDebug>

Client::Client(QObject *parent)
    : QObject{parent}, socket(new QUdpSocket(this))
{
    connect(socket, &QUdpSocket::readyRead, this, &Client::onReadyRead);
}

void Client::start(const QString &host, int port) {
    serverAddress = QHostAddress(host);
    serverPort = port;

    if (!socket->bind(QHostAddress(QHostAddress::AnyIPv4), quint16(0))) {
        qDebug() << "Bind failed:" << socket->errorString();
        return;
    }

    qDebug() << "Client listening on port" << socket->localPort();

    QByteArray msg = "SUBSCRIBE!";
    socket->writeDatagram(msg, serverAddress, serverPort);

    qDebug() << "SUBSCRIBE sent to server";
}

void Client::onReadyRead()
{
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(datagram.data(), datagram.size(),
                             &sender, &senderPort);

        QString message = QString::fromUtf8(datagram);

        qDebug() << "Received from" << sender.toString()
                 << ":" << senderPort << "->" << message;

        emit messageReceived(message);
    }
}