#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QList>
#include "vessel.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(QObject *parent = 0);
    void startSimulation();
    Vessel *getSub();
signals:
    void vesselUpdated(Vessel *v);
    void vesselCreated(Vessel *v);
    void vesselDeleted(Vessel *v);
    void tickTime(double dt, int total);
private slots:
    void tick();
    void vesselDestroyed();
public slots:
    void fireTorpedo(double direction);

private:
    QTimer timer;
    QTime time, totalTime;
    Vessel sub;
    QList<Vessel*> otherVessels;
    int lastVesselId;
};

#endif // SIMULATION_H
