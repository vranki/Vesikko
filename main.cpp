#include <QtGui/QApplication>
#include <QDebug>
#include <QDeclarativeView>
#include <QGraphicsObject>
#include <QDeclarativeItem>
#include <QMainWindow>
#include "qmlapplicationviewer.h"
#include "simulation.h"
#include "mapqmlupdater.h"

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
    QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(object);
    QObject *sub = object->findChild<QObject*>("sub");
    QObject *helm = item->findChild<QObject*>("helm");
    QObject *speed = item->findChild<QObject*>("speed");
    Simulation simulation;
    MapQmlUpdater mqu(0, sub, helm);

    QObject::connect(&simulation, SIGNAL(subMoved(Submarine*)), &mqu, SLOT(subMoved(Submarine*)));
    QObject::connect(helm, SIGNAL(setHelm(int)), simulation.getSub(), SLOT(setHelm(int)));
    QObject::connect(speed, SIGNAL(setSpeed(int)), simulation.getSub(), SLOT(setSpeed(int)));
    return app.exec();
}
