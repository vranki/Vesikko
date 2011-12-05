#include "torpedo.h"

Torpedo::Torpedo(QObject *parent, int i) : Vessel(parent, i)
{
    type = 2;
    speed = 50;
    QTimer::singleShot(5000, this, SLOT(deleteLater()));
}
