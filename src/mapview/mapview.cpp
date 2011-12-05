#include <QDebug>
#include <QGraphicsObject>
#include <QDeclarativeItem>
#include <QCoreApplication>
#include "mapview.h"
#include "qmlapplicationviewer.h"

MapView::MapView(QObject *parent) : QObject(parent), mainWin(), mqu(this) {
    view = new QDeclarativeView(&mainWin);
    view->setSource(QUrl::fromLocalFile("src/mapview/qml/vesikko/main.qml"));
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    mainWin.setGeometry(QRect(0,0,500,500));
    mainWin.setCentralWidget(view);
    mainWin.setWindowTitle("Vesikko");
    mainWin.show();

    QGraphicsObject *object = view->rootObject();
    if(!object) {
        qDebug() << "No root object - QML missing?";
        return;
    }
    QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(object);
    QObject *sub = object->findChild<QObject*>("sub");
    QObject *helm = item->findChild<QObject*>("helm");
    QObject *speed = item->findChild<QObject*>("speed");
    QObject *depth = item->findChild<QObject*>("depth");
    if(!sub) {
        qDebug() << "No sub object - QML missing?";
        return;
    }
    QObject::connect(helm, SIGNAL(setHelm(int)), this, SIGNAL(setHelm(int)));
    QObject::connect(speed, SIGNAL(setSpeed(int)), this, SIGNAL(setSpeed(int)));
    QObject::connect(depth, SIGNAL(setDepthChange(int)), this, SIGNAL(setDepthChange(int)));

    mqu.init(sub, helm, object);

    connect(&mainWin, SIGNAL(destroyed()), QCoreApplication::instance(), SLOT(quit()));
}
