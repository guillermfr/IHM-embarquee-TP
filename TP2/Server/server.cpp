#include "server.h"

Server::Server(QObject *parent)
    : QObject{parent}, TCPserver(new QTcpServer(this)), UDPsocket(new QUdpSocket(this))
{
    connect(TCPserver, &QTcpServer::newConnection, this, &Server::onNewConnection);
    connect(UDPsocket, &QUdpSocket::readyRead, this, &Server::onReadyReadUDP);
}

// Démarrage du Server pour l'écoute (listen)
void Server::start(int TCPport, int UDPport)
{
    if(!TCPserver->listen(QHostAddress::LocalHost, TCPport)) {
        qDebug() << "Broker failed to start:" << TCPserver->errorString();
        return;
    }

    if(!UDPsocket->bind(QHostAddress::LocalHost, UDPport)) {
        qDebug() << "UDP bind failed:" << UDPsocket->errorString();
        return;
    }

    qDebug() << "Broker listening to TCP port" << TCPport;
    qDebug() << "Broker listening to UDP port" << UDPport;
}

// Action à faire à chaque nouvelle connection => ajout des fonction onReadyRead et onDisconnected
void Server::onNewConnection()
{
    while (TCPserver->hasPendingConnections()) {
        QTcpSocket *newCapteur = TCPserver->nextPendingConnection();
        qDebug() << "New connection from" << newCapteur->peerAddress().toString() << ":" << newCapteur->peerPort();

        connect(newCapteur, &QTcpSocket::readyRead, this, &Server::onReadyReadTCP);
        // connect(newCapteur, &QTcpSocket::disconnected, this, &Server::onDisconnected);

        qDebug() << "New subscription";
    }
}

// Lecture des trames TCP
void Server::onReadyReadTCP()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QByteArray buffer;
    buffer.append(socket->readAll());

    int index = buffer.indexOf('!');

    QByteArray raw = buffer.left(index);
    buffer.remove(0, index + 1);

    if(QString::fromUtf8(raw).trimmed() == "REGISTER_SENSOR") {
        capteurs.clear();

        while(!buffer.isEmpty()) {

            index = buffer.indexOf('!');

            raw = buffer.left(index);
            buffer.remove(0, index + 1);

            QString msg = QString::fromUtf8(raw).trimmed();
            QStringList data = msg.split(":");

            qDebug() << "type : " + data[0] + " / couleur : " + data[1];

            capteurs.insert(data[0], data[1]);
        }
    }
}

// Lectures des datagrames UDP et renvoi au client
void Server::onReadyReadUDP()
{
    while (UDPsocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(UDPsocket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        UDPsocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString message = QString::fromUtf8(datagram);
        QString senderKey = sender.toString() + ":" + QString::number(senderPort);

        if(message.startsWith("SUBSCRIBE")) {
            clients.insert(senderKey);
            qDebug() << "New client subscribed: " << senderKey;
        }
        else if(message.startsWith("DATA")) {
            qDebug() << "UDP received from" << senderKey << "->" << message;
            for (const QString &client : std::as_const(clients)) {
                QStringList parts = client.split(":");
                QHostAddress addr(parts[0]);
                quint16 port = parts[1].toUShort();

                UDPsocket->writeDatagram(datagram, addr, port);
                qDebug() << "UDP sent to" << client;
            }
        }
    }
}