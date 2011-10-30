import QtQuick 1.0

Image {
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
    x: map.transformToMapX(lat)
    y: map.transformToMapY(lon)
}
