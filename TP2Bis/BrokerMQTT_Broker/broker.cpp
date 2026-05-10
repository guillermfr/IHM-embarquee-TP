#include "broker.h"

Broker::Broker(QObject *parent)
    : QObject{parent}, server(new QTcpServer(this))
{
    connect(server, &QTcpServer::newConnection, this, &Broker::onNewConnection);

}

// Démarrage du Broker pour l'écoute (listen)
void Broker::start(quint16 port)
{
    if(!server->listen(QHostAddress::Any, port)) {
        qDebug() << "Broker failed to start:" << server->errorString();
        return;
    }

    qDebug() << "Broker listening to port" << port;
}

// Action à faire à chaque nouvelle connection => ajout des fonction onReadyRead et onDisconnected
void Broker::onNewConnection()
{
    while (server->hasPendingConnections()) {
        QTcpSocket *newSubscriber = server->nextPendingConnection();
        qDebug() << "New connection from" << newSubscriber->peerAddress().toString() << ":" << newSubscriber->peerPort();

        connect(newSubscriber, &QTcpSocket::readyRead, this, &Broker::onReadyRead);
        connect(newSubscriber, &QTcpSocket::disconnected, this, &Broker::onDisconnected);

        qDebug() << "New subscription";
    }
}

// Lecture des trames TCP
void Broker::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    buffers[socket].append(socket->readAll());

    while (buffers[socket].contains('\n')) {
        int index = buffers[socket].indexOf('\n');

        QByteArray raw = buffers[socket].left(index);
        buffers[socket].remove(0, index + 1);

        QString msg = QString::fromUtf8(raw).trimmed();
        handleMessage(socket, msg);
    }
}

// Gestion des types de message PUBLISH/SUBSCRIBE
void Broker::handleMessage(QTcpSocket *socket, const QString &message)
{
    QStringList parts = message.split(":", Qt::SkipEmptyParts);
    if(parts.isEmpty()) return;

    QString command = parts[0].toUpper();
    if(command == "PUBLISH" && parts.size() >= 3 ) {
        QString topic = parts[1].toUpper();
        QString payload = parts[2];
        publishMessage(topic, payload);
    }
    else if(command == "SUBSCRIBE" && parts.size() == 2) {
        QString topic = parts[1].toUpper();
        subscribeSocket(socket, topic);
    }
    else {
        qDebug() << "Unknown command:" << command;
    }
}

// Envoi des messages au listener (en vérifiant qu'il est bien subscribed au topic)
void Broker::publishMessage(const QString &topic, const QString &payload)
{
    QString message = QString("MESSAGE %1 %2:").arg(topic, payload);
    if(topicSubscribers.contains(topic)) {
        foreach (QTcpSocket *sub, topicSubscribers[topic]) {
            if(sub->state() == QAbstractSocket::ConnectedState) {
                sub->write(message.toUtf8());
                sub->flush();
            }
        }
    }
}

// Ajout d'un nouveau subscriber
void Broker::subscribeSocket(QTcpSocket *socket, const QString &topic)
{
    topicSubscribers[topic].append(socket);
    QString response = QString("Subscribed to %1").arg(topic);
    socket->write(response.toUtf8());
    socket->flush();
    qDebug() << "Socket" << socket->peerAddress().toString() << ":" << socket->peerPort() << "subscribed to" << topic;
}

// Commande à faire lors de la déconnexion d'un socket
void Broker::onDisconnected()
{
    QTcpSocket *subscriber = qobject_cast<QTcpSocket*>(sender());
    if(!subscriber) return;

    for (auto it = topicSubscribers.begin(); it != topicSubscribers.end(); ++it) {
        it.value().removeAll(subscriber);
    }
    subscriber->deleteLater();

    qDebug() << "Subscriber disconnected";
}