import QtQuick 1.0

Item {
    property real scaling: 1.0
    function updateScale() {
        statusText.text = "Map Scale " + parent.width / scaling + "m (" + scaling + "x)"
        if(gridsize*scaling < 30) {
            gridsize*=10
        } else if(gridsize*scaling > 300) {
            gridsize/=10
        }
    }

    Button {
        anchors.right: parent.right
        text: "+"
        MouseArea {
            anchors.fill: parent
            onClicked: { scaling *= 2.0;updateScale()}
        }
    }
    Button {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        text: "-"
        MouseArea {
            anchors.fill: parent
            onClicked: { scaling /= 2.0;updateScale()}
        }
    }
}
