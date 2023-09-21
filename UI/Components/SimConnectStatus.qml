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
}