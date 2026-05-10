/**
 * @file mainbackend.h
 * @brief Chat history backend for the main chat page.
 */
#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QJsonArray>
#include <QMap>

class TcpManager;

/**
 * @class MainBackend
 * @brief Stores chat history, routes messages to conversation buckets, and exposes the data to QML.
 */
class MainBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonArray users READ getUsers NOTIFY historyUpdated) //!< Users returned by the latest history payload.
    Q_PROPERTY(QJsonArray globalMessages READ getGlobalMessages NOTIFY historyUpdated) //!< Messages displayed in the global channel.
    Q_PROPERTY(QString currentUsername READ currentUsername NOTIFY currentUsernameChanged) //!< Current authenticated username.

public:
    /**
     * @brief Creates a chat backend bound to a TCP transport.
     * @param tcpManager TCP manager used for network communication.
     * @param parent Optional QObject parent.
     */
    explicit MainBackend(TcpManager *tcpManager, QObject *parent = nullptr);

    /**
     * @brief Sets the authenticated username and refreshes the local user lookup.
     * @param username Logged-in username.
     */
    void setCurrentUsername(const QString &username);
    /**
     * @brief Replaces the cached history with the payload received from the server.
     * @param users JSON array of known users.
     * @param messages JSON array of messages from the server.
     */
    void onHistoryReceived(const QJsonArray &users, const QJsonArray &messages);
    /**
     * @brief Stores a live chat message in the appropriate history bucket.
     * @param messageContent Message body.
     * @param senderId Sender user id.
     * @param receiverId Receiver user id, or -1 for the global channel.
     */
    void onChatMessageReceived(const QString &messageContent, int senderId, int receiverId);
    /**
     * @brief Sends a chat message request to the server.
     * @param messageContent Message body.
     * @param receiverId Receiver user id, or -1 for the global channel.
     */
    Q_INVOKABLE void sendChatMessage(const QString &messageContent, int receiverId);
    /**
     * @brief Disconnects from the server and clears the local chat state.
     */
    Q_INVOKABLE void logout();

    /**
     * @brief Returns the current user list.
     * @return JSON array of users received from the last history payload.
     */
    QJsonArray getUsers() const;
    /**
     * @brief Returns the global channel messages.
     * @return JSON array containing global channel messages.
     */
    QJsonArray getGlobalMessages() const;
    /**
     * @brief Returns the current authenticated username.
     * @return Username associated with the logged-in account.
     */
    QString currentUsername() const;

    /**
     * @brief Returns the private messages for the given partner id.
     * @param userId Partner user id.
     * @return JSON array containing the private conversation.
     */
    Q_INVOKABLE QJsonArray getPrivateMessages(int userId) const;

private:
    /**
     * @brief Resolves the current user id from the cached username and user list.
     */
    void resolveCurrentUserId();

    TcpManager *tcpManager;
    QJsonArray globalMessages;
    QMap<int, QJsonArray> privateMessages;
    QJsonArray m_users;
    QString m_currentUsername;
    int m_currentUserId = -1;

signals:
    /**
     * @brief Emitted whenever users or messages are refreshed.
     */
    void historyUpdated();
    /**
     * @brief Emitted whenever the current username changes.
     */
    void currentUsernameChanged();
};
