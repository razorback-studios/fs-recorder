import QtQuick 2.15

Item {
    id: stopIcon

    //Stop Button
    Rectangle {
        id: stopButton
        width: 100
        height: 100
        color:  simConnectController.isRecording ? "white" : "#9e9e9e"
        anchors.centerIn: parent

        MouseArea {
            anchors.fill: parent
            onClicked: {
                //If recording, stop recording else do nothing
                simConnectController.isRecording ? simConnectController.StopRecording() : null
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
