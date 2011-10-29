#include "mapqmlupdater.h"
#include "submarine.h"
#include <QVariant>
#include <QDebug>

MapQmlUpdater::MapQmlUpdater(QObject *parent, QObject *s, QObject *h) :
    QObject(parent), subObject(s), helmObject(h)
{
}

void MapQmlUpdater::subMoved(Submarine *sub) {
    subObject->setProperty("lat", sub->x);
    subObject->setProperty("lon", sub->y);
    subObject->setProperty("rotation", sub->heading);
}

double MapQmlUpdater::getHelm() {
    return helmObject.property("helm").toDouble();
}
