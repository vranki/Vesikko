#pragma once
#include <QString>
#include <QObject>
#include <osg/Camera>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>

#include <osgText/Text>
#include <osgText/Font>

// ----------------------------------------------------
//                  Text HUD Class (from osgOcean)
// ----------------------------------------------------


class TextHUD : public QObject
{
private:
    osg::ref_ptr< osg::Camera > _camera;
    osg::ref_ptr< osgText::Text > _headingText;
    osg::ref_ptr< osgText::Text > _distanceText;
    int oldHeading, oldDistance;
public:
    TextHUD( QObject *parent ) : QObject(parent) {
        _camera = createCamera();
        _camera->addChild( createText() );
        oldHeading = -1;
        oldDistance = -1;
    }

    osg::Camera* createCamera( void )
    {
        osg::Camera* camera=new osg::Camera;

        camera->setViewport(0,0,1024,768);
        camera->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
        camera->setProjectionMatrixAsOrtho2D(0,1024,0,768);
        camera->setRenderOrder(osg::Camera::POST_RENDER);
        camera->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
        camera->setClearMask(GL_DEPTH_BUFFER_BIT);

        return camera;
    }

    osg::Node* createText( void )
    {
        osg::Geode* textGeode = new osg::Geode;

        _headingText = new osgText::Text;
        _headingText->setFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
        _headingText->setCharacterSize(80);
        _headingText->setPosition( osg::Vec3f(450.f, 700.f, 0.f ) );
        _headingText->setDataVariance(osg::Object::DYNAMIC);
        _headingText->setColor(osg::Vec4f(0.0,0,0,1.0));
        _headingText->setAlignment(osgText::TextBase::CENTER_CENTER);
        textGeode->addDrawable( _headingText.get() );

        _distanceText = new osgText::Text;
        _distanceText->setFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
        _distanceText->setCharacterSize(30);
        _distanceText->setPosition( osg::Vec3f(512.f, 650.f, 0.f ) );
        _distanceText->setDataVariance(osg::Object::DYNAMIC);
        _distanceText->setColor(osg::Vec4f(0,0,0,1.0));
        _headingText->setAlignment(osgText::TextBase::CENTER_CENTER);
        textGeode->addDrawable( _distanceText.get() );

        osg::PositionAttitudeTransform* titlePAT = new osg::PositionAttitudeTransform;
        titlePAT->addChild(textGeode);
//        setDistance(42);
        return titlePAT;
    }

    osg::Camera* getHudCamera(void)
    {
        return _camera.get();
    }
public slots:
    void setHeading(double heading)
    {
        int newHeading = heading;
        if(newHeading != oldHeading) {
            _headingText->setText( QString::number(newHeading).toStdString() );
            oldHeading = newHeading;
        }
    }
    void setDistance(double distance)
    {
        if(distance > 0) {
        int newDistance = distance;
        if(newDistance != oldDistance) {
            _distanceText->setText( QString("Distance %1m").arg(newDistance).toStdString() );
            oldDistance = newDistance;
        }
        } else {
            _distanceText->setText("");
        }
    }
};
