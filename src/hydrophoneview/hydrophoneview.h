#pragma once

#include <QObject>
#include <QDeclarativeView>
#include <QMainWindow>
class Vessel;

class HydrophoneView : public QObject {
Q_OBJECT

public:
    HydrophoneView(QObject *parent = 0);
public slots:
    void vesselUpdated(Vessel* vessel);
private slots:
    void hydrophoneDirectionChanged(double dir);
private:
    QDeclarativeView *view;
    QMainWindow mainWin;
    QObject *hydrophoneViewObject;
};
