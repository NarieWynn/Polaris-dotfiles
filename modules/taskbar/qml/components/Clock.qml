import QtQuick

Item {
    id: root
    width: clockColumn.width
    height: parent ? parent.height : 0

    //xếp chồng 2 text
    Column {
        id: clockColumn
        spacing: 1 //space between time text and date text

        //place text in the middle of taskbar (vertical)
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id: dateTextDisplay
            text: sysClock.dateText
            color: "white"
            font.bold: true
            font.pixelSize: 12
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: timeTextDisplay
            text: sysClock.timeText
            color: "#aaaaaa"
            font.pixelSize: 12
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}