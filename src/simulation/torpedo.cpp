#include "torpedo.h"
#include <math.h>

Torpedo::Torpedo(QObject *parent, int i) : Vessel(parent, i)
{
    type = 2;
    speedCommand = 50;
    acceleration = 5;
    headingCommand = heading;
    QTimer::singleShot(50000, this, SLOT(deleteLater()));
}
void Torpedo::tickTime(double dt, int total) {
    Vessel::tickTime(dt, total);

    if(qAbs(heading - headingCommand) < 0.5) {
        setHelm(0);
        return;
    }

    double x1,y1,x2,y2;
    x1=sinf(heading * (M_PI/180.0));
    y1=cosf(heading * (M_PI/180.0));
    x2=sinf(headingCommand * (M_PI/180.0));
    y2=cosf(headingCommand * (M_PI/180.0));
    double cross = x1*y2 - y1*x2;
    if(cross < 0) setHelm(2);
    else setHelm(-2);
}
