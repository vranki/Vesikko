import QtQuick 1.0

Rectangle {
    id: map
    z: -1000
    color: "steelblue"
    property int gridsize: 100
    property int gridCount: 40

    function transformToMapX(lat) {
        return (lat - sub.lat) * zoomcontrol.scaling + map.width/2
    }
    function transformToMapY(lon) {
        return (lon - sub.lon) * zoomcontrol.scaling + map.height/2
    }

    ZoomControl {
        z:100
        id: zoomcontrol
        width: parent.width
        height: parent.height
    }

    StatusDisplay {

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
        DepthControl {
            objectName: "depth"
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
        property real depth: 0
        property real speed: 0
        x: parent.width / 2  - width/2
        y: parent.height / 2 - height/2
    }

    Grid {
        function positionGridX() {
            return transformToMapX(xPos - gridsize * gridCount/2)
        }
        function positionGridY() {
            return transformToMapY(yPos - gridsize * gridCount/2)
        }

        Timer {
            interval: 500; running: true; repeat: true
            onTriggered: {
                while(sub.lon < mapGrid.yPos)
                    mapGrid.yPos -= gridsize
                while(sub.lon >= mapGrid.yPos + gridsize)
                    mapGrid.yPos += gridsize
                while(sub.lat < mapGrid.xPos)
                    mapGrid.xPos -= gridsize
                while(sub.lat >= mapGrid.xPos + gridsize)
                    mapGrid.xPos += gridsize
            }
        }

        id: mapGrid
        x: positionGridX()
        y: positionGridY()
        z: 1
        spacing: gridsize * zoomcontrol.scaling-dotsize
        columns: gridCount
        clip: true
        property int dotsize: 2
        property int xPos: 0
        property int yPos: 0
        Repeater {
            model: gridCount*gridCount
            Rectangle {
                z: -100
                color: "blue"
                width: mapGrid.dotsize
                height: width

            }
        }
    }

}
