TARGET=vesikko

QT += declarative gui

LIBS += -L../mapview -lmapview
CONFIG += link_prl

# If periscopeview included
CONFIG += link_pkgconfig
PKGCONFIG += openscenegraph
LIBS += -losgOcean
#LIBS += -static -L../periscopeview -lperiscopeview -dynamic
#LIBS += -static -L../mapview -lmapview -dynamic
LIBS +=  ../periscopeview/libperiscopeview.a
LIBS +=  ../mapview/libmapview.a

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    simulation.cpp \
    vessel.cpp \
    torpedo.cpp

HEADERS += \
    simulation.h \
    vessel.h \
    torpedo.h


