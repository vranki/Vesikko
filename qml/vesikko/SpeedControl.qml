import QtQuick 1.0



Row {
    property int speed: 0
    signal setSpeed(int speed)
    id: speedPanel

    function updateSpeed() {
        if(speed==-1) statusText.text = "Reverse"
        if(speed==0) statusText.text = "Full Stop"
        if(speed==1) statusText.text = "Silent running"
        if(speed==2) statusText.text = "Cruise speed"
        if(speed==3) statusText.text = "Flank speed"
        speedPanel.setSpeed(speed)
    }

    Button {
        text: "-"
        MouseArea {
            anchors.fill: parent
            onClicked: { if(speed > -1) speed -= 1; updateSpeed()}
        }
    }
    Button {
        text: "+"
        MouseArea {
            anchors.fill: parent
            onClicked: { if(speed < 3)speed += 1; updateSpeed()}
        }
    }
}
