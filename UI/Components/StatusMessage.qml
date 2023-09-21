import QtQuick 2.15

Item {
    id: statusMessage

    Text {
        text: recordingController.status
        color: "red"
        font.pixelSize: 32
        anchors.centerIn: parent
    }
}