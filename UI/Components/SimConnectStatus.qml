import QtQuick 2.15

Item {
    id: simConnectStatus

    Text {
        id: connectedStatusText
        text: "MSFS Status: "
        color: "white"
        font.pixelSize: 20

        anchors.centerIn: parent
    }

    Rectangle {
        id: statusCircle
        color: simConnectController.isConnected ? "green" : "red"
        height: 30
        width: 30
        radius: width/2

        anchors {
            left: connectedStatusText.right
            leftMargin: 10
            verticalCenter: connectedStatusText.verticalCenter
        }
    }
}