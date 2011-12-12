TEMPLATE=lib
TARGET=periscopeview
CONFIG += staticlib
CONFIG += link_pkgconfig
CONFIG += create_prl
PKGCONFIG += openscenegraph

LIBS += -L/usr/local/lib -losgOcean

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += periscopeview.cpp \
    SkyDome.cpp \
    SphereSegment.cpp \
    explosion.cpp

HEADERS += periscopeview.h \
    explosion.h\
    TextHUD.h



