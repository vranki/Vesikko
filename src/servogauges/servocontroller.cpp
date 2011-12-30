#include "servocontroller.h"

ServoController::ServoController(QObject *parent) :
    QObject(parent)
{
    for(int i=0;i<SERVOCOUNT;i++)
        servoPos[i] = -1;
    fd = -1;
}

ServoController::~ServoController() {
    if (fd >= 0) { // center servos & close the serial port
        for(int i=0;i<SERVOCOUNT;i++)
            setPosRaw(i, 127);
        close(fd);
    }
}

void ServoController::setPosScaled(int servo, double pos) {
//    qDebug() << Q_FUNC_INFO << servo << pos;
    if(pos < 0) pos = 0;
    if(pos > 1) pos = 1;
    int rawPos = SERVO_POS_MIN + (double)(SERVO_POS_MAX - SERVO_POS_MIN) * pos;
    setPosRaw(servo, rawPos);
}

void ServoController::setPosRaw(int servo, int pos) {
        if(fd < 1) return;
        if(servoPos[servo] == pos) return;
        // Limits
        if(pos < SERVO_POS_MIN) pos = SERVO_POS_MIN;
        if(pos > SERVO_POS_MAX) pos = SERVO_POS_MAX;
        Q_ASSERT(pos >=0 && pos < 256);
        char foo[3];
        foo[0] = 0xff;
        foo[1] = servo + 8;
        foo[2] = pos;
        write(fd, foo, 3);
        servoPos[servo] = pos;
//        qDebug() << Q_FUNC_INFO << pos;
}

int ServoController::currentPos(int servo) {
    if(servo < 0 || servo > SERVOCOUNT) return -1;
    return servoPos[servo];
}


bool ServoController::openSerial() {
    qDebug() << Q_FUNC_INFO;
    struct termios newtio;

    //open the device(com port) to be non-blocking (read will return immediately)
    fd = open(DEVICENAME, O_WRONLY | O_NOCTTY);
    if (fd < 0) {
        perror(DEVICENAME);
        return false;
    } else {
        // set new port settings for canonical input processing
        newtio.c_cflag = B9600 | CRTSCTS | CS8 | 1 | 0 | 0 | CLOCAL/* | CREAD*/;
        newtio.c_iflag = IGNPAR;
        newtio.c_oflag = 0;
        newtio.c_lflag = 0;       //ICANON;
        newtio.c_cc[VMIN]=1;
        newtio.c_cc[VTIME]=0;
        tcflush(fd, TCIFLUSH);
        tcsetattr(fd,TCSANOW,&newtio);
        for(int i=0;i<SERVOCOUNT;i++)
            setPosRaw(i, 127);
    }

    qDebug() << Q_FUNC_INFO << DEVICENAME << "opened successfully";
    return true;
}
