#include <string>
#include <SFML/System.hpp>
#include <objects/visualAppearance.hpp>
#include <objects/spacialObject.hpp>
#include <objects/gameObjectManager.hpp>
#include <main.hpp>
#include <Box2D/Box2D.h>

namespace objects
{
    std::string SpacialObject::getSpacialObjectId()
    {
        return spacialObjectId_;
    }
    float SpacialObject::getAngleOffset()
    {
        return angleOffset_;
    }

    void SpacialObject::setAngleOffset( float tmp)
    {
        angleOffset_ = tmp;
    }

    VisualAppearance* SpacialObject::getVisualAppearance()
    {
        return visualAppearance_;
    }

    SpacialObject::SpacialObject( std::string spacialObjectId, std::string visualAppearanceId )
    {
        this->selected_ = false;
        spacialObjectId_.assign( spacialObjectId );

        this->visualAppearance_ = b2WorldAndVisualWorld.globalGameObjectManager_->provideVisualAppearance( visualAppearanceId );

        std::string visId ("static");
        this->visualAppearance_->setCurrentAnimationByAnimationId( visId );

    }

    SpacialObject::~SpacialObject()
    {
        this->visualAppearance_ = NULL;
    }
}
