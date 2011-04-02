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

#ifndef VISUALAPPEARANCE_HPP
#define VISUALAPPEARANCE_HPP

#include <string>
#include <vector>
#include <objects/animation.hpp>
namespace objects
{
    class VisualAppearance
    {
        public:
            void        setCurrentAnimationByAnimationId( std::string animationId );
            Animation*  getCurrentAnimation();
            std::string getVisualAppearanceId();

            std::string constructFileEntryAndSaveAnimations();
            VisualAppearance( FileEntry inData );
            ~VisualAppearance();
        protected:

        private:
            void loadAnimations();
            void saveAnimations( std::string animationFile );
            std::string constructFileEntry();

            std::string                 animationsDescriptionFile_;
            std::string                 visualAppearanceId_;
            std::vector< Animation* >   possibleAnimations_;
            Animation*                  currentAnimation_;
    };
}
#endif
