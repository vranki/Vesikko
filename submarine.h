#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <QObject>

class Submarine : public QObject
{
    Q_OBJECT
public:
    explicit Submarine(QObject *parent = 0);
    double x, y, depth, verticalVelocity, heading, speed, helm;
signals:

public slots:
    void setHelm(int h);
    void setSpeed(int s);
    void setDepthChange(int s);
};

#endif // SUBMARINE_H
