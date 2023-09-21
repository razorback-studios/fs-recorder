import QtQuick 2.15

Item {
    id: pauseButton

    Rectangle {
        id: pauseContainer
        border.color: "white"
        border.width: 3
        width: 60
        color: "transparent"

        Rectangle {
            id: leftBar
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
            }
            height: 100
            width: 20
            color: "white"
        }

        Rectangle {
            id: rightBar
            anchors {
                left: leftBar.right
                leftMargin: 20
                verticalCenter: parent.verticalCenter
            }
            height: 100
            width: 20
            color: "white"
        }

        Text {
            id: playText
            text: "Play"
            color: "white"
            font.pixelSize: 32
            anchors {
                top: leftBar.bottom
                topMargin: 10
                horizontalCenter: pauseContainer.horizontalCenter
            }
        }   

    }
}