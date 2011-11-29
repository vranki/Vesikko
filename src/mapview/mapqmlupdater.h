#ifndef MAPQMLUPDATER_H
#define MAPQMLUPDATER_H
#include "../simulation/vessel.h"
#include <QObject>

class MapQmlUpdater : public QObject
{
    Q_OBJECT
public:
    explicit MapQmlUpdater(QObject *parent, QObject *s, QObject *h, QObject *v);
signals:

public slots:
    void vesselUpdated(Vessel *v);
    void createVessel(Vessel *v);
    void vesselDeleted(Vessel *v);
private:
    QObject *subObject, *helmObject, *vesselsObject;
};

#endif // MAPQMLUPDATER_H
