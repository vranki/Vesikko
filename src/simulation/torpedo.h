#ifndef TORPEDO_H
#define TORPEDO_H
#include "vessel.h"
#include <QTimer>
class Torpedo : public Vessel
{
    Q_OBJECT
public:
    explicit Torpedo(QObject *parent, int id);

signals:

public slots:
};

#endif // TORPEDO_H
