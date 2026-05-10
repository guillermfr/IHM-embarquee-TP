/**
 * @file tcpmanager.h
 * @brief TCP transport and message parser for the chat protocol.
 */
#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QAbstractSocket>

/**
 * @class TcpManager
 * @brief Owns the TCP socket, sends raw JSON messages, and parses incoming protocol frames.
 */
class TcpManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Creates a TCP manager with an internal socket.
     * @param parent Optional QObject parent.
     */
    explicit TcpManager(QObject *parent = nullptr);
    /**
     * @brief Opens a connection to the given server.
     * @param host Server hostname or IP address.
     * @param port Server TCP port.
     */
    void connectToServer(const QString &host, int port);
    /**
     * @brief Sends a single line JSON frame to the server.
     * @param message Serialized JSON payload, typically newline-terminated.
     */
    void sendMessage(const QString &message);
    /**
     * @brief Closes the current TCP connection and clears the input buffer.
     */
    void disconnectFromServer();
    /**
     * @brief Returns the current socket state.
     * @return Current QTcpSocket state.
     */
    QAbstractSocket::SocketState state() const;

signals:
    /**
     * @brief Emitted when the socket connects successfully.
     */
    void connected(); // emitted when socket connects

    /**
     * @brief Emitted when the server accepts authentication.
     */
    void loginSuccess();
    /**
     * @brief Emitted when the server rejects authentication.
     * @param reason Rejection reason returned by the server.
     */
    void loginFailed(const QString &reason);
    /**
     * @brief Emitted when a history payload is received.
     * @param users JSON array of known users.
     * @param messages JSON array of stored messages.
     */
    void historyReceived(QJsonArray users, QJsonArray messages);
    /**
     * @brief Emitted when a live chat message is received.
     * @param messageContent Message body.
     * @param senderId Sender user id.
     * @param receiverId Receiver user id, or -1 for the global channel.
     */
    void chatMessageReceived(QString messageContent, int senderId, int receiverId);

private slots:
    /**
     * @brief Handles the socket connected event.
     */
    void onConnected();
    /**
     * @brief Reads and parses all complete newline-delimited protocol frames.
     */
    void onReadyRead();
    /**
     * @brief Logs socket errors.
     * @param error Socket error code.
     */
    void onError(QAbstractSocket::SocketError error);

private:
    QTcpSocket *socket;
    QByteArray buffer;
};