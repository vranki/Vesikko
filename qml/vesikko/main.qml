import QtQuick 1.0

Rectangle {
    id: map
    color: "lightblue"
    property real scaling: 1.0
    property int helm: 0
    signal setHelm(int helm)

    Text {
        id: scaleText
        text: "Map Scale " + parent.width / parent.scaling + "m"
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Text {
        id: statusText
        text: ""
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: scaleText.bottom
    }
    Image {
        id: sub
        objectName: "sub"
        source: "sub.png"
        smooth: true
        property real rudder: 0
        property real lat: 0
        property real lon: 0
        x: parent.width / 2 + lat * scaling
        y: parent.height / 2 + lon * scaling
    }

    Rectangle {
        id: helmLeft
        width: 40
        height: width
        anchors.bottom: parent.bottom
        radius: 5
        color: "gray"
        Text {
            color: "white"
            text: qsTr("<-")
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: { if(map.helm > -3) map.helm -= 1; map.setHelm(map.helm);
                if(map.helm==-1)  statusText.text="Rudder quarter left";
                if(map.helm==-2)  statusText.text="Rudder left";
                if(map.helm==-3)  statusText.text="Rudder full left";
            }
        }
    }
    Rectangle {
        id: helmStraight
        width: 40
        height: width
        anchors.left: helmLeft.right
        anchors.top: helmLeft.top
        color: "gray"
        radius: 5
        Text {
            color: "white"
            text: qsTr("|")
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: { map.helm = 0; map.setHelm(map.helm); statusText.text="Helm straight"}
        }
    }

    Rectangle {
        id: helmRight
        width: 40
        height: width
        radius: 5
        anchors.left: helmStraight.right
        anchors.top: helmStraight.top
        color: "gray"
        Text {
            color: "white"
            text: qsTr("->")
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {if(map.helm < 3)  map.helm += 1; map.setHelm(map.helm);
                if(map.helm==1)  statusText.text="Rudder quarter right";
                if(map.helm==2)  statusText.text="Rudder right";
                if(map.helm==3)  statusText.text="Rudder full right";
            }
        }
    }

    Rectangle {
        width: 40
        height: width
        anchors.right: parent.right
        color: "gray"
        radius: 5
        Text {
            color: "white"
            text: qsTr("+")
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: { parent.parent.scaling *= 2.0}
        }
    }
    Rectangle {
        width: 40
        height: width
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        radius: 5
        color: "gray"
        Text {
            color: "white"
            text: qsTr("-")
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: { parent.parent.scaling /= 2.0}
        }
    }
}
