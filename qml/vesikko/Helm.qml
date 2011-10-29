import QtQuick 1.0

Row {
    property int helm: 0
    signal setHelm(int helm)
    id: helmPanel
    Button {
        id: helmLeft
        text: "<-"
        MouseArea {
            anchors.fill: parent
            onClicked: { if(helmPanel.helm > -3) helmPanel.helm -= 1; helmPanel.setHelm(helmPanel.helm);
                if(helmPanel.helm==-1)  statusText.text="Rudder 5 degrees left";
                if(helmPanel.helm==-2)  statusText.text="Rudder 20 degrees left";
                if(helmPanel.helm==-3)  statusText.text="Rudder full left";
            }
        }
    }
    Button {
        id: helmStraight

        text: "^"
        MouseArea {
            anchors.fill: parent
            onClicked: { helmPanel.helm = 0; helmPanel.setHelm(helmPanel.helm); statusText.text="Helm straight"}
        }
    }

    Button {
        id: helmRight

        text: "->"
        MouseArea {
            anchors.fill: parent
            onClicked: {if(helmPanel.helm < 3)  helmPanel.helm += 1; helmPanel.setHelm(helmPanel.helm);
                if(helmPanel.helm==1)  statusText.text="Rudder 5 degrees right";
                if(helmPanel.helm==2)  statusText.text="Rudder 20 degrees right";
                if(helmPanel.helm==3)  statusText.text="Rudder full right";
            }
        }
    }

}
