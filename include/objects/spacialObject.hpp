#ifndef SPACIALOBJECT_HPP
#define SPACIALOBJECT_HPP

#include <string>
#include <SFML/System.hpp>
#include <objects/visualAppearance.hpp>
#include <Box2D/Box2D.h>

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
    class SpacialObject
    {
    	public:
            float getAngleOffset();
            void setAngleOffset(float tmp);
            std::string getSpacialObjectId();
            VisualAppearance* getVisualAppearance();

            sf::Vector2f moveObject( sf::Vector2f addThis );

            SpacialObject( std::string spacialObjectId, std::string visualAppearanceId );
                            /*string* audialAppearanceId,*/ /*float objectHealth,*/ /*float objectHardness*/
            ~SpacialObject();

            std::string spacialObjectId_;


            bodyDefinition bodyDefinition_;

            fixtureDefinition fixtureDefinition_;

            Shape shape_;

            circle circle_;

            polygon polygon_;

            box box_;

            bool selected_;

    	protected:

    	private:
            float angleOffset_;
//    		float               objectHealth_;              //objects can be damaged
//    		float               objectHardness_;            //some objects resist damage better than others
                                                            //combined with collision, this means, you can
                                                            //use anything and everything as a shield against attacks.
//          float               objectTemperature_;
//          float               objectMoisture_;
//          pointer to material holding having certain properties,
//          like, meltable, flamable, temperature for meltpoint/inflamationpoint whatever

            VisualAppearance*   visualAppearance_;          //null means, this is either a zone for a script,
                                                            //or something is attached to the ground, like a
                                                            //pole for a line or something

            //AudioAppearance*    audialAppearance_;        //basically the same as visualAppearance.
                                                            //holds the samples this objects can play.
//probably not neccessary:
            //Attachment*         attachedTo_;              //Attach one Object to another
                                                            //in example: Flashlight to Shovel
                                                            //attachmentStrength determines if object can be removed
                                                            //objectHealth must be higher than attachment strength, else object breaks during removal
                                                            //orientation relative to attached object
                                                            //attached at top, bottom, hind, front, one side or the other
//probably neccessary
            //Script*             objectScript_;            //also for AI
    };
}

#endif
