#include "submarine.h"
#include <QDebug>

Submarine::Submarine(QObject *parent) :
    QObject(parent)
{
    x = y = z = heading = speed = helm = 0;
}
void Submarine::setHelm(int h){
    helm = h;
}
