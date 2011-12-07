import QtQuick 1.0

Rectangle {
    property string text: ""
    width: 200
    height: 50
    color: "#222222"
    border.color: "white"
    border.width: 3
    radius: 5
    smooth: true
    Text {
        anchors.centerIn: parent
        text: parent.text
        color: "white"
    }
}
