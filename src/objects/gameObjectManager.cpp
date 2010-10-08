#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <objects/spacialObject.hpp>
#include <objects/visualAppearance.hpp>
#include <objects/gameObjectManager.hpp>
namespace objects{

    void GameObjectManager::createSpacialObject( std::string spacialObjectId, std::string visualAppearanceId )
    {
        SpacialObject* temporaryObject = new SpacialObject( spacialObjectId, visualAppearanceId );
        this->spacialObjects_.push_back( temporaryObject );
    }

    VisualAppearance* GameObjectManager::provideVisualAppearance( std::string visualAppearanceId )
    {
        std::vector< VisualAppearance* >::iterator it;
        for( it = this->visualAppearancesLibrary_.begin(); it < this->visualAppearancesLibrary_.end(); it++ )
        {
            std::string foostr = (*it)->getVisualAppearanceId();
            if( visualAppearanceId.compare( (*it)->getVisualAppearanceId() ) == 0 )
            {
                return (*it);
            }
        }
        //throw exception
        exit(1);
    }

    SpacialObject* GameObjectManager::nextSpacialObject( int current )
    {
         std::vector< SpacialObject* >::iterator it;
         it = this->spacialObjects_.begin();
         it += current;
         if( it < this->spacialObjects_.end() )
         {
            return (*it);
         }
         return NULL;
    }

    VisualAppearance* GameObjectManager::nextVisualAppearance( int current )
    {
         std::vector< VisualAppearance* >::iterator it;
         it = this->visualAppearancesLibrary_.begin();
         it += current;
         if( it < this->visualAppearancesLibrary_.end() )
         {
            return (*it);
         }
         return NULL;
    }

//    AudioAppearance* GameObjectManager::provideAudioAppearance( std::string* audioAppearanceId )
 //std::string spacialObjectId, std::string visualAppearanceId, b2BodyDef* bodyDefinition, b2FixtureDef* fixtureDefinition
    //std::string* spacialObjectId, float posX, float posY, PositionInZ posZ, float orientation, bool collides, float collisionR, std::string* visualAppearanceId
    void GameObjectManager::loadObjects( std::string spacialObjectsFile )
    {
        FileData* dataFromFile = fetchFileData( &spacialObjectsFile, 38 );
        FileData::iterator itData;
        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileEntry::iterator itEntry;
            FileEntry tmp = (*itData);
            itEntry = tmp.begin();

            std::string objectId = (*itEntry);
            itEntry++;
            std::string visualAppearanceId = (*itEntry);
            itEntry++;

            SpacialObject* temporaryObject = new SpacialObject( objectId, visualAppearanceId );

            if( (*itEntry).compare( "static" ) == 0 ){
                temporaryObject->bodyDefinition_.type_ = STATIC;
            }
            else if ( (*itEntry).compare( "dynamic" ) == 0 ){
                temporaryObject->bodyDefinition_.type_ = DYNAMIC;
            }
            else if ( (*itEntry).compare( "kinematic" ) == 0 ){
                temporaryObject->bodyDefinition_.type_ = KINEMATIC;
            }
            else{
                delete temporaryObject;
                exit(1);
            }
            itEntry++;
            temporaryObject->bodyDefinition_.position_.x = atof((*itEntry).c_str());;
            itEntry++;
            temporaryObject->bodyDefinition_.position_.y = atof((*itEntry).c_str());;
            itEntry++;
            temporaryObject->bodyDefinition_.angle_ = atof((*itEntry).c_str());
            itEntry++;
            temporaryObject->bodyDefinition_.linearVelocity_.x = atof((*itEntry).c_str());
            itEntry++;
            temporaryObject->bodyDefinition_.linearVelocity_.y = atof((*itEntry).c_str());
            itEntry++;
            temporaryObject->bodyDefinition_.angularVelocity_ = atof((*itEntry).c_str());
            itEntry++;
            temporaryObject->bodyDefinition_.linearDamping_ =  atof((*itEntry).c_str());
            itEntry++;
            temporaryObject->bodyDefinition_.angularDamping_ = atof((*itEntry).c_str());
            itEntry++;

            if( (*itEntry).compare( "allowSleep" ) == 0 ){
                temporaryObject->bodyDefinition_.allowSleep_ = true;
            }
            else if( (*itEntry).compare( "denySleep" ) == 0 ){
                temporaryObject->bodyDefinition_.allowSleep_ = false;
            }
            else{
                delete temporaryObject;
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "awake" ) == 0 ){
                temporaryObject->bodyDefinition_.awake_ = true;
            }
            else if( (*itEntry).compare( "asleep" ) == 0 ){
                temporaryObject->bodyDefinition_.awake_ = false;
            }
            else{
                delete temporaryObject;
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "denyRotation" ) == 0 ){
                //in b2BodyDef this is fixedRotation, not denyRotation
                temporaryObject->bodyDefinition_.denyRotation_ = true;
            }
            else if( (*itEntry).compare( "allowRotation" ) == 0 ){
                //in b2BodyDef this is fixedRotation, not denyRotation
                temporaryObject->bodyDefinition_.denyRotation_= false;
            }
            else{
                delete temporaryObject;
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "isBullet" ) == 0 ){
                temporaryObject->bodyDefinition_.isBullet_ = true;
            }
            else if( (*itEntry).compare( "isNoBullet" ) == 0 ){
                temporaryObject->bodyDefinition_.isBullet_ = false;
            }
            else{
                delete temporaryObject;
                exit(1);
            }
            itEntry++;

            if( (*itEntry).compare( "active" ) == 0 ){
                temporaryObject->bodyDefinition_.active_ = true;
            }
            else if( (*itEntry).compare( "inactive" ) == 0 ){
                temporaryObject->bodyDefinition_.active_ = false;
            }
            else{
                delete temporaryObject;
                exit(1);
            }
            itEntry++;
            temporaryObject->fixtureDefinition_.friction_ = atof((*itEntry).c_str());
            itEntry++;
            temporaryObject->fixtureDefinition_.restitution_ = atof((*itEntry).c_str());
            itEntry++;
            temporaryObject->fixtureDefinition_.density_ = atof((*itEntry).c_str());
            itEntry++;
            if( (*itEntry).compare( "isSensor") == 0 ){
                temporaryObject->fixtureDefinition_.isSensor_ = true;
            }
            else if( (*itEntry).compare( "isNoSensor" ) == 0 ){
                temporaryObject->fixtureDefinition_.isSensor_ = false;
            }
            itEntry++;

            b2CircleShape tmpCircle;
            b2PolygonShape tmpBox;

            if( (*itEntry).compare( "circle" ) == 0 ){
                temporaryObject->shape_ = CIRCLE;
                itEntry++;
                temporaryObject->circle_.center.x = atof((*itEntry).c_str());
                itEntry++;
                temporaryObject->circle_.center.y = atof((*itEntry).c_str());
                itEntry++;
                temporaryObject->circle_.radius = atof((*itEntry).c_str());

                temporaryObject->setAngleOffset(0);
            }
            else if( (*itEntry).compare( "edge" ) == 0 ){
                temporaryObject->shape_ = EDGE;
                itEntry++;
                temporaryObject->polygon_.countOfVertices = 2;
                temporaryObject->polygon_.vertices[0].x = atof((*itEntry).c_str());
                itEntry++;
                temporaryObject->polygon_.vertices[0].y = atof((*itEntry).c_str());
                itEntry++;
                temporaryObject->polygon_.vertices[1].x = atof((*itEntry).c_str());
                itEntry++;
                temporaryObject->polygon_.vertices[1].y = atof((*itEntry).c_str());

                temporaryObject->setAngleOffset(0);
            }
            else if( (*itEntry).compare( "axisAlignedBox" ) == 0 ){
                temporaryObject->shape_ = ALIGNED_BOX;
                itEntry++;

                temporaryObject->box_.halfSize.x = atof((*itEntry).c_str());
                itEntry++;
                temporaryObject->box_.halfSize.y = atof((*itEntry).c_str());

                temporaryObject->box_.center.x = 0;
                temporaryObject->box_.center.x = 0;
                temporaryObject->box_.angle = 0;
                temporaryObject->setAngleOffset(0);
            }
            else if( (*itEntry).compare( "orientedBox" ) == 0 ){
                temporaryObject->shape_ = ORIENTED_BOX;
                itEntry++;
                temporaryObject->box_.halfSize.x = atof((*itEntry).c_str());
                itEntry++;
                temporaryObject->box_.halfSize.y = atof((*itEntry).c_str());
                itEntry++;
                temporaryObject->box_.center.x = atof((*itEntry).c_str());
                itEntry++;
                temporaryObject->box_.center.y = atof((*itEntry).c_str());
                itEntry++;
                temporaryObject->box_.angle = atof((*itEntry).c_str());
                temporaryObject->setAngleOffset(atof((*itEntry).c_str()));
            }
            else if( (*itEntry).compare( "polygon" ) == 0 ){ //circle edge alignedBox orientedBox polygon
                temporaryObject->shape_ = POLYGON;
                itEntry++;
                temporaryObject->polygon_.countOfVertices = atoi((*itEntry).c_str());

                for( unsigned int i = 0; i < temporaryObject->polygon_.countOfVertices; i++ ){
                    itEntry++;
                    temporaryObject->polygon_.vertices[i].x = atof((*itEntry).c_str());
                    itEntry++;
                    temporaryObject->polygon_.vertices[i].y = atof((*itEntry).c_str());
                }

                temporaryObject->setAngleOffset(0);
            }
            else{
                delete temporaryObject;
                exit(1);
            }

            if( temporaryObject != NULL )
            {
                this->spacialObjects_.push_back( temporaryObject );
            }
        }
    }

    FileData* GameObjectManager::fetchFileData( std::string* fileName, int fields )
    {
        std::ifstream ifs( fileName->c_str(), std::ifstream::in );
        if( ifs.is_open() ){
            char* buffer;
            int length;

            ifs.seekg( 0,std::ios::end );
            length = ifs.tellg();
            ifs.seekg( 0,std::ios::beg );

            buffer = new char[ length ];
            for(int i = 0; i < length; i++){
                buffer[i]=0;
            }

            ifs.read( buffer, length );
            ifs.close();

            std::string tmp;
            tmp.clear();
            tmp.assign(buffer);

            delete[] buffer;

            unsigned int lastPos = 0;
            unsigned int lastCarriageRet = 0;
            FileData* tmpData = new FileData();
            std::string entryDivider ("!");
            std::string dataDivider (";");
            unsigned int foo = entryDivider.length();
            unsigned int goo = dataDivider.length();
            while( tmp.find( dataDivider, lastPos ) != std::string::npos && tmp.find( entryDivider, lastCarriageRet ) != std::string::npos )
            {
                unsigned int nextCarriageRet = tmp.find( entryDivider, lastCarriageRet );
                FileEntry tmpEntry;
                while( tmp.find( dataDivider, lastPos ) != std::string::npos && tmp.find( dataDivider, lastPos ) < nextCarriageRet)
                {
                    unsigned int nextPos = tmp.find( dataDivider, lastPos );
                    std::string tmpstr = tmp.substr( lastPos, (nextPos - lastPos) );
                    tmpEntry.push_back( tmpstr );

                    lastPos = nextPos+goo;
                }
                lastCarriageRet = nextCarriageRet+foo+2;
                lastPos = lastCarriageRet;
                tmpData->push_back( tmpEntry );
                tmpEntry.clear();
            }
            return tmpData;
        }
        exit(1);
    }

    // std::string* visualAppearanceId; std::string* animationsDescriptionFile
    void GameObjectManager::loadVisualAppearances( std::string visualAppearanceFile )
    {
        FileData* dataFromFile = fetchFileData( &visualAppearanceFile, 2 );
        FileData::iterator itData;

        for( itData = dataFromFile->begin(); itData < dataFromFile->end(); itData++ )
        {
            FileEntry::iterator itEntry;
            FileEntry tmp = (*itData);
            itEntry = tmp.begin();

            std::string visualId = (*itEntry);
            itEntry++;
            std::string animationFile = (*itEntry);

            VisualAppearance* temporaryVisualAppearance = new VisualAppearance( visualId, animationFile );
            this->visualAppearancesLibrary_.push_back( temporaryVisualAppearance );
        }
    }

//    void GameObjectManager::loadAudioAppearances( std::string* audioAppearanceFile )

    GameObjectManager::GameObjectManager()
    {
    }

    GameObjectManager::~GameObjectManager()
    {
        this->spacialObjects_.clear();
        this->visualAppearancesLibrary_.clear();
    }
}
