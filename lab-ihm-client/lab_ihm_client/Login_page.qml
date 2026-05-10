import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    title: "Home"

	signal loginSuccessful()

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 15
        width: 300

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            TextField {
                id: serverInput
                placeholderText: "Serveur"
                text: "192.168.12.119"
                Layout.fillWidth: true
                validator: RegularExpressionValidator {
                    regularExpression: /^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/
                }
            }

            TextField {
                id: portInput
                placeholderText: "Port"
                text: "8080"
                Layout.preferredWidth: 80
                validator: IntValidator { bottom: 1; top: 65535 }
                inputMethodHints: Qt.ImhDigitsOnly
            }
        }

        TextField {
            id: usernameInput
            placeholderText: "Nom d'utilisateur"
            text: "admin"
            Layout.fillWidth: true
        }

        TextField {
            id: passwordInput
            placeholderText: "Mot de passe"
            echoMode: TextInput.Password
            text: "admin"
            Layout.fillWidth: true
        }

        Button {
            text: "Se connecter"
            Layout.fillWidth: true

            onClicked: {
                loginBackend.login(serverInput.text, portInput.text, usernameInput.text, passwordInput.text)
            }
        }
    }

    Connections {
        target: loginBackend

        function onLoginSuccess() {
            console.log("Login successful!")
			loginSuccessful()
        }

        function onLoginFailed(reason) {
            console.log("Login failed: " + reason)
        }
    }
}