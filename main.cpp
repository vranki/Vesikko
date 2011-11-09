#include <QtGui/QApplication>
#include <QDebug>
#include <QDeclarativeView>
#include <QGraphicsObject>
#include <QDeclarativeItem>
#include <QMainWindow>
#include "qmlapplicationviewer.h"
#include "simulation.h"
#include "mapqmlupdater.h"
#include "periscopeview.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainWin;
    QDeclarativeView view;
    view.setSource(QUrl::fromLocalFile("qml/vesikko/main.qml"));
    view.setResizeMode(QDeclarativeView::SizeRootObjectToView);
    view.show();
    mainWin.setGeometry(QRect(0,0,500,500));
    mainWin.setCentralWidget(&view);
    mainWin.setWindowTitle("Vesikko");
    mainWin.show();
    QGraphicsObject *object = view.rootObject();
    if(!object) {
        qDebug() << "No root object - QML missing?";
        return -1;
    }
    QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(object);
    QObject *sub = object->findChild<QObject*>("sub");
    QObject *helm = item->findChild<QObject*>("helm");
    QObject *speed = item->findChild<QObject*>("speed");
    QObject *depth = item->findChild<QObject*>("depth");
    if(!sub) {
        qDebug() << "No sub object - QML missing?";
        return -1;
    }
    Simulation simulation;
    MapQmlUpdater mqu(0, sub, helm, object);

    QObject::connect(&simulation, SIGNAL(vesselUpdated(Vessel*)), &mqu, SLOT(vesselUpdated(Vessel*)));
    QObject::connect(&simulation, SIGNAL(vesselCreated(Vessel*)), &mqu, SLOT(createVessel(Vessel*)));
    QObject::connect(helm, SIGNAL(setHelm(int)), simulation.getSub(), SLOT(setHelm(int)));
    QObject::connect(speed, SIGNAL(setSpeed(int)), simulation.getSub(), SLOT(setSpeed(int)));
    QObject::connect(depth, SIGNAL(setDepthChange(int)), simulation.getSub(), SLOT(setDepthChange(int)));
    PeriscopeView periscope;
    QObject::connect(&simulation, SIGNAL(vesselUpdated(Vessel*)), &periscope, SLOT(vesselUpdated(Vessel*)));
    QObject::connect(&simulation, SIGNAL(vesselCreated(Vessel*)), &periscope, SLOT(createVessel(Vessel*)));
    QObject::connect(&simulation, SIGNAL(tickTime(double, int)), &periscope, SLOT(tick(double, int)));

    simulation.startSimulation();
    foreach(QObject *child, object->children()) {
        qDebug() << "Object " << child->objectName() << " in " << object;
    }

    return app.exec();
}
