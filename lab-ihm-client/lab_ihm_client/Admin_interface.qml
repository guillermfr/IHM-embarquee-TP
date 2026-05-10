import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    title: "Admin Interface"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 50
        spacing: 10

        Label {
            text: "Admin interface"
            font.bold: true
            Layout.fillWidth: true
            font.pixelSize: 24
        }

        ToolSeparator {
            Layout.fillWidth: true
        }

        Label {
            text: "Encryption Configuration"
            font.bold: true
            Layout.fillWidth: true
        }

        Rectangle {
            Layout.fillWidth: true
            height: 60
            color: "#eeeeee"
            radius: 5

            Label {
                anchors.centerIn: parent
                text: "Encryption settings coming soon..."
                color: "gray"
            }
        }

        ToolSeparator {
            Layout.fillWidth: true
        }

        Label {
            text: "User Management"
            font.bold: true
            Layout.fillWidth: true
        }

        ListView {
            id: userList
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            model: ListModel {
                id: userModel
                ListElement { name: "Alice" }
                ListElement { name: "Bob" }
                ListElement { name: "Charlie" }
            }

            delegate: ItemDelegate {
                text: model.name
                width: ListView.view.width

                highlighted: ListView.isCurrentItem

                onClicked: {
                    userList.currentIndex = index
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            TextField {
                id: usernameInput
                placeholderText: "Enter username"
                Layout.fillWidth: true
            }

            Button {
                text: "Add"
                onClicked: {
                    
                }
            }

            Button {
                text: "Delete"
                enabled: userList.currentIndex !== -1

                onClicked: {
                    
                }
            }
        }

        ToolSeparator {
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: "Exit without Saving"
                Layout.fillWidth: true

                onClicked: {
                    
                }
            }

            Button {
                text: "Save Configuration"
                Layout.fillWidth: true

                onClicked: {
                    
                }
            }
        }
    }
}