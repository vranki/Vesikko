#include "servogauges.h"
#include "../simulation/vessel.h"

ServoGauges::ServoGauges(QObject *parent) :
    QObject(parent)
{
    speed = depth = 0;
    if(controller.openSerial()) {
        connect(&updateTimer, SIGNAL(timeout()), this, SLOT(updateServos()));
        updateTimer.setSingleShot(false);
        updateTimer.setInterval(100);
        updateTimer.start();
    }
}

void ServoGauges::vesselUpdated(Vessel* vessel) {
    if(vessel->id==0) {
        speed = vessel->speed;
        depth = vessel->depth;
    }
}

void ServoGauges::updateServos() {
    controller.setPosScaled(0, 1.0d-speed / 30.0d);
}
