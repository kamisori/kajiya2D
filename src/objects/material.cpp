#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <objects/animation.hpp>
#include <objects/visualAppearance.hpp>
#include <main.hpp>

namespace objects
{
    std::string Material::getMaterialId()
    {
        return materialId_;
    }

    std::string Material::getVisualAppearanceId()
    {
        return visualAppearanceId_;
    }

    fixtureDefinition Material::getFixtureDefinition()
    {
        return fixtureDefinitionTemplate_;
    }

    bodyDefinition Material::getBodyDefinition()
    {
        return bodyDefinitionTemplate_;
    }

    float Material::getAngleOffsetForAnimation()
    {
        return angleOffsetForAnimation_;
    }

    Shape Material::getShapeType()
    {
       return shapeType_;
    }

    circle Material::getCircleShape()
    {
        return circleShapeTemplate_;
    }

    polygon Material::getPolygonShape()
    {
        return polygonShapeTemplate_;
    }

    box Material::getBoxShape()
    {
        return boxShapeTemplate_;
    }

    Material::Material( std::string materialId, std::string visualAppearanceId, bodyDefinition bodyDefinitionTemplate, fixtureDefinition fixtureDefinitionTemplate, float  angleOffsetForAnimation, circle shapeTemplate )
    {
        this->shapeType_ = CIRCLE;
        this->materialId_ = materialId;
        this->visualAppearanceId_ = visualAppearanceId;
        this->angleOffsetForAnimation_ = angleOffsetForAnimation;
        this->circleShapeTemplate_ = shapeTemplate;

        this->bodyDefinitionTemplate_ = bodyDefinitionTemplate;
        this->fixtureDefinitionTemplate_ = fixtureDefinitionTemplate;
    }

    Material::Material( std::string materialId, std::string visualAppearanceId, bodyDefinition bodyDefinitionTemplate, fixtureDefinition fixtureDefinitionTemplate, float  angleOffsetForAnimation, Shape shapeType, polygon shapeTemplate )
    {
        this->shapeType_ = shapeType;
        this->materialId_ = materialId;
        this->visualAppearanceId_ = visualAppearanceId;
        this->angleOffsetForAnimation_ = angleOffsetForAnimation;
        this->polygonShapeTemplate_ = shapeTemplate;

        this->bodyDefinitionTemplate_ = bodyDefinitionTemplate;
        this->fixtureDefinitionTemplate_ = fixtureDefinitionTemplate;
    }

    Material::Material( std::string materialId, std::string visualAppearanceId, bodyDefinition bodyDefinitionTemplate, fixtureDefinition fixtureDefinitionTemplate, float  angleOffsetForAnimation, Shape shapeType, box shapeTemplate )
    {
        this->shapeType_ = shapeType;
        this->materialId_ = materialId;
        this->visualAppearanceId_ = visualAppearanceId;
        this->angleOffsetForAnimation_ = angleOffsetForAnimation;
        this->boxShapeTemplate_ = shapeTemplate;

        this->bodyDefinitionTemplate_ = bodyDefinitionTemplate;
        this->fixtureDefinitionTemplate_ = fixtureDefinitionTemplate;
    }

    Material::Material()
    {
        exit(1);
    }

    Material::~Material()
    {
    }
}
