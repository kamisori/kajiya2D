/*
    kajiya2D is an editor for leveldata for heikiko2D/nodachi2D.
    Copyright (C) 2010-2011  Paul Predkiewicz

    kajiya2D is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
        resultString += this->visualAppearanceId_ + ";";
        resultString += this->animationsDescriptionFile_ + ";";

        return resultString;
    }
    std::string VisualAppearance::constructFileEntryAndSaveAnimations()
    {
        saveAnimations( this->animationsDescriptionFile_ );
        return constructFileEntry();
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
    void VisualAppearance::saveAnimations( std::string animationFile )
    {
        std::vector< Animation* >::iterator it;
        std::string fileContent;
        fileContent = "";
        for( it = this->possibleAnimations_.begin(); it < this->possibleAnimations_.end(); it++ )
        {
            fileContent += (*it)->constructFileEntry() + "\r\n";
        }
        b2WorldAndVisualWorld.globalGameObjectManager_->dumpFileData(animationFile, fileContent);
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
