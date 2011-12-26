import QtQuick 1.0

Rectangle {
    id: hydrophoneView
    property real hydrophoneDirection: 0
    property real hydrophoneRotateSpeed: 0
    property real subDirection: 0
    signal hydrophoneDirectionChangedSignal(double dir)
    color: "black"

    function subDirectionChanged(dir) {
        subDirection = dir
    }

    Timer {
        id: rotateTimer
        interval: 10
        running: false
        repeat: true
        onTriggered: {
            if(hydrophoneRotateSpeed != 0) {
                hydrophoneDirection += hydrophoneRotateSpeed
                while(hydrophoneDirection >= 360) hydrophoneDirection -= 360;
                while(hydrophoneDirection < 0) hydrophoneDirection += 360;
                hydrophoneView.hydrophoneDirectionChangedSignal(hydrophoneDirection)
            }
        }
    }

    Image {
        source: "hydrophone_background.svg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }
    Image {
        source: "hydrophone_needle.svg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        z: 10
        rotation: parent.hydrophoneDirection
    }
    Image {
        source: "hydrophone_sub.svg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        z: 5
        rotation: parent.subDirection
    }
    Rectangle {
        color: "gray"
        width: 150
        height:40
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                hydrophoneRotateSpeed = (mouseX - parent.width/2)/ parent.width
                rotateTimer.start()
            }

            onMouseXChanged: {
                if(containsMouse) {
                    hydrophoneRotateSpeed = (mouseX - parent.width/2)/ parent.width
                }
            }
            onContainsMouseChanged:  {
                if(!containsMouse) {
                    rotateTimer.stop()
                    hydrophoneRotateSpeed = 0
                }
            }
        }
    }
}
