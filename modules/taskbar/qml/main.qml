import QtQuick
import QtQuick.Controls
import "components"

Window {
    id: root
    width: Screen.width
    height: 40
    visible: true
    title: "taskbar"
    color: "#1e1e2e"

    Row {
        id: rightSystemTray
        spacing: 16


        anchors.right: parent.right
        anchors.rightMargin: 16
        anchors.verticalCenter: parent.verticalCenter

        Clock {
            id: clockWidget
            anchors.verticalCenter: parent.verticalCenter
        }

        Battery {
            id: batteryWidget
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}