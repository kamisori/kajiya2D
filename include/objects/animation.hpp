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

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace objects
{
#define SPRITE_SIZE 32
    typedef std::vector< std::string > FileEntry;
    class Animation
    {
        public:
            sf::Sprite* getNextFrame();
            std::string getAnimationId();

            sf::Image* getAllFrames();

            std::string constructFileEntry();
            Animation( FileEntry inData );
            ~Animation();
        protected:

        private:
            void iterateToNextFrame();

            void loadPicture();
            void buildAnimation();

            sf::Vector2i rowsAndCollumns_;
            int delayPerFrameInMs_;
            std::string animationId_;
            sf::Image* allFrames_;
            std::string fileName_;
            std::vector< sf::Sprite* > frames_;
            unsigned int currentFrame_;
    };
}
#endif
