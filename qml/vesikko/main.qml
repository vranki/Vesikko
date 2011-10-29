import QtQuick 1.0

Rectangle {
    id: map
    z: -1000
    color: "blue"
    property int gridsize: 100
    property int gridCount: 20
    ZoomControl {
        z:100
        id: zoomcontrol
        width: parent.width
        height: parent.height
    }
    Row {
        z:100
        spacing: 5
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        Helm {
            objectName: "helm"

        }
        SpeedControl {
            objectName: "speed"
        }
    }
    Text {
        z:100
        id: statusText
        text: ""
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Image {
        id: sub
        objectName: "sub"
        source: "sub.png"
        smooth: true
        z: 10
        scale:0.5
        transformOrigin: "Center"
        property real rudder: 0
        property real lat: 0
        property real lon: 0
        x: parent.width / 2  - width/2
        y: parent.height / 2 - height/2
    }
    Grid {
        x: parent.width/2 - (sub.lat+gridsize*gridCount/2) * zoomcontrol.scaling
        y: parent.height/2 - (sub.lon+gridsize*gridCount/2) * zoomcontrol.scaling
        z: 1
        columns: gridCount
        Repeater {
            model: gridCount*gridCount
            Rectangle {
                border.color: "blue"
                border.width: 1
                z: -100
                color: "steelblue"
                width: gridsize * zoomcontrol.scaling
                height: width
            }
        }
    }

}
