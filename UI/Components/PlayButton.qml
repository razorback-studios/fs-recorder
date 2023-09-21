import QtQuick 2.15

Item {
    id: playButton

    Image {
        id: playImage
        source: "qrc:/Assets/Vector.png"
        height: 99
        width: 88
        anchors.centerIn: parent
    }   

    Text {
        id: playText
        text: "PLAY"
        color: "white"
        font.pixelSize: 32
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: playImage.bottom
            topMargin: 10
        }
    }
}