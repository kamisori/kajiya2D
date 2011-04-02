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

#ifndef SPACIALOBJECT_HPP
#define SPACIALOBJECT_HPP

#include <string>
#include <SFML/System.hpp>
#include <objects/visualAppearance.hpp>
#include <Box2D/Box2D.h>
#include <objects/material.hpp>

namespace objects
{
    class SpacialObject
    {
    	public:
            float getAngleOffsetForAnimation();
            void setAngleOffsetForAnimation(float tmp);
            std::string getSpacialObjectId();
            VisualAppearance* getVisualAppearance();

            sf::Vector2f moveObject( sf::Vector2f addThis );

            std::string spacialObjectId_;
            std::string materialId_;

            bodyDefinition bodyDefinition_;
            fixtureDefinition fixtureDefinition_;
            Shape shape_;
            circle circle_;
            polygon polygon_;
            box box_;

            bool selected_;

            std::string constructFileEntry();
            SpacialObject( FileEntry inData );
            ~SpacialObject();
    	protected:

    	private:
            float angleOffsetForAnimation_;
            VisualAppearance*   visualAppearance_;
    };
}

#endif
