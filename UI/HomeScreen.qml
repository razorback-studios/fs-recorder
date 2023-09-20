import QtQuick 2.15

Item {
    id: homeScreen

    //Background
    Rectangle {
        id: homeBackground
        anchors.fill: parent
        color: "#1A1919"
    }

    //Recording Icon
    RecordingIcon {
        id: recordingIconContainer
        anchors.centerIn: parent
    }

    //Stop Button
    Rectangle {
        id: stopButton
        width: 100
        height: 100
        color: "white"
        anchors {
            verticalCenter: parent.verticalCenter
            right: recordingIconContainer.left
            rightMargin: 100
        }
    }

    Text {
        id: stopText
        text: "STOP"
        color: "white"
        font.pixelSize: 32
        anchors {
            horizontalCenter: stopButton.horizontalCenter
            top: stopButton.bottom
            topMargin: 10
        }
    }
}
