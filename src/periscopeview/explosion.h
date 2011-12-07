#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>

#include <osg/Group>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>

#include <osgParticle/ParticleSystem>
#include <osgParticle/Particle>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/ModularEmitter>
#include <osgParticle/ModularProgram>
#include <osgParticle/AccelOperator>
#include <osgParticle/RandomRateCounter>
#include <osgParticle/PointPlacer>
#include <osgParticle/RadialShooter>

class Explosion : public QObject
{
    Q_OBJECT
public:
    explicit Explosion(QObject *parent = 0);
    osg::Group& getGroup();
    osg::PositionAttitudeTransform& getPat();
    void setEnabled(bool e);
signals:

public slots:
private:
    osg::Group *                            root;
    osg::Geode *                            geode;
    osgParticle::ModularEmitter *           emitter;
    osgParticle::ParticleSystem *           particleSystem;
    osgParticle::Particle *                 defaultParticle;
    osgParticle::ParticleSystemUpdater *    updater;
    osgParticle::RandomRateCounter *        rateCounter;
    osgParticle::PointPlacer *              placer;
    osgParticle::RadialShooter *            shooter;
    osg::PositionAttitudeTransform *        pat;

};

#endif // EXPLOSION_H
