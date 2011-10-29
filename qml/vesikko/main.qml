import QtQuick 1.0

Rectangle {
    id: map
    color: "steelblue"
    property int gridsize: 100
    property int gridCount: 10
    ZoomControl {
        id: zoomcontrol
        width: parent.width
        height: parent.height
    }
    Row {
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
        id: scaleText
        text: "Map Scale " + parent.width / zoomcontrol.scaling + "m"
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Text {
        id: statusText
        text: ""
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: scaleText.bottom
    }
    Image {
        id: sub
        objectName: "sub"
        source: "sub.png"
        smooth: true
        z: 10
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
                color: "#00000000"
                width: gridsize * zoomcontrol.scaling
                height: width
            }
        }
    }

}
