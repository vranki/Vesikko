import QtQuick 1.0

Rectangle {
    width: 100
    height: 70
    color: "#88000000"
    z: 100
    Column {
        Text {
            color: "white"
            text: "Heading: " + Math.round(sub.rotation) + "°"
        }
        Text {
            color: "white"
            text: "Speed: " + Math.round(sub.speed) + "m/s"
        }
        Text {
            color: "white"
            text: "Depth: " + Math.round(sub.depth) + "m"
        }
    }
}
