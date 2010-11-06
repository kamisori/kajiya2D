#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <objects/animation.hpp>
#include <objects/visualAppearance.hpp>
#include <main.hpp>
#include <conversion.hpp>
#define NACCURACY 1000

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

    std::string Material::constructFileEntry()
    {
        std::string resultString;

        resultString = "";

        resultString += this->materialId_ + ";";
        resultString += this->visualAppearanceId_ + ";";

        if( this->bodyDefinitionTemplate_.type_  == STATIC )
        {
            resultString += "static;";
        }
        else if( this->bodyDefinitionTemplate_.type_  == DYNAMIC )
        {
            resultString += "dynamic;";
        }
        else if( this->bodyDefinitionTemplate_.type_  == KINEMATIC )
        {
            resultString += "kinematic;";
        }

        resultString += conversion::itoa((int)( this->bodyDefinitionTemplate_.angle_ * NACCURACY ) ) + ";";
        resultString += conversion::itoa((int)( this->bodyDefinitionTemplate_.linearVelocity_.x * NACCURACY )) + ";";
        resultString += conversion::itoa((int)( this->bodyDefinitionTemplate_.linearVelocity_.y * NACCURACY )) + ";";
        resultString += conversion::itoa((int)( this->bodyDefinitionTemplate_.angularVelocity_ * NACCURACY )) + ";";
        resultString += conversion::itoa((int)( this->bodyDefinitionTemplate_.linearDamping_ * NACCURACY )) + ";";
        resultString += conversion::itoa((int)( this->bodyDefinitionTemplate_.angularDamping_ * NACCURACY )) + ";";

        if( this->bodyDefinitionTemplate_.allowSleep_ )
        {
            resultString += "allowSleep;";
        }
        else if( !this->bodyDefinitionTemplate_.allowSleep_ )
        {
            resultString += "denySleep;";
        }

        if( this->bodyDefinitionTemplate_.awake_ )
        {
            resultString += "awake;";
        }
        else if( !this->bodyDefinitionTemplate_.awake_ )
        {
            resultString += "asleep;";
        }

        if( this->bodyDefinitionTemplate_.denyRotation_ )
        {
            resultString += "denyRotation;";
        }
        else if( !this->bodyDefinitionTemplate_.denyRotation_)
        {
            resultString += "allowRotation;";
        }

        if( this->bodyDefinitionTemplate_.isBullet_ )
        {
            resultString += "isBullet;";
        }
        else if( !this->bodyDefinitionTemplate_.isBullet_ )
        {
            resultString += "isNoBullet;";
        }

        if( this->bodyDefinitionTemplate_.active_ )
        {
            resultString += "active;";
        }
        else if( !this->bodyDefinitionTemplate_.active_ )
        {
            resultString += "inactive;";
        }

        resultString += conversion::itoa((int)( this->fixtureDefinitionTemplate_.friction_ * NACCURACY )) + ";";
        resultString += conversion::itoa((int)( this->fixtureDefinitionTemplate_.restitution_ * NACCURACY )) + ";";
        resultString += conversion::itoa((int)( this->fixtureDefinitionTemplate_.density_ * NACCURACY )) + ";";

        if( this->fixtureDefinitionTemplate_.isSensor_ )
        {
            resultString += "isSensor;";
        }
        else if( !this->fixtureDefinitionTemplate_.isSensor_ )
        {
            resultString += "isNoSensor;";
        }

        switch (this->shapeType_)
        {
            case CIRCLE:
                resultString += "circle;";
                resultString += conversion::itoa((int)( this->circleShapeTemplate_.center.x * NACCURACY )) + ";";
                resultString += conversion::itoa((int)( this->circleShapeTemplate_.center.y * NACCURACY )) + ";";
                resultString += conversion::itoa((int)( this->circleShapeTemplate_.radius * NACCURACY )) + ";";
                break;
            case EDGE:
                resultString += "edge;";
                resultString += conversion::itoa((int)( this->polygonShapeTemplate_.vertices[0].x * NACCURACY )) + ";";
                resultString += conversion::itoa((int)( this->polygonShapeTemplate_.vertices[0].y * NACCURACY )) + ";";
                resultString += conversion::itoa((int)( this->polygonShapeTemplate_.vertices[1].x * NACCURACY )) + ";";
                resultString += conversion::itoa((int)( this->polygonShapeTemplate_.vertices[1].y * NACCURACY )) + ";";
                break;
            case ALIGNED_BOX:
                resultString += "axisAlignedBox;";
                resultString += conversion::itoa((int)( this->boxShapeTemplate_.halfSize.x * NACCURACY )) + ";";
                resultString += conversion::itoa((int)( this->boxShapeTemplate_.halfSize.y * NACCURACY )) + ";";
                break;
            case ORIENTED_BOX:
                resultString += "orientedBox;";
                resultString += conversion::itoa((int)( this->boxShapeTemplate_.halfSize.x * NACCURACY )) + ";";
                resultString += conversion::itoa((int)( this->boxShapeTemplate_.halfSize.y * NACCURACY )) + ";";
                resultString += conversion::itoa((int)( this->boxShapeTemplate_.center.x * NACCURACY )) + ";";
                resultString += conversion::itoa((int)( this->boxShapeTemplate_.center.y * NACCURACY )) + ";";
                resultString += conversion::itoa((int)( this->boxShapeTemplate_.angle * NACCURACY )) + ";";
                break;
            case POLYGON:
                resultString += "polygon;";
                resultString += conversion::itoa((int)( this->polygonShapeTemplate_.countOfVertices * NACCURACY ))+ ";";
                for( unsigned int i = 0; i < this->polygonShapeTemplate_.countOfVertices; i++ )
                {
                    resultString += conversion::itoa((int)( this->polygonShapeTemplate_.vertices[i].x * NACCURACY )) + ";";
                    resultString += conversion::itoa((int)( this->polygonShapeTemplate_.vertices[i].y * NACCURACY )) + ";";
                }
                break;
            default:
                exit(1);

        }
        return resultString;
    }

    void Material::createMaterial( std::string materialId, std::string visualAppearanceId, bodyDefinition bodyDefinitionTemplate, fixtureDefinition fixtureDefinitionTemplate, float  angleOffsetForAnimation, circle shapeTemplate )
    {
        this->shapeType_ = CIRCLE;
        this->materialId_ = materialId;
        this->visualAppearanceId_ = visualAppearanceId;
        this->angleOffsetForAnimation_ = angleOffsetForAnimation;
        this->circleShapeTemplate_ = shapeTemplate;

        this->bodyDefinitionTemplate_ = bodyDefinitionTemplate;
        this->fixtureDefinitionTemplate_ = fixtureDefinitionTemplate;
    }

    void Material::createMaterial( std::string materialId, std::string visualAppearanceId, bodyDefinition bodyDefinitionTemplate, fixtureDefinition fixtureDefinitionTemplate, float  angleOffsetForAnimation, Shape shapeType, polygon shapeTemplate )
    {
        this->shapeType_ = shapeType;
        this->materialId_ = materialId;
        this->visualAppearanceId_ = visualAppearanceId;
        this->angleOffsetForAnimation_ = angleOffsetForAnimation;
        this->polygonShapeTemplate_ = shapeTemplate;

        this->bodyDefinitionTemplate_ = bodyDefinitionTemplate;
        this->fixtureDefinitionTemplate_ = fixtureDefinitionTemplate;
    }

    void Material::createMaterial( std::string materialId, std::string visualAppearanceId, bodyDefinition bodyDefinitionTemplate, fixtureDefinition fixtureDefinitionTemplate, float  angleOffsetForAnimation, Shape shapeType, box shapeTemplate )
    {
        this->shapeType_ = shapeType;
        this->materialId_ = materialId;
        this->visualAppearanceId_ = visualAppearanceId;
        this->angleOffsetForAnimation_ = angleOffsetForAnimation;
        this->boxShapeTemplate_ = shapeTemplate;

        this->bodyDefinitionTemplate_ = bodyDefinitionTemplate;
        this->fixtureDefinitionTemplate_ = fixtureDefinitionTemplate;
    }

    Material::Material( FileEntry inData )
    {
        FileEntry::iterator itEntry;
        itEntry = inData.begin();

        this->materialId_ = (*itEntry);
        itEntry++;
        this->visualAppearanceId_ = (*itEntry);
        itEntry++;

        bodyDefinition bodyDefinitionTemplate;

        bodyDefinitionTemplate.position_.x = 0.0;
        bodyDefinitionTemplate.position_.y = 0.0;

        if( (*itEntry).compare( "static" ) == 0 ){
            bodyDefinitionTemplate.type_ = STATIC;
        }
        else if ( (*itEntry).compare( "dynamic" ) == 0 ){
            bodyDefinitionTemplate.type_ = DYNAMIC;
        }
        else if ( (*itEntry).compare( "kinematic" ) == 0 ){
            bodyDefinitionTemplate.type_ = KINEMATIC;
        }
        else{
            exit(1);
        }
        itEntry++;
        bodyDefinitionTemplate.angle_ = atof((*itEntry).c_str()) / NACCURACY;
        itEntry++;
        bodyDefinitionTemplate.linearVelocity_.x = atof((*itEntry).c_str()) / NACCURACY;
        itEntry++;
        bodyDefinitionTemplate.linearVelocity_.y = atof((*itEntry).c_str()) / NACCURACY;
        itEntry++;
        bodyDefinitionTemplate.angularVelocity_ = atof((*itEntry).c_str()) / NACCURACY;
        itEntry++;
        bodyDefinitionTemplate.linearDamping_ =  atof((*itEntry).c_str()) / NACCURACY;
        itEntry++;
        bodyDefinitionTemplate.angularDamping_ = atof((*itEntry).c_str()) / NACCURACY;
        itEntry++;

        if( (*itEntry).compare( "allowSleep" ) == 0 ){
            bodyDefinitionTemplate.allowSleep_ = true;
        }
        else if( (*itEntry).compare( "denySleep" ) == 0 ){
            bodyDefinitionTemplate.allowSleep_ = false;
        }
        else{
            exit(1);
        }
        itEntry++;

        if( (*itEntry).compare( "awake" ) == 0 ){
            bodyDefinitionTemplate.awake_ = true;
        }
        else if( (*itEntry).compare( "asleep" ) == 0 ){
            bodyDefinitionTemplate.awake_ = false;
        }
        else{
            exit(1);
        }
        itEntry++;

        if( (*itEntry).compare( "denyRotation" ) == 0 ){
            bodyDefinitionTemplate.denyRotation_ = true;
        }
        else if( (*itEntry).compare( "allowRotation" ) == 0 ){
            bodyDefinitionTemplate.denyRotation_ = false;
        }
        else{
            exit(1);
        }
        itEntry++;

        if( (*itEntry).compare( "isBullet" ) == 0 ){
            bodyDefinitionTemplate.isBullet_ = true;
        }
        else if( (*itEntry).compare( "isNoBullet" ) == 0 ){
            bodyDefinitionTemplate.isBullet_ = false;
        }
        else{
            exit(1);
        }
        itEntry++;

        if( (*itEntry).compare( "active" ) == 0 ){
            bodyDefinitionTemplate.active_ = true;
        }
        else if( (*itEntry).compare( "inactive" ) == 0 ){
            bodyDefinitionTemplate.active_ = false;
        }
        else{
            exit(1);
        }

        itEntry++;
        fixtureDefinition fixtureDefinitionTemplate;
        fixtureDefinitionTemplate.friction_ = atof((*itEntry).c_str()) / NACCURACY;
        itEntry++;
        fixtureDefinitionTemplate.restitution_ = atof((*itEntry).c_str()) / NACCURACY;
        itEntry++;
        fixtureDefinitionTemplate.density_ = atof((*itEntry).c_str()) / NACCURACY;
        itEntry++;
        if( (*itEntry).compare( "isSensor") == 0 ){
            fixtureDefinitionTemplate.isSensor_ = true;
        }
        else if( (*itEntry).compare( "isNoSensor" ) == 0 ){
            fixtureDefinitionTemplate.isSensor_ = false;
        }
        itEntry++;

        circle tmpCircle;
        polygon tmpPolygon;
        box tmpBox;
        float  angleOffsetForAnimation = 0;
        if( (*itEntry).compare( "circle" ) == 0 ){
            itEntry++;
            tmpCircle.center.x = atof((*itEntry).c_str()) / NACCURACY;
            itEntry++;
            tmpCircle.center.y = atof((*itEntry).c_str()) / NACCURACY;
            itEntry++;
            tmpCircle.radius = atof((*itEntry).c_str()) / NACCURACY;

            createMaterial( this->materialId_, this->visualAppearanceId_, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, tmpCircle );
        }
        else
        {
            Shape shapeType;
            if( (*itEntry).compare( "edge" ) == 0 ){
                shapeType = EDGE;
                itEntry++;
                tmpPolygon.countOfVertices = 2;
                tmpPolygon.vertices[0].x = atof((*itEntry).c_str()) / NACCURACY;
                itEntry++;
                tmpPolygon.vertices[0].y = atof((*itEntry).c_str()) / NACCURACY;
                itEntry++;
                tmpPolygon.vertices[1].x = atof((*itEntry).c_str()) / NACCURACY;
                itEntry++;
                tmpPolygon.vertices[1].y = atof((*itEntry).c_str()) / NACCURACY;

                createMaterial( this->materialId_, this->visualAppearanceId_, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, shapeType, tmpPolygon );
            }
            else if( (*itEntry).compare( "axisAlignedBox" ) == 0 ){
                shapeType = ALIGNED_BOX;
                itEntry++;

                tmpBox.halfSize.x = atof((*itEntry).c_str()) / NACCURACY;
                itEntry++;
                tmpBox.halfSize.y = atof((*itEntry).c_str()) / NACCURACY;

                tmpBox.center.x = 0;
                tmpBox.center.x = 0;
                tmpBox.angle = 0;

                createMaterial( this->materialId_, this->visualAppearanceId_, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, shapeType, tmpBox );
            }
            else if( (*itEntry).compare( "orientedBox" ) == 0 ){
                shapeType = ORIENTED_BOX;

                itEntry++;
                tmpBox.halfSize.x = atof((*itEntry).c_str()) / NACCURACY;
                itEntry++;
                tmpBox.halfSize.y = atof((*itEntry).c_str()) / NACCURACY;
                itEntry++;
                tmpBox.center.x = atof((*itEntry).c_str()) / NACCURACY;
                itEntry++;
                tmpBox.center.y = atof((*itEntry).c_str()) / NACCURACY;
                itEntry++;
                tmpBox.angle = atof((*itEntry).c_str()) / NACCURACY;
                angleOffsetForAnimation = tmpBox.angle;

                createMaterial( this->materialId_, this->visualAppearanceId_, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, shapeType, tmpBox );
            }
            else if( (*itEntry).compare( "polygon" ) == 0 ){
                shapeType = POLYGON;
                itEntry++;
                tmpPolygon.countOfVertices = atoi((*itEntry).c_str()) / NACCURACY;

                for( unsigned int i = 0; i < tmpPolygon.countOfVertices; i++ )
                {
                    itEntry++;
                    tmpPolygon.vertices[i].x = atof((*itEntry).c_str()) / NACCURACY;
                    itEntry++;
                    tmpPolygon.vertices[i].y = atof((*itEntry).c_str()) / NACCURACY;
                }

                createMaterial( this->materialId_, this->visualAppearanceId_, bodyDefinitionTemplate, fixtureDefinitionTemplate, angleOffsetForAnimation, shapeType, tmpPolygon );
            }
            else
            {
                exit(1);
            }
        }
    }

    Material::~Material()
    {
    }
}
