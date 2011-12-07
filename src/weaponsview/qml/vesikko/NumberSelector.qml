import QtQuick 1.0

Column {
    property int value: 0
    property int maxValue: 9
    Button {
        width: parent.width
        height: parent.height/3
        text: "+"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                parent.parent.value += 1;
                if(parent.parent.value > maxValue)
                    parent.parent.value = 0;
            }
        }
    }
    Rectangle {
        width: parent.width
        height: parent.height/3
        gradient: Gradient {
            GradientStop { position: 0.0; color: "gray" }
            GradientStop { position: 0.5; color: "white" }
            GradientStop { position: 1.0; color: "gray" }
        }
        Text {
            anchors.centerIn: parent
            text: parent.parent.value + ""
            color: "black"
            font.pointSize: 20
        }
    }
    Button {
        width: parent.width
        height: parent.height/3
        text: "-"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                parent.parent.value -= 1;
                if(parent.parent.value < 0)
                    parent.parent.value = maxValue;
            }
        }

    }
}
