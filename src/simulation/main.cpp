#include <QtGui/QApplication>
#include <QDebug>
#include <QMainWindow>
#include <QTimer>
#include "simulation.h"
#include "../mapview/mapqmlupdater.h"
#include "../mapview/mapview.h"
#include "../periscopeview/periscopeview.h"
#include "../weaponsview/weaponsview.h"
#include "../hydrophoneview/hydrophoneview.h"
#include "../servogauges/servogauges.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Simulation simulation;
    MapView mapView;
    WeaponsView weaponsView;
    HydrophoneView hydrophoneView;
    ServoGauges servoGauges;
    QObject::connect(&simulation, SIGNAL(vesselUpdated(Vessel*)), &mapView.mqu, SLOT(vesselUpdated(Vessel*)));
    QObject::connect(&simulation, SIGNAL(vesselCreated(Vessel*)), &mapView.mqu, SLOT(createVessel(Vessel*)));
    QObject::connect(&simulation, SIGNAL(vesselDeleted(Vessel*)), &mapView.mqu, SLOT(vesselDeleted(Vessel*)));
    QObject::connect(&mapView, SIGNAL(setHelm(int)), simulation.getSub(), SLOT(setHelm(int)));
    QObject::connect(&mapView, SIGNAL(setSpeed(int)), simulation.getSub(), SLOT(setSpeed(int)));
    QObject::connect(&mapView, SIGNAL(setDepthChange(int)), simulation.getSub(), SLOT(setDepthChange(int)));
    QObject::connect(&weaponsView, SIGNAL(fireTorpedo(double)), &simulation, SLOT(fireTorpedo(double)));
    QObject::connect(&simulation, SIGNAL(vesselUpdated(Vessel*)), &hydrophoneView, SLOT(vesselUpdated(Vessel*)));
    QObject::connect(&simulation, SIGNAL(vesselUpdated(Vessel*)), &servoGauges, SLOT(vesselUpdated(Vessel*)));

    PeriscopeView *periscope = 0;
    // periscope = new PeriscopeView(&app);
    if(periscope) {
        QObject::connect(&simulation, SIGNAL(vesselUpdated(Vessel*)), periscope, SLOT(vesselUpdated(Vessel*)));
        QObject::connect(&simulation, SIGNAL(vesselCreated(Vessel*)), periscope, SLOT(createVessel(Vessel*)));
        QObject::connect(&simulation, SIGNAL(vesselDeleted(Vessel*)), periscope, SLOT(vesselDeleted(Vessel*)));
        QObject::connect(&simulation, SIGNAL(tickTime(double, int)), periscope, SLOT(tick(double, int)));
        QObject::connect(periscope, SIGNAL(collisionBetween(Vessel*,Vessel*)), &simulation, SLOT(collisionBetween(Vessel*,Vessel*)));
        QObject::connect(&simulation, SIGNAL(explosion(double,double,double)), periscope, SLOT(addExplosion(double,double,double)));
    }
    QTimer::singleShot(1, &simulation, SLOT(startSimulation()));
    return app.exec();
}
