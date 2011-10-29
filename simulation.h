#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include "submarine.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(QObject *parent = 0);
    Submarine *getSub();
signals:
    void subMoved(Submarine *sub);

private slots:
    void tick();

public slots:

private:
    QTimer timer;
    QTime time;
    Submarine sub;
};

#endif // SIMULATION_H
