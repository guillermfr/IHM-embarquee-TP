/**
 * @file loginbackend.cpp
 * @brief Implementation of the login backend.
 */

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

#include "loginbackend.h"
#include "tcpmanager.h"

/** @copydoc LoginBackend::LoginBackend */
LoginBackend::LoginBackend(TcpManager *tcpManager, QObject *parent) : QObject(parent), tcpManager(tcpManager) {
    connect(tcpManager, &TcpManager::loginSuccess, this, &LoginBackend::onLoginSuccess);
    connect(tcpManager, &TcpManager::loginFailed, this, &LoginBackend::onLoginFailed);
    connect(tcpManager, &TcpManager::connected, this, &LoginBackend::onConnected);
}

/** @copydoc LoginBackend::login */
void LoginBackend::login(const QString &ip_address, const QString &port, const QString &username, const QString &password) {
    m_username = username;

    // Build the JSON request and store it
    QJsonObject content;
    content["name"] = username;
    content["password"] = password;

    QJsonObject request;
    request["type"] = "login";
    request["content"] = content;

    m_pendingRequest = request;
    m_requestPending = true;

    // If already connected, send immediately; otherwise connect first
    if (tcpManager->state() == QAbstractSocket::ConnectedState) {
        sendLoginRequest();
    } else {
        tcpManager->connectToServer(ip_address, port.toInt());
        // Wait for onConnected() to send the request
    }
}

/** @copydoc LoginBackend::onConnected */
void LoginBackend::onConnected() {
    if (m_requestPending) {
        sendLoginRequest();
        m_requestPending = false;
    }
}

/** @copydoc LoginBackend::sendLoginRequest */
void LoginBackend::sendLoginRequest() {
    QJsonDocument doc(m_pendingRequest);
    QString jsonString = doc.toJson(QJsonDocument::Compact) + "\n";
    qDebug() << "Login request:" << jsonString;
    tcpManager->sendMessage(jsonString);
}

/** @copydoc LoginBackend::onLoginSuccess */
void LoginBackend::onLoginSuccess() {
    qDebug() << "Login successful";
    emit loginSuccess();
}

/** @copydoc LoginBackend::onLoginFailed */
void LoginBackend::onLoginFailed(const QString &message) {
    qDebug() << "Login failed:" << message;
}

/** @copydoc LoginBackend::currentUsername */
QString LoginBackend::currentUsername() const {
    return m_username;
}