import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 850
    height: 150
    focus: true

    property variant wallpaperList: wallpaperManager.loadWallpapers()
    property bool isReady: false

    Keys.onLeftPressed: pathView.decrementCurrentIndex()
    Keys.onRightPressed: pathView.incrementCurrentIndex()
    Keys.onEscapePressed: Qt.quit()


    Timer {
        id: focusFixTimer
        interval: 50
        running: false
        repeat: false
        onTriggered: {
            var activeIndex = wallpaperManager.getCurrentWallpaperIndex(root.wallpaperList)
            pathView.currentIndex = activeIndex

            root.isReady = true
        }
    }

    Component.onCompleted: {
        focusFixTimer.start()
    }

    Rectangle {
        anchors.fill: parent
        color: "#CC121212"
        radius: 16
        border.color: "#26FFFFFF"
        border.width: 1

        PathView {
            id: pathView
            anchors.fill: parent
            anchors.margins: 15
            clip: true
            focus: true

            model: root.wallpaperList

            preferredHighlightBegin: 0.5
            preferredHighlightEnd: 0.5
            highlightRangeMode: PathView.StrictlyEnforceRange
            highlightMoveDuration: 200

            delegate: Item {
                width: 160
                height: 120
                property string filePathData: modelData

                scale: PathView.itemScale
                z: PathView.itemZ

                Rectangle {
                    width: 160
                    height: 120
                    anchors.centerIn: parent
                    radius: 8
                    color: "#22FFFFFF"
                    clip: true

                    Image {
                        anchors.fill: parent
                        source: modelData
                        fillMode: Image.PreserveAspectCrop
                        asynchronous: true
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: pathView.currentIndex = index
                    }
                }
            }

            path: Path {
                startX: -60; startY: 60
                PathAttribute { name: "itemScale"; value: 0.75 }
                PathAttribute { name: "itemZ"; value: 1 }

                PathLine { x: 410; y: 60 }
                PathPercent { value: 0.5 }
                PathAttribute { name: "itemScale"; value: 1.1 }
                PathAttribute { name: "itemZ"; value: 10 }

                PathLine { x: 880; y: 60 }
                PathPercent { value: 1.0 }
                PathAttribute { name: "itemScale"; value: 0.75 }
                PathAttribute { name: "itemZ"; value: 1 }
            }

            onCurrentIndexChanged: {
                if (root.isReady && count > 0 && currentItem) {
                    wallpaperManager.setWallpaper(currentItem.filePathData)
                }
            }
        }

        Rectangle {
            width: 180
            height: 120
            anchors.centerIn: parent
            color: "transparent"
            border.color: "#FFFFFF"
            border.width: 3
            radius: 10
            z: 100
        }
    }
}