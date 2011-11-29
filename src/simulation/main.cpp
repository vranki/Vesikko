#include <QtGui/QApplication>
#include <QDebug>
#include <QMainWindow>
#include "simulation.h"
#include "../mapview/mapqmlupdater.h"
#include "../mapview/mapview.h"
#include "../periscopeview/periscopeview.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Simulation simulation;
    MapView mapView;
    QObject::connect(&simulation, SIGNAL(vesselUpdated(Vessel*)), mapView.mqu, SLOT(vesselUpdated(Vessel*)));
    QObject::connect(&simulation, SIGNAL(vesselCreated(Vessel*)), mapView.mqu, SLOT(createVessel(Vessel*)));
    QObject::connect(&mapView, SIGNAL(setHelm(int)), simulation.getSub(), SLOT(setHelm(int)));
    QObject::connect(&mapView, SIGNAL(setSpeed(int)), simulation.getSub(), SLOT(setSpeed(int)));
    QObject::connect(&mapView, SIGNAL(setDepthChange(int)), simulation.getSub(), SLOT(setDepthChange(int)));
    PeriscopeView periscope;
    QObject::connect(&simulation, SIGNAL(vesselUpdated(Vessel*)), &periscope, SLOT(vesselUpdated(Vessel*)));
    QObject::connect(&simulation, SIGNAL(vesselCreated(Vessel*)), &periscope, SLOT(createVessel(Vessel*)));
    QObject::connect(&simulation, SIGNAL(tickTime(double, int)), &periscope, SLOT(tick(double, int)));

    simulation.startSimulation();
    /*
    foreach(QObject *child, object->children()) {
        qDebug() << "Object " << child->objectName() << " in " << object;
    }
*/
    return app.exec();
}
