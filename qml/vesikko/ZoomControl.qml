import QtQuick 1.0

Item {
    property real scaling: 1.0
    Button {
        anchors.right: parent.right
        text: "+"
        MouseArea {
            anchors.fill: parent
            onClicked: { scaling *= 2.0}
        }
    }
    Button {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        text: "-"
        MouseArea {
            anchors.fill: parent
            onClicked: { scaling /= 2.0}
        }
    }
}
