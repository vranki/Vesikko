import QtQuick 1.0

Image {
    signal deleteVesselSignal(int id)
    source: "sub.png"
    smooth: true
    z: 10
    scale:0.5
    transformOrigin: "Center"
    x: map.transformToMapX(lat)
    y: map.transformToMapY(lon)
    property real rudder: 0
    property real lat: 0
    property real lon: 0
    property real depth: 0
    property real speed: 0
    property int vesselId: -1
    onDeleteVesselSignal: {
        if(id == vesselId) {
            visible = false;
            destroy()
        }
    }
}
