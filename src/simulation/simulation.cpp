#include "simulation.h"
#include "torpedo.h"
#include <QDebug>

Simulation::Simulation(QObject *parent) : QObject(parent), lastVesselId(0), sub(this, 0)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer.setSingleShot(false);
    timer.setInterval(50);
    connect(this, SIGNAL(tickTime(double,int)), &sub, SLOT(tickTime(double,int)));
    connect(&sub, SIGNAL(vesselUpdated(Vessel*)), this, SIGNAL(vesselUpdated(Vessel*)));
}

void Simulation::startSimulation() {
    timer.start();
    totalTime.start();
    time.start();
    Vessel *v = new Vessel(this, ++lastVesselId);
    v->x = 500;
    v->y = -1000;
    v->heading = 90;
    v->type = 1;
    v->speed =10;
    v->setHelm(1);
    otherVessels.append(v);
    connect(this, SIGNAL(tickTime(double,int)), v, SLOT(tickTime(double,int)));
    connect(v, SIGNAL(vesselUpdated(Vessel*)), this, SIGNAL(vesselUpdated(Vessel*)));
    connect(v, SIGNAL(destroyed()), this, SLOT(vesselDestroyed()));
    emit vesselCreated(v);
    v = new Vessel(this, ++lastVesselId);
    v->x = 2000;
    v->y = -200;
    v->heading = 70;
    v->type = 1;
    v->speed =10;
    otherVessels.append(v);
    connect(this, SIGNAL(tickTime(double,int)), v, SLOT(tickTime(double,int)));
    connect(v, SIGNAL(vesselUpdated(Vessel*)), this, SIGNAL(vesselUpdated(Vessel*)));
    connect(v, SIGNAL(destroyed()), this, SLOT(vesselDestroyed()));
    emit vesselCreated(v);
    v = new Vessel(this, ++lastVesselId);
    v->x = -500;
    v->y = -2000;
    v->heading = -45;
    v->type = 1;
    v->speed =10;
    v->setHelm(1);
    otherVessels.append(v);
    connect(this, SIGNAL(tickTime(double,int)), v, SLOT(tickTime(double,int)));
    connect(v, SIGNAL(vesselUpdated(Vessel*)), this, SIGNAL(vesselUpdated(Vessel*)));
    connect(v, SIGNAL(destroyed()), this, SLOT(vesselDestroyed()));
    emit vesselCreated(v);
    v = new Vessel(this, ++lastVesselId);
    v->x = 3000;
    v->y = 2000;
    v->heading = 70;
    v->type = 1;
    v->speed =5;
    v->setHelm(-1);
    otherVessels.append(v);
    connect(this, SIGNAL(tickTime(double,int)), v, SLOT(tickTime(double,int)));
    connect(v, SIGNAL(vesselUpdated(Vessel*)), this, SIGNAL(vesselUpdated(Vessel*)));
    connect(v, SIGNAL(destroyed()), this, SLOT(vesselDestroyed()));
    emit vesselCreated(v);
}

void Simulation::tick() {
    double dt = time.elapsed() / 1000.0f;
    time.start();
    if(dt > 0.2) {
        qDebug() << "Skipping frame, dt: " << dt;
        dt = 0;
    }
    emit tickTime(dt, totalTime.elapsed());
}

Vessel *Simulation::getSub() {
    return &sub;
}

void Simulation::fireTorpedo(double direction) {
    Torpedo *v = new Torpedo(this, ++lastVesselId);
    v->x = sub.x;
    v->y = sub.y;
    v->heading = sub.heading;
    v->speed = sub.speed + 10;
    v->headingCommand = direction;
    otherVessels.append(v);
    connect(this, SIGNAL(tickTime(double,int)), v, SLOT(tickTime(double,int)));
    connect(v, SIGNAL(vesselUpdated(Vessel*)), this, SIGNAL(vesselUpdated(Vessel*)));
    connect(v, SIGNAL(destroyed()), this, SLOT(vesselDestroyed()));
    emit vesselCreated(v);
}

void Simulation::vesselDestroyed() {
    Vessel *v = static_cast<Vessel*> (sender());
    emit vesselDeleted(v);
    otherVessels.removeAll(v);
}

void Simulation::collisionBetween(Vessel *v, Vessel *v2) {
    if(!v || !v2) return;
    if(v->type==2 && v2->type==2) return;
    Q_ASSERT(otherVessels.contains(v));
    Q_ASSERT(otherVessels.contains(v2));
    Vessel *torpedo, *target;
    torpedo = 0;
    target = 0;
    if(v->type==2) {
        torpedo = v;
        target = v2;
    }
    if(v2->type==2) {
        torpedo = v2;
        target = v;
    }
    qDebug() << "Torpedo " << torpedo << "hit ship " << target;
    emit explosion(torpedo->x, torpedo->y, 1);
    delete torpedo;
    target->wasHitByTorpedo();
}
