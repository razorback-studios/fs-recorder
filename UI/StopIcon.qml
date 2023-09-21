import QtQuick 2.15

Item {
    id: stopIcon

    //Stop Button
    Rectangle {
        id: stopButton
        width: 100
        height: 100
        color: "white"
        anchors.centerIn: parent

        MouseArea {
            anchors.fill: parent
            onClicked: {
                recordingController.handleRecordStop()
            }
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
