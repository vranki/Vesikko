import QtQuick 1.0
import "ComponentCreation.js" as ComponentCreation

Rectangle {
    id: map
    z: -1000
    color: "steelblue"
    property int gridsize: 100
    property int gridCount: 40
    property real mapCenterLat: sub.lat
    property real mapCenterLon: sub.lon

    function createVessel(id, lat, lon, type) {
        ComponentCreation.createVessel(id, lat, lon, type)
    }

    function transformToMapX(lat) {
        return (lat - mapCenterLat) * zoomcontrol.scaling + map.width/2
    }
    function transformToMapY(lon) {
        return (lon - mapCenterLon) * zoomcontrol.scaling + map.height/2
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

    Vessel {
        id: sub
        objectName: "sub"
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
                while(mapCenterLon < mapGrid.yPos)
                    mapGrid.yPos -= gridsize
                while(mapCenterLon >= mapGrid.yPos + gridsize)
                    mapGrid.yPos += gridsize
                while(mapCenterLat < mapGrid.xPos)
                    mapGrid.xPos -= gridsize
                while(mapCenterLat >= mapGrid.xPos + gridsize)
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
