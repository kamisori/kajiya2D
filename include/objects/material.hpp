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

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <vector>

namespace objects
{
    enum bodyType{ STATIC, DYNAMIC, KINEMATIC };

    struct bodyDefinition{
        bodyType type_;
        sf::Vector2f position_;
        float angle_;
        sf::Vector2f linearVelocity_;
        float angularVelocity_;
        float linearDamping_;
        float angularDamping_;
        bool allowSleep_;
        bool awake_;
        bool denyRotation_;
        bool isBullet_;
        bool active_;
    };

    struct fixtureDefinition{
        float friction_;
        float restitution_;
        float density_;
        bool isSensor_;
    };

    enum Shape{ CIRCLE, EDGE, ALIGNED_BOX, ORIENTED_BOX, POLYGON };

    struct circle{
        sf::Vector2f center;
        float radius;
    };

    struct polygon{
        unsigned int countOfVertices;
        sf::Vector2f vertices[8];
    };

    struct box{
        sf::Vector2f halfSize;
        sf::Vector2f center;
        float angle;
    };

    class Material
    {
        public:
            std::string getMaterialId();
            std::string getVisualAppearanceId();
            std::string constructFileEntry();

            float getAngleOffsetForAnimation();

            fixtureDefinition getFixtureDefinition();
            bodyDefinition getBodyDefinition();

            circle getCircleShape();
            polygon getPolygonShape();
            box getBoxShape();

            Shape getShapeType();

            void createMaterial( std::string materialId, std::string visualAppearanceId, bodyDefinition bodyDefinitionTemplate, fixtureDefinition fixtureDefinitionTemplate, float  angleOffsetForAnimation, circle shapeTemplate );
            void createMaterial( std::string materialId, std::string visualAppearanceId, bodyDefinition bodyDefinitionTemplate, fixtureDefinition fixtureDefinitionTemplate, float  angleOffsetForAnimation, Shape shapeType, polygon shapeTemplate );
            void createMaterial( std::string materialId, std::string visualAppearanceId, bodyDefinition bodyDefinitionTemplate, fixtureDefinition fixtureDefinitionTemplate, float  angleOffsetForAnimation, Shape shapeType, box shapeTemplate );
            Material( FileEntry inData );
            ~Material();

        protected:

        private:
            std::string     materialId_;
            std::string     visualAppearanceId_;

            float               angleOffsetForAnimation_;
            fixtureDefinition   fixtureDefinitionTemplate_;
            bodyDefinition      bodyDefinitionTemplate_;

            Shape shapeType_;
            circle circleShapeTemplate_;
            polygon polygonShapeTemplate_;
            box boxShapeTemplate_;
    };
}
#endif
