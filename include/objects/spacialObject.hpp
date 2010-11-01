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
