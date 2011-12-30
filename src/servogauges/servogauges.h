#ifndef SERVOGAUGES_H
#define SERVOGAUGES_H

#include <QObject>
#include <QTimer>

#include "servocontroller.h"

class Vessel;

class ServoGauges : public QObject
{
    Q_OBJECT
public:
    explicit ServoGauges(QObject *parent = 0);
    
signals:
    
public slots:
    void vesselUpdated(Vessel* vessel);
private slots:
    void updateServos();
private:
    ServoController controller;
    QTimer updateTimer;
    double speed, depth;
};

#endif // SERVOGAUGES_H
