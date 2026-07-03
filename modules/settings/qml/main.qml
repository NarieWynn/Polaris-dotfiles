import QtQuick
import QtQuick.Controls
import "components"

Window {
    width: 800
    height: 600
    title: "Settings"
    color: "#1e1e2e"
    visible: true
    Row {
        anchors.fill: parent

        Rectangle {
            width: parent.width * 0.3
            height: parent.height
            color: "#181825"

            Column {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 4

                WifiButton {
                    width: parent.width
                    height: 48
                }
            }
        }

        Rectangle {
            width: parent.width * 0.7
            height: parent.height
            color: "#1e1e2e"
        }
    }
}