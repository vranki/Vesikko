#pragma once

#include <QObject>
#include <QDeclarativeView>
#include <QMainWindow>

class HydrophoneView : public QObject {
Q_OBJECT

public:
    HydrophoneView(QObject *parent = 0);

private:
    QDeclarativeView *view;
    QMainWindow mainWin;
};
