#ifndef TORPEDO_H
#define TORPEDO_H
#include "vessel.h"
#include <QTimer>
class Torpedo : public Vessel
{
    Q_OBJECT
public:
    explicit Torpedo(QObject *parent, int id);
    double headingCommand;
signals:

public slots:
    virtual void tickTime(double dt, int total);
};

#endif // TORPEDO_H
