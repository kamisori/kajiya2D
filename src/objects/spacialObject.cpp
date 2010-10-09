#include <string>
#include <SFML/System.hpp>
#include <objects/visualAppearance.hpp>
#include <objects/spacialObject.hpp>
#include <objects/gameObjectManager.hpp>
#include <main.hpp>
#include <Box2D/Box2D.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <objects/material.hpp>

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

    SpacialObject::SpacialObject( std::string spacialObjectId, std::string materialId, b2Vec2 position )
    {
        this->selected_ = false;
        spacialObjectId_.assign( spacialObjectId );

        Material* temporaryMaterial;
        temporaryMaterial = b2WorldAndVisualWorld.globalGameObjectManager_->provideMaterial( materialId );

        this->visualAppearance_ = b2WorldAndVisualWorld.globalGameObjectManager_->provideVisualAppearance( temporaryMaterial->getVisualAppearanceId() );

        this->bodyDefinition_ = temporaryMaterial->getBodyDefinition();
        this->bodyDefinition_.position_.x = position.x;
        this->bodyDefinition_.position_.y = position.y;
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
