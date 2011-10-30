import QtQuick 1.0

Row {
    property int depthChange: 0
    signal setDepthChange(int depth)
    id: depthControl

    function updateDepth() {
        if(depthChange==-1) statusText.text = "Ascending"
        if(depthChange==0) statusText.text = "Dive Planes Level"
        if(depthChange==1) statusText.text = "Diving"
        depthControl.setDepthChange(depthChange)
    }

    Button {
        text: "↑"
        MouseArea {
            anchors.fill: parent
            onClicked: { if(depthChange > -1) depthChange -= 1; updateDepth()}
        }
    }
    Button {
        text: "-"
        MouseArea {
            anchors.fill: parent
            onClicked: { depthChange = 0; updateDepth()}
        }
    }
    Button {
        text: "↓"
        MouseArea {
            anchors.fill: parent
            onClicked: { if(depthChange < 1)depthChange += 1; updateDepth()}
        }
    }
}
