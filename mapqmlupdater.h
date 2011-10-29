#ifndef MAPQMLUPDATER_H
#define MAPQMLUPDATER_H
#include "submarine.h"
#include <QObject>

class MapQmlUpdater : public QObject
{
    Q_OBJECT
public:
    explicit MapQmlUpdater(QObject *parent, QObject *s, QObject *h);
    double getHelm();
signals:

public slots:
    void subMoved(Submarine *sub);
private:
    QObject *subObject, helmObject;
};

#endif // MAPQMLUPDATER_H
