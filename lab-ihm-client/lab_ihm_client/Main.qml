pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("QtChat")

    Connections {
        target: stack.currentItem
        ignoreUnknownSignals: true

        function onLogoutRequested() {
            stack.pop()
        }
    }

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: loginPageComponent

        Component {
            id: loginPageComponent
            Login_page {
                onLoginSuccessful: stack.push(mainPageComponent)
            }
        }

        Component {
            id: mainPageComponent
            Main_interface {}
        }
    }
}
