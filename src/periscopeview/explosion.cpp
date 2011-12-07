#include "explosion.h"

Explosion::Explosion(QObject *parent) :
    QObject(parent),
    root(new osg::Group()),
    geode(new osg::Geode()),
    emitter(new osgParticle::ModularEmitter()),
    particleSystem(new osgParticle::ParticleSystem()),
    defaultParticle(new osgParticle::Particle()),
    updater(new osgParticle::ParticleSystemUpdater()),
    rateCounter((osgParticle::RandomRateCounter*)emitter->getCounter()),
    placer((osgParticle::PointPlacer*)emitter->getPlacer()),
    shooter((osgParticle::RadialShooter*)emitter->getShooter()),
    pat(new osg::PositionAttitudeTransform())
{
    //    defaultParticle->setShape(osgParticle::Particle::POINT);
    defaultParticle->setShape(osgParticle::Particle::QUAD_TRIANGLESTRIP);
    defaultParticle->setSizeRange(osgParticle::rangef(0.1, 1));
    defaultParticle->setColorRange(
                osgParticle::rangev4(
                    osg::Vec4f(1.0, 0.0, 0.0, 1.0),
                    osg::Vec4f(0.0, 1.0, 0.0, 1.0)
                    )
                );
    defaultParticle->setLifeTime(6.0);
    // particleSystem->setDefaultAttributes("resources/textures/waterparticle.png");
    particleSystem->setDefaultParticleTemplate(*defaultParticle);
    particleSystem->setParticleAlignment(osgParticle::ParticleSystem::BILLBOARD);

    geode->addDrawable(particleSystem);
    root->addChild(geode);
    updater->addParticleSystem(particleSystem);
    root->addChild(updater);
    rateCounter->setRateRange(500.0, 1000.0);
    shooter->setThetaRange( osgParticle::rangef(0.1, 0.4));
    shooter->setPhiRange( osgParticle::rangef(0.0, 6.2));
    shooter->setInitialSpeedRange( osgParticle::rangef(2, 40.0));
    emitter->setParticleSystem(particleSystem);
    pat->addChild(emitter);
    pat->setPosition( osg::Vec3d(0.0, -0.0, -10.0));


    // Create a modular program and attach it to our particle system
    osgParticle::ModularProgram *moveDustInAir = new osgParticle::ModularProgram;
    moveDustInAir->setParticleSystem(particleSystem);

    // Create an operator that simulates gravity, adjust it and add it to our program
    osgParticle::AccelOperator *accelUp = new osgParticle::AccelOperator;
    accelUp->setToGravity(2); // scale factor for normal acceleration due to gravity.
    moveDustInAir->addOperator(accelUp);

    // Finally, add the program to the scene
    getGroup().addChild(moveDustInAir);

    setEnabled(false);
}

osg::Group& Explosion::getGroup() { return *root; }

osg::PositionAttitudeTransform& Explosion::getPat(){
    return *pat;
}

void Explosion::setEnabled(bool e) {
    emitter->setEnabled(e);
}
