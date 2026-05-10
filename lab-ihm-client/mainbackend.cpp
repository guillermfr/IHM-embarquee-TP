/**
 * @file mainbackend.cpp
 * @brief Implementation of the chat history backend.
 */

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

#include "mainbackend.h"
#include "tcpmanager.h"

/** @copydoc MainBackend::MainBackend */
MainBackend::MainBackend(TcpManager *tcpManager, QObject *parent) : QObject(parent), tcpManager(tcpManager) {
	connect(tcpManager, &TcpManager::historyReceived, this, &MainBackend::onHistoryReceived);
	connect(tcpManager, &TcpManager::chatMessageReceived, this, &MainBackend::onChatMessageReceived);
}

/** @copydoc MainBackend::setCurrentUsername */
void MainBackend::setCurrentUsername(const QString &username) {
	m_currentUsername = username;
	resolveCurrentUserId();
	emit currentUsernameChanged();
}

/** @copydoc MainBackend::resolveCurrentUserId */
void MainBackend::resolveCurrentUserId() {
	m_currentUserId = -1;

	if (m_currentUsername.isEmpty()) {
		return;
	}

	for (const QJsonValue &value : m_users) {
		QJsonObject user = value.toObject();
		if (user.value("name").toString() == m_currentUsername) {
			m_currentUserId = user.value("id").toInt(-1);
			break;
		}
	}
}

/** @copydoc MainBackend::onHistoryReceived */
void MainBackend::onHistoryReceived(const QJsonArray &users, const QJsonArray &messages) {
	// Wipe previous history
	globalMessages = QJsonArray();
	privateMessages.clear();
	m_users = users;
	resolveCurrentUserId();

	auto appendPrivateMessage = [this](const QJsonObject &msg, int senderId, int receiverId) {
		if (receiverId == -1 || m_currentUserId < 0) {
			return;
		}

		if (senderId != m_currentUserId && receiverId != m_currentUserId) {
			return;
		}

		int partnerId = (senderId == m_currentUserId) ? receiverId : senderId;
		if (partnerId == m_currentUserId || partnerId < 0) {
			return;
		}

		privateMessages[partnerId].append(msg);
	};

	// Store messages for global channel and private messages
	for (int index = messages.size() - 1; index >= 0; --index) {
		const QJsonValue &value = messages.at(index);
		QJsonObject msg = value.toObject();
		int receiver = msg["receiver"].toInt();
		
		if (receiver == -1) {
			globalMessages.append(msg);
		} else {
			int sender = msg["sender"].toInt();
			appendPrivateMessage(msg, sender, receiver);
		}
	}
	
	emit historyUpdated();
}

/** @copydoc MainBackend::onChatMessageReceived */
void MainBackend::onChatMessageReceived(const QString &messageContent, int senderId, int receiverId) {
	QJsonObject msg;
	msg["sender"] = senderId;
	msg["receiver"] = receiverId;
	msg["message"] = messageContent;

	if (receiverId == -1) {
		globalMessages.append(msg);
	} else {
		if (m_currentUserId >= 0) {
			if (senderId == m_currentUserId || receiverId == m_currentUserId) {
				int partnerId = (senderId == m_currentUserId) ? receiverId : senderId;
				if (partnerId != m_currentUserId && partnerId >= 0) {
					privateMessages[partnerId].append(msg);
				}
			}
		}
	}
	
	emit historyUpdated();
}

/** @copydoc MainBackend::sendChatMessage */
void MainBackend::sendChatMessage(const QString &messageContent, int receiverId) {
	if (messageContent.trimmed().isEmpty()) {
		return;
	}

	QJsonObject content;
	content["receiver"] = receiverId;
	content["message"] = messageContent;

	QJsonObject request;
	request["type"] = "send";
	request["content"] = content;

	QString jsonString = QJsonDocument(request).toJson(QJsonDocument::Compact) + "\n";
	qDebug() << "Sending chat request:" << jsonString;
	tcpManager->sendMessage(jsonString);
}

/** @copydoc MainBackend::logout */
void MainBackend::logout() {
	tcpManager->disconnectFromServer();
	m_currentUsername.clear();
	m_currentUserId = -1;
	m_users = QJsonArray();
	globalMessages = QJsonArray();
	privateMessages.clear();
	emit currentUsernameChanged();
}

/** @copydoc MainBackend::getUsers */
QJsonArray MainBackend::getUsers() const {
    return m_users;
}

/** @copydoc MainBackend::getGlobalMessages */
QJsonArray MainBackend::getGlobalMessages() const {
    return globalMessages;
}

/** @copydoc MainBackend::currentUsername */
QString MainBackend::currentUsername() const {
	return m_currentUsername;
}

/** @copydoc MainBackend::getPrivateMessages */
QJsonArray MainBackend::getPrivateMessages(int userId) const {
    return privateMessages.value(userId);
}
