/**
 * @file tcpmanager.cpp
 * @brief Implementation of the TCP transport and protocol parser.
 */

#include "tcpmanager.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

//TODO: errorOccurred

/** @copydoc TcpManager::TcpManager */
TcpManager::TcpManager(QObject *parent) : QObject{parent}, socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &TcpManager::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpManager::onReadyRead);
    connect(socket, &QAbstractSocket::errorOccurred, this, &TcpManager::onError);
}

/** @copydoc TcpManager::connectToServer */
void TcpManager::connectToServer(const QString &host, int port) {
    // Non‑blocking – just initiate connection
    socket->connectToHost(host, port);
}

/** @copydoc TcpManager::disconnectFromServer */
void TcpManager::disconnectFromServer() {
    buffer.clear();

    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->disconnectFromHost();
        socket->close();
    }
}

/** @copydoc TcpManager::state */
QAbstractSocket::SocketState TcpManager::state() const {
    return socket->state();
}

/** @copydoc TcpManager::onConnected */
void TcpManager::onConnected() {
    emit connected();
    qDebug() << "TcpManager Connected to server";
}

/** @copydoc TcpManager::onError */
void TcpManager::onError(QAbstractSocket::SocketError error) {
    Q_UNUSED(error)
    qDebug() << "Socket error:" << socket->errorString();
    // Could emit an error signal here if needed
}

/** @copydoc TcpManager::onReadyRead */
void TcpManager::onReadyRead() {
    buffer.append(socket->readAll());

    // Process all complete lines (terminated by '\n')
    while (buffer.contains('\n')) {
        int index = buffer.indexOf('\n');
        QByteArray raw = buffer.left(index);
        buffer.remove(0, index + 1);

        QString msg = QString::fromUtf8(raw).trimmed();
        if (!msg.isEmpty()) {
            qDebug() << "Received data from Server:" << msg;
            //TODO: mettre plusieurs types de signaux pour différencier les types de messages => login, chat
            
			QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());
			if (!doc.isObject())
				return;

			QJsonObject obj = doc.object();
			QString type = obj.value("type").toString();
            QJsonObject content = obj.value("content").toObject();
            qDebug() << "Message type:" << type << ", content:" << content;

			if (type == "login_success") {
				// Message received on successful login
				emit loginSuccess();
			} else if (type == "login_failed") {
				// Message received on failed login
				QString reason = obj.value("reason").toString("Unknown error");
				emit loginFailed(reason);
			} else if (type == "history") {
				// Message received with chat history

				// {"type":"history","content":{"users":[{"id":0,"name":"admin"}],"messages":[{"sender":0,"receiver":-1,"message":"Hello"}]}}
				QJsonArray users = content.value("users").toArray();
				QJsonArray messages = content.value("messages").toArray();

				emit historyReceived(users, messages);
			} else if (type == "message") {
				QString messageContent = content.value("message").toString();
				int senderId = content.value("sender").toInt();
				int receiverId = content.value("receiver").toInt();

				qDebug() << "Chat message received:" << messageContent << "(sender:" << senderId << ", receiver:" << receiverId << ")";

				emit chatMessageReceived(messageContent, senderId, receiverId);
			}
        }
    }
}

/** @copydoc TcpManager::sendMessage */
void TcpManager::sendMessage(const QString &message) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(message.toUtf8());
        socket->flush();   // optional, ensures immediate send
        qDebug() << "TcpManager sent" << message;
    } else {
        qWarning() << "Cannot send – not connected";
    }
}