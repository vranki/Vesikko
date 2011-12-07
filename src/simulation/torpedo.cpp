#include "torpedo.h"

Torpedo::Torpedo(QObject *parent, int i) : Vessel(parent, i)
{
    type = 2;
    speedCommand = 50;
    acceleration = 5;
    QTimer::singleShot(50000, this, SLOT(deleteLater()));
}
