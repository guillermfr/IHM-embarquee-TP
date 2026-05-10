/**
 * @file loginbackend.h
 * @brief Login flow controller for the chat client.
 */
#pragma once

#include <QObject>
#include <QJsonObject>
#include <QTcpSocket>
#include "tcpmanager.h"

/**
 * @class LoginBackend
 * @brief Builds and sends login requests, and exposes the authenticated username.
 */
class LoginBackend : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Creates a login backend bound to a TCP transport.
     * @param tcpManager TCP manager used to send requests and receive responses.
     * @param parent Optional QObject parent.
     */
    explicit LoginBackend(TcpManager *tcpManager, QObject *parent = nullptr);

    /**
     * @brief Starts the login flow for the given server and credentials.
     * @param ip_address Server IPv4 address.
     * @param port Server TCP port.
     * @param username Account username.
     * @param password Account password.
     */
    Q_INVOKABLE void login(const QString &ip_address, const QString &port, const QString &username, const QString &password);
    /**
     * @brief Returns the username used for the most recent login request.
     * @return Current username, or an empty string if no login was attempted.
     */
    QString currentUsername() const;

private slots:
    /**
     * @brief Sends the pending login request once the socket is connected.
     */
    void onConnected();
    /**
     * @brief Handles a successful login response from the server.
     */
    void onLoginSuccess();
    /**
     * @brief Handles a failed login response from the server.
     * @param error Human-readable rejection reason.
     */
    void onLoginFailed(const QString &error);

signals:
    /**
     * @brief Emitted when the server accepts the login.
     */
    void loginSuccess();
    /**
     * @brief Emitted when the server rejects the login.
     * @param error Human-readable rejection reason.
     */
    void loginFailed(const QString &error);

private:
    /**
     * @brief Serializes and sends the pending login request as JSON.
     */
    void sendLoginRequest();

    TcpManager *tcpManager;
    QJsonObject m_pendingRequest; ///< Stored login request payload.
    bool m_requestPending = false;
    QString m_username;
};