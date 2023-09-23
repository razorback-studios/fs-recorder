import QtQuick 2.15

Item {
    id: simConnectStatus

    Text {
        id: connectedStatusText
        text: "MSFS Status: "  //+ (simConnectController.connectionStatus ? "Connected" : "Not Connected")
        color: "white"
        font.pixelSize: 20

        anchors.centerIn: parent
    }
}