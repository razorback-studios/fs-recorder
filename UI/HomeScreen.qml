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
    StatusMessage {
        id: statusMessageContainer
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 40
        }
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

    PlayButton {
        id: playButtonContainer
        anchors {
            verticalCenter: parent.verticalCenter
            left: recordingIconContainer.right
            leftMargin: 150
        }
    }

    //File Menu
    FileMenu {
        id: fileMenuContainer
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: statusMessageContainer.bottom
            topMargin: 60
        }
    }
}
