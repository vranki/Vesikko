#include "simulation.h"
#include <QDebug>
#include <math.h>

Simulation::Simulation(QObject *parent) : QObject(parent), lastVesselId(0), sub(this, 0)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer.setSingleShot(false);
    timer.setInterval(50);
}

void Simulation::startSimulation() {
    timer.start();
    time.start();
    Vessel *v = new Vessel(this, ++lastVesselId);
    v->x = 30;
    v->y = 20;
    otherVessels.append(v);
    emit vesselCreated(v);
}

void Simulation::tick() {
    double dt = time.elapsed() / 1000.0d;
    time.start();
    sub.x += sin(sub.heading * (M_PI/180.0)) * sub.speed * dt;
    sub.y -= cos(sub.heading * (M_PI/180.0)) * sub.speed * dt;
    sub.depth += sub.verticalVelocity * dt;
    if(sub.depth < 0) sub.depth = 0;
    sub.heading += sub.helm * 3 * dt;
    emit vesselUpdated(&sub);
}

Vessel *Simulation::getSub() {
    return &sub;
}
