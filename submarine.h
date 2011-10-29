#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <QObject>

class Submarine : public QObject
{
    Q_OBJECT
public:
    explicit Submarine(QObject *parent = 0);
    double x, y, z, heading, speed, helm;
signals:

public slots:
    void setHelm(int h);
};

#endif // SUBMARINE_H
