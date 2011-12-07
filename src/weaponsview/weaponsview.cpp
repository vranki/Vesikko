#include "weaponsview.h"
#include <QDebug>
#include <QGraphicsObject>
#include <QDeclarativeItem>
#include <QCoreApplication>

WeaponsView::WeaponsView(QObject *parent) : QObject(parent), mainWin()
{
    view = new QDeclarativeView(&mainWin);
    view->setSource(QUrl::fromLocalFile("src/weaponsview/qml/vesikko/WeaponsView.qml"));
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    mainWin.setGeometry(QRect(500,0,500,150));
    mainWin.setCentralWidget(view);
    mainWin.setWindowTitle("Vesikko Weapons");
    mainWin.show();

    QGraphicsObject *object = view->rootObject();
    if(!object) {
        qDebug() << "No root object - QML missing?";
        return;
    }
    QObject::connect(object, SIGNAL(fireTorpedo(double)), this, SIGNAL(fireTorpedo(double)));
    connect(&mainWin, SIGNAL(destroyed()), QCoreApplication::instance(), SLOT(quit()));
}
