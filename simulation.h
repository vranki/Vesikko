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
private slots:
    void tick();

public slots:

private:
    QTimer timer;
    QTime time;
    Vessel sub;
    QList<Vessel*> otherVessels;
    int lastVesselId;
};

#endif // SIMULATION_H
