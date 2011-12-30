#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <termios.h>
#include <fcntl.h>
#define DEVICENAME "/dev/ttyUSB0"
#define SERVOCOUNT 1
#define SERVO_POS_MIN 22
#define SERVO_POS_MAX 220

class ServoController : public QObject
{
    Q_OBJECT
public:
    explicit ServoController(QObject *parent = 0);
    ~ServoController();
    void setPosRaw(int servo, int pos);
    void setPosScaled(int servo, double pos);
    int currentPos(int servo);
    bool openSerial();
signals:

public slots:


private:
    int servoPos[SERVOCOUNT];
    int fd;
};

#endif // SERVOCONTROLLER_H
