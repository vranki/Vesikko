import QtQuick 1.0

Rectangle {
    id: weaponsView
    color: "black"
    signal fireTorpedo(double direction)

    Button {
        id: firebutton
        anchors.verticalCenter: parent.verticalCenter
        text: "Fire"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                var heading = 0;
                heading += num1.value*100;
                heading += num2.value*10;
                heading += num3.value;
                while(heading > 360)
                    heading -= 360;
                console.log("fire in " + heading);
                weaponsView.fireTorpedo(heading);
            }
        }
    }

    Row {
        anchors.left: firebutton.right
        anchors.verticalCenter: parent.verticalCenter

        NumberSelector {
            id: num1
            width: 50
            height: 200
            maxValue: 3
        }
        NumberSelector {
            id: num2
            width: 50
            height: 200
        }
        NumberSelector {
            id: num3
            width: 50
            height: 200
        }
    }
}
