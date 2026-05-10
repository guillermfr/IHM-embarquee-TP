pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    title: "QtChat"

    signal logoutRequested()

    function contactNameForId(userId) {
        for (var i = 0; i < contactsModel.count; ++i) {
            var contact = contactsModel.get(i)
            if (Number(contact.contactId) === Number(userId)) {
                return contact.contactName
            }
        }

        return String(userId)
    }

    function normalizeContact(user) {
        return {
            contactId: Number(user.id),
            contactName: String(user.name)
        }
    }

    function normalizeMessage(messageObject) {
        var senderId = Number(messageObject.sender !== undefined ? messageObject.sender : messageObject["sender"])
        var receiverId = Number(messageObject.receiver !== undefined ? messageObject.receiver : messageObject["receiver"])
        var messageText = String(messageObject.message !== undefined ? messageObject.message : messageObject["message"])

        return {
            senderId: senderId,
            senderName: contactNameForId(senderId),
            receiverId: receiverId,
            messageText: messageText
        }
    }

    Connections {
        target: mainBackend
        function onHistoryUpdated() {
            var oldIdx = contactsList.currentIndex
            var oldUserId = (oldIdx >= 0 && contactsModel.count > oldIdx) ? contactsModel.get(oldIdx).contactId : -1

            contactsModel.clear()
            var users = mainBackend.users
            var newIdx = -1
            for (var i = 0; i < users.length; ++i) {
                contactsModel.append(normalizeContact(users[i]))
                if (Number(users[i].id) === Number(oldUserId)) {
                    newIdx = i
                }
            }
            if (oldIdx === -1) {
                contactsList.currentIndex = -1
            } else {
                contactsList.currentIndex = newIdx
            }
            updateMessages()
        }
    }

    function updateMessages() {
        messagesModel.clear()
        var msgs
        if (contactsList.currentIndex === -1) {
            msgs = mainBackend.globalMessages
        } else {
            var userId = contactsModel.get(contactsList.currentIndex).contactId
            msgs = mainBackend.getPrivateMessages(userId)
        }
        
        if (msgs) {
            for (var i = 0; i < msgs.length; ++i) {
                messagesModel.append(normalizeMessage(msgs[i]))
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // Gauche : Liste des contacts
        ColumnLayout {
            Layout.maximumWidth: 225
            Layout.fillHeight: true
            spacing: 0

            ItemDelegate {
                text: "Global Channel"
                Layout.fillWidth: true

                highlighted: contactsList.currentIndex === -1

                onClicked: {
                    contactsList.currentIndex = -1
                    updateMessages()
                }
            }

            ToolSeparator {
                orientation: Qt.Horizontal
                Layout.fillWidth: true
            }

            ListView {
                id: contactsList
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true

                model: ListModel {
                    id: contactsModel
                }

                delegate: ItemDelegate {
                    required property int index
                    required property string contactName

                    text: contactName !== undefined ? contactName : ""
                    width: ListView.view.width

                    highlighted: ListView.isCurrentItem

                    onClicked: {
                        contactsList.currentIndex = index
                        updateMessages()
                    }
                }
            }

            // Zone utilisateur en bas
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 100
                color: Qt.rgba(0, 0, 0, 0.02) // Léger fond transparent pour créer un contraste

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 5

                    Label {
                        text: "Utilisateur"
                        font.bold: true
                        Layout.fillWidth: true
                        elide: Label.ElideRight
                    }

					ColumnLayout {
						spacing: 5


                        Button {
                            text: "Admin Panel"
                            Layout.preferredHeight: 30
                            Layout.alignment: Qt.AlignCenter
                        }

                        Button {
                            text: "Logout"
                            Layout.preferredHeight: 30
                            Layout.alignment: Qt.AlignCenter

                            onClicked: {
                                mainBackend.logout()
                                logoutRequested()
                            }
                        }
					}
                }
            }
        }

        // Séparateur visuel simple (optionnel mais lisible)
        ToolSeparator {
            Layout.fillHeight: true
        }

        // Droite : Zone de discussion
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            // En-tête de la discussion
            ToolBar {
                Layout.fillWidth: true
                Layout.preferredHeight: 40

                Row {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.margins: 24
                    anchors.leftMargin: 6
                    spacing: 8

                    ToolButton {
                        icon.name: "changes-prevent" // Icône symbolique Linux/GTK (cadenas). "lock" ou "dialog-password" fonctionnent aussi selon le thème.
                        background: null // Rend le bouton complètement invisible (pas de fond)
                        enabled: false // Rend l'icône purement décorative
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Label {
                        text: "General Channel"
                        font.pixelSize: 18
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }

            // Liste des messages
            ListView {
                id: messagesList
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
				Layout.margins: 10

                model: ListModel {
                    id: messagesModel
                }

                delegate: ItemDelegate {
                    required property string senderName
                    required property string messageText

                    text: senderName + ": " + messageText
                    width: ListView.view.width
                }
            }

            // Zone de saisie
            RowLayout {
                Layout.fillWidth: true
                Layout.margins: 10
                spacing: 10

                TextField {
                    id: messageInput
                    placeholderText: "Write a message..."
                    Layout.fillWidth: true
                }

                Button {
                    text: "Send"

                    onClicked: {
                        var messageText = messageInput.text.trim()
                        if (messageText.length === 0) {
                            return
                        }

                        var rcvr = contactsList.currentIndex === -1 ? -1 : contactsModel.get(contactsList.currentIndex).contactId
                        mainBackend.sendChatMessage(messageText, rcvr)
                        messageInput.text = ""
                    }
                }
            }
        }
    }
}