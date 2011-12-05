TEMPLATE=lib
TARGET=mapview
CONFIG += create_prl
QT += declarative gui

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += mapqmlupdater.cpp \
    mapview.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += mapqmlupdater.h \
    mapview.h



