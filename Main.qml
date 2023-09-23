import QtQuick
import QtQuick.Window
import Razorback 1.0

Window {
    width: 950
    height: 534
    visible: true
    title: qsTr("FSRecorder")

    Recording {
        id: recordingController
    }

    SimConnectWorker {
        id: simConnectController
    }

    Loader {
        id: mainLoader
        anchors.fill: parent
        source: "./UI/HomeScreen.qml"
    }
}
