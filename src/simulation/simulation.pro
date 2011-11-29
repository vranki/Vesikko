TARGET=vesikko

QT += declarative gui

LIBS += -L../mapview -lmapview
CONFIG += link_prl

# If periscopeview included
CONFIG += link_pkgconfig
PKGCONFIG += openscenegraph
LIBS += -L/usr/local/lib -losgOcean
LIBS += -L../periscopeview -lperiscopeview

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    simulation.cpp \
    vessel.cpp

HEADERS += \
    simulation.h \
    vessel.h
