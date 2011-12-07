#ifndef PERISCOPEVIEW_H
#define PERISCOPEVIEW_H

#include <QObject>
#include <QMap>
#include <QTimer>

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osgGA/FirstPersonManipulator>

#include <osgOcean/Version>
#include <osgOcean/OceanScene>
#include <osgOcean/FFTOceanSurface>
#include <osgOcean/SiltEffect>
#include <osgOcean/ShaderManager>

#include "../simulation/vessel.h"
#include "explosion.h"

class SceneEventHandler;

class PeriscopeView : public QObject
{
    Q_OBJECT
public:
    explicit PeriscopeView(QObject *parent = 0);
signals:
    void collisionBetween(Vessel *v, Vessel *v2);
public slots:
    void tick(double dt, int total);
    void vesselUpdated(Vessel *v);
    void createVessel(Vessel *v);
    void vesselDeleted(Vessel *v);
    void setPeriscopeDirection(double dir);
    void addExplosion(double x, double y, double intensity);
private slots:
    void killExplosion();
private:
    void pollKeyboard();
    double periscopeDir;
    double subPitch, subRoll, subYaw;
    osg::Vec4f intColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255 );

    osgViewer::Viewer viewer;
    osg::Node* shipNode;
    osg::ref_ptr<osgOcean::OceanScene> _oceanScene;
    osg::ref_ptr<osgOcean::FFTOceanSurface> _oceanSurface;
    osgGA::FirstPersonManipulator* manipulator;
    std::vector<std::string> _cubemapDirs;
    std::vector<osg::Vec4f>  _lightColors;
    std::vector<osg::Vec4f>  _fogColors;
    std::vector<osg::Vec3f>  _underwaterAttenuations;
    std::vector<osg::Vec4f>  _underwaterDiffuse;

    osg::ref_ptr<osg::Light> _light;

    std::vector<osg::Vec3f>  _sunPositions;
    std::vector<osg::Vec4f>  _sunDiffuse;
    std::vector<osg::Vec4f>  _waterFogColors;
    SceneEventHandler *eventHandler;
    QMap<Vessel *, osg::MatrixTransform*> vesselsTransforms;
    osg::ref_ptr<osg::Node> ship, torpedo;
    Explosion explosion;
    QTimer killExplosionTimer;
};

#endif // PERISCOPEVIEW_H
