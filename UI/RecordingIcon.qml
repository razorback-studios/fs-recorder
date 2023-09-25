import QtQuick 2.15

Item {
    id: recordingIcon
    
    //Outline Circle
    Rectangle {
        id: recordButtonOutline
        anchors.centerIn: parent
        width: 100
        height: 100
        radius: width / 2
        color: "#1A1919"
        border.color: "red"
        border.width: 3

        MouseArea {
            anchors.fill: parent
            onClicked: {
                simConnectController.StartRecording()
            }
        }
    }

    //Inner Circle
    Rectangle {
        id: recordButtonCenter
        anchors.centerIn: recordButtonOutline
        width: 78
        height: 78
        radius: width / 2
        color: "red"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                simConnectController.StartRecording()
            }
        }
    }

    //Recording Text
    Text {
        id: recordText
        text: "REC"
        color: "red"
        font.pixelSize: 32
        anchors {
            horizontalCenter: recordButtonCenter.horizontalCenter
            top:recordButtonOutline.bottom
            topMargin: 10
        }
    }

}
