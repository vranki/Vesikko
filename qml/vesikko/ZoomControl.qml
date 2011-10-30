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
    NumberAnimation on scaling {
        id: scalingAnimation
        to: 1;
        duration: 100
        running: false
        easing { type: Easing.InQuad }
    }
    Button {
        anchors.right: parent.right
        text: "+"
        MouseArea {
            anchors.fill: parent
            onClicked: { scalingAnimation.from = scaling;
                scaling *= 2.0;
                scalingAnimation.to = scaling; updateScale()
                scalingAnimation.start()
            }
        }
    }
    Button {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        text: "-"
        MouseArea {
            anchors.fill: parent
            onClicked: { scalingAnimation.from = scaling;
                scaling /= 2.0;
                scalingAnimation.to = scaling; updateScale()
                scalingAnimation.start()}
        }
    }
}
