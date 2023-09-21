import QtQuick 2.15

import "./Components"

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

    StopIcon {
        id: stopIconContainer
        anchors {
            verticalCenter: parent.verticalCenter
            right: recordingIconContainer.left
            rightMargin: 150
        }
    }

    //Status Text
    Text {
        id: statusText
        color: "red"
        text: recordingController.status
    }

    //Pause / PlayButton
    // PauseButton {
    //     id: playButtonContainer
    //     anchors {
    //         verticalCenter: parent.verticalCenter
    //         left: recordingIconContainer.right
    //         leftMargin: 110
    //     }
    // }

    // Image {
    //     id: testImage
    //     source: "qrc:/Assets/Vector.png"
    //     height: 100
    //     width: 100

    //     anchors {
    //         verticalCenter: parent.verticalCenter
    //         left: recordingIconContainer.right
    //         leftMargin: 120
    //     }
    // }
    PlayButton {
        id: playButtonContainer
        anchors {
            verticalCenter: parent.verticalCenter
            left: recordingIconContainer.right
            leftMargin: 110
        }
    }
}
