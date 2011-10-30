#include "submarine.h"
#include <QDebug>

Submarine::Submarine(QObject *parent) :
    QObject(parent)
{
    x = y = depth = heading = speed = helm = verticalVelocity = 0;
}
void Submarine::setHelm(int h){
    helm = h;
}
void Submarine::setSpeed(int s){
    if(s == -1) speed = -5;
    if(s == 0) speed = 0;
    if(s == 1) speed = 5;
    if(s == 2) speed = 10;
    if(s == 3) speed = 20;
}
void Submarine::setDepthChange(int s){
    if(s == -1) verticalVelocity = -5;
    if(s == 0) verticalVelocity = 0;
    if(s == 1) verticalVelocity = 5;
}
