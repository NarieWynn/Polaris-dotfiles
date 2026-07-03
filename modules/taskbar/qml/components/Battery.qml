import QtQuick
import QtQuick.Layouts


Row {
    id: batteryRow
    spacing: 6

    width: batteryIcon.width + batteryText.width + spacing
    height: 40

    Text {
        id: batteryIcon
        font.family: "JetBrainsMono Nerd Font" 
        font.pixelSize: 16


        text: sysBattery.isCharging ? "󱐋" :
            (sysBattery.batteryLevel > 80 ? " " :
                    sysBattery.batteryLevel > 50 ? " " :
                        sysBattery.batteryLevel > 20 ? " " : " ")

        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        id: batteryText
        text: sysBattery.batteryLevel + "%"
        color: sysBattery.isCharging ? "#00FF7F" : (sysBattery.batteryLevel <= 20 ? "#FF6347" : "white")
        font.pixelSize: 13
        font.bold: true
        anchors.verticalCenter: parent.verticalCenter
    }
}