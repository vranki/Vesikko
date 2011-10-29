#include "simulation.h"
#include <QDebug>
#include <math.h>

Simulation::Simulation(QObject *parent) :
    QObject(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer.setSingleShot(false);
    timer.setInterval(50);
    timer.start();
    time.start();
}

void Simulation::tick() {
    double dt = time.elapsed() / 1000.0d;
    time.start();
    sub.x += sin(sub.heading * (M_PI/180.0)) * sub.speed * dt;
    sub.y -= cos(sub.heading * (M_PI/180.0)) * sub.speed * dt;
    sub.heading += sub.helm * 3 * dt;
    emit subMoved(&sub);
}

Submarine *Simulation::getSub() {
    return &sub;
}
