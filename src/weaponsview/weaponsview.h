#ifndef WEAPONSVIEW_H
#define WEAPONSVIEW_H


#include <QObject>
#include <QDeclarativeView>
#include <QMainWindow>

class WeaponsView : public QObject {
Q_OBJECT

public:
    WeaponsView(QObject *parent = 0);
signals:
    void fireTorpedo(double dir);
private:
    QDeclarativeView *view;
    QMainWindow mainWin;
};

#endif // WEAPONSVIEW_H
