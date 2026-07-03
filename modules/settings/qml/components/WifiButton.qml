import QtQuick
import QtQuick.Effects

Item {
    id: root

    Rectangle {
        id: background
        anchors.fill: parent
        radius: 16
        color: Qt.rgba(1, 1, 1, 0.08)
        border.color: Qt.rgba(1, 1, 1, 0.15)
        border.width: 1
        layer.enabled: true
        layer.effect: MultiEffect {
            blurEnabled: true
            blur: 0.4
            blurMax: 32
        }
    }

    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 12
        spacing: 12

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: "Wi-Fi"
            color: "white"
            font.pixelSize: 15
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: console.log("wifi clicked")
    }
}