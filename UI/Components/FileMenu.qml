import QtQuick 2.15

Item {
    id: fileMenu

    Rectangle {
        id: leftBlock
        height: 35
        width: 125
        color: "transparent"
        border.color: "#FF0101"
        border.width: 1
        anchors {
            verticalCenter: parent.verticalCenter
            right: centerBlock.left
            rightMargin: 40
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                simConnectController.SaveCSV("C:\\Users\\w_can\\OneDrive\\Desktop\\test", "data.frc", "test.frc");
            }
        }

        Text {
            id: leftBlockText
            color: "white"
            text: "Save File"
            font.pixelSize: 20
            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
        }
    }

    Rectangle {
        id: centerBlock
        height: 35
        width: 125
        color: "transparent"
        border.color: "#FF0101"
        border.width: 1
        anchors.centerIn: parent

        Text {
            id: centerBlockText
            color: "white"
            text: "Load File"
            font.pixelSize: 20
            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
        }
    }
    
    Rectangle {
        id: rightBlock
        height: 35
        width: 125
        color: "transparent"
        border.color: "#FF0101"
        border.width: 1
        anchors {
            verticalCenter: parent.verticalCenter
            left: centerBlock.right
            leftMargin: 40
        }

        Text {
            id: rightBlockText
            color: "white"
            text: "Settings"
            font.pixelSize: 20
            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
        }
    }
}