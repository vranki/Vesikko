#include "hydrophoneview.h"
#include <QDebug>
#include <QGraphicsObject>
#include <QDeclarativeItem>
#include <QCoreApplication>
#include "../simulation/vessel.h"

HydrophoneView::HydrophoneView(QObject *parent) : QObject(parent), mainWin()
{
    view = new QDeclarativeView(&mainWin);
    view->setSource(QUrl::fromLocalFile("src/hydrophoneview/qml/vesikko/HydrophoneView.qml"));
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    mainWin.setGeometry(QRect(500,400,500,500));
    mainWin.setCentralWidget(view);
    mainWin.setWindowTitle("Vesikko Hydrophone");
    mainWin.show();

    QGraphicsObject *object = view->rootObject();
    if(!object) {
        qDebug() << "No root object - QML missing?";
        return;
    }
    hydrophoneViewObject = object;
    QObject::connect(hydrophoneViewObject, SIGNAL(hydrophoneDirectionChangedSignal(double)),
                     this, SLOT(hydrophoneDirectionChanged(double)));

    connect(&mainWin, SIGNAL(destroyed()), QCoreApplication::instance(), SLOT(quit()));
}

void HydrophoneView::vesselUpdated(Vessel* vessel) {
    if(vessel->id==0) {
        QMetaObject::invokeMethod(hydrophoneViewObject, "subDirectionChanged",
                                  Q_ARG(QVariant, vessel->heading));
    }
}

void HydrophoneView::hydrophoneDirectionChanged(double dir) {
    qDebug() << Q_FUNC_INFO << dir;
}
