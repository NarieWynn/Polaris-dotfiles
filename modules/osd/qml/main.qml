import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 240
    height: 30

    Rectangle {
        anchors.fill: parent
        color: "#CC121212"
        radius: 16
        border.color: "#26FFFFFF"
        border.width: 1

        Row {
            anchors.centerIn: parent
            spacing: 10

            Text {
                text: osdMode === "volume" ? "" : "🔆"
                font.pointSize: 12
                color: "#A7C080"
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle {
                width: 140
                height: 5
                color: "#33FFFFFF"
                radius: 3
                anchors.verticalCenter: parent.verticalCenter

                Rectangle {
                    width: (osdMode === "volume" ? hardwareManager.volume : hardwareManager.brightness) / 100 * parent.width
                    height: parent.height
                    color: "#A7C080"
                    radius: 3

                    Behavior on width {
                        NumberAnimation { duration: 120; easing.type: Easing.OutQuad }
                    }
                }
            }

            Text {
                text: (osdMode === "volume" ? hardwareManager.volume : hardwareManager.brightness) + "%"
                font.bold: true
                font.pixelSize: 11
                color: "#E0FFFFFF"
                anchors.verticalCenter: parent.verticalCenter
                width: 30
            }
        }
    }

    Timer {
        id: closeTimer
        interval: 2000
        running: true
        repeat: false
        onTriggered: fadeAnimator.start()
    }

    OpacityAnimator {
        id: fadeAnimator
        target: root
        to: 0.0
        duration: 250
        onFinished: Qt.quit()
    }
}