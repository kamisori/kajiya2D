#include <string>
#include <SFML/System.hpp>
#include <objects/visualAppearance.hpp>
#include <objects/spacialObject.hpp>
#include <objects/gameObjectManager.hpp>
#include <main.hpp>
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <objects/material.hpp>
#include <iostream>
#include <conversion.hpp>
#define NACCURACY 1000
namespace objects
{
    float SpacialObject::getAngleOffsetForAnimation()
    {
        return angleOffsetForAnimation_;
    }

    void SpacialObject::setAngleOffsetForAnimation( float tmp)
    {
        angleOffsetForAnimation_ = tmp;
    }

    std::string SpacialObject::getSpacialObjectId()
    {
        return spacialObjectId_;
    }

    VisualAppearance* SpacialObject::getVisualAppearance()
    {
        return visualAppearance_;
    }

    std::string SpacialObject::constructFileEntry()
    {
        std::string resultString;

        resultString = "";
        resultString += this->spacialObjectId_ + ";";
        resultString += this->materialId_ + ";";
        resultString += conversion::itoa((int)(this->bodyDefinition_.position_.x * NACCURACY)) + ";";
        resultString += conversion::itoa((int)(this->bodyDefinition_.position_.y * NACCURACY)) + ";";
        return resultString;
    }

    SpacialObject::SpacialObject( FileEntry inData )
    {
        FileEntry::iterator itEntry;
        itEntry = inData.begin();

        this->selected_ = false;
        this->spacialObjectId_ = (*itEntry);
        itEntry++;
        this->materialId_ = ( *itEntry );
        Material* temporaryMaterial = b2WorldAndVisualWorld.globalGameObjectManager_->provideMaterial( *itEntry );
        itEntry++;
        this->bodyDefinition_ = temporaryMaterial->getBodyDefinition();
        this->bodyDefinition_.position_.x = atof((*itEntry).c_str()) / NACCURACY;
        itEntry++;
        this->bodyDefinition_.position_.y = atof((*itEntry).c_str()) / NACCURACY;


        this->visualAppearance_ = b2WorldAndVisualWorld.globalGameObjectManager_->provideVisualAppearance( temporaryMaterial->getVisualAppearanceId() );
        this->fixtureDefinition_ = temporaryMaterial->getFixtureDefinition();

        this->shape_ = temporaryMaterial->getShapeType();
        if( this->shape_ == CIRCLE )
        {
            this->circle_ = temporaryMaterial->getCircleShape();
        }
        else if( this->shape_ == EDGE || this->shape_ == POLYGON )
        {
            this->polygon_ = temporaryMaterial->getPolygonShape();
        }
        else if( this->shape_ == ALIGNED_BOX || this->shape_ == ORIENTED_BOX )
        {
            this->box_ = temporaryMaterial->getBoxShape();
        }

        std::string visId ("static");
        this->visualAppearance_->setCurrentAnimationByAnimationId( visId );

    }

    SpacialObject::~SpacialObject()
    {
        this->visualAppearance_ = NULL;
    }
}
