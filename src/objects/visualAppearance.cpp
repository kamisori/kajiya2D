#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <objects/animation.hpp>
#include <objects/visualAppearance.hpp>
#include <main.hpp>

namespace objects
{
    typedef std::vector< std::string > FileEntry;
    typedef std::vector< FileEntry > FileData;

    void VisualAppearance::setCurrentAnimationByAnimationId( std::string animationId )
    {
        std::vector< Animation* >::iterator it;
        for( it = possibleAnimations_.begin(); it < possibleAnimations_.end(); it++ )
        {
            if( animationId.compare( (*it)->getAnimationId() ) == 0 )
            {
                this->currentAnimation_ = *it;
                return;
            }
        }
        this->currentAnimation_ = NULL;
    }

    Animation*  VisualAppearance::getCurrentAnimation()
    {
        return this->currentAnimation_;
    }

    std::string VisualAppearance::getVisualAppearanceId()
    {
        return visualAppearanceId_;
    }

    std::string VisualAppearance::constructFileEntry()
    {
        std::string resultString;

        resultString = "";
        resultString = this->visualAppearanceId_ + ";";
        resultString = this->animationsDescriptionFile_ + ";";

        return resultString;
    }

    void VisualAppearance::loadAnimations()
    {
        FileData* dataFromFile = b2WorldAndVisualWorld.globalGameObjectManager_->parseFileData( &this->animationsDescriptionFile_, 5 );

        FileData::iterator itData;
        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileEntry tmp = (*itData);
            Animation* temporaryAnimation = new Animation(tmp);

            if( temporaryAnimation != NULL )
            {
                this->possibleAnimations_.push_back( temporaryAnimation );
            }
        }

    }

    VisualAppearance::VisualAppearance( FileEntry inData )
    {
        FileEntry::iterator itEntry;
        itEntry = inData.begin();

        this->visualAppearanceId_ = (*itEntry);
        itEntry++;
        this->animationsDescriptionFile_ = (*itEntry);

        loadAnimations();

        if(possibleAnimations_.empty())
        {
            exit(1);
        }
    }

    VisualAppearance::~VisualAppearance()
    {
        this->possibleAnimations_.clear();
        delete this->currentAnimation_;
    }
}
