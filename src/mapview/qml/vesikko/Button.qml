import QtQuick 1.0

Rectangle {
    property string text: ""
    width: 40
    height: width
    radius: 5
    color: "#88000000"
    z: 100
    Text {
        color: "white"
        text: parent.text
        anchors.centerIn: parent
    }
}
