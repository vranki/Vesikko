#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QObject>
#include <QDeclarativeView>
#include <QMainWindow>

#include "mapqmlupdater.h"

class MapView : public QObject
{
    Q_OBJECT
public:
    explicit MapView(QObject *parent = 0);
    MapQmlUpdater mqu;

signals:
    void setHelm(int);
    void setSpeed(int);
    void setDepthChange(int);

public slots:
private:
    QDeclarativeView *view;
    QMainWindow mainWin;
};

#endif // MAPVIEW_H
