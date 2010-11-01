#include <string>
#include <vector>
#include <map>
#include <objects/gameObjectManager.hpp>
#include <gameWorld.hpp>
#include <Box2D/Box2D.h>

GameWorld::GameWorld()
{
    std::string visualAppearancesFile ( "data/visualAppearances.data" );
    std::string materialFile ( "data/materials.data" );
    std::string objectFile ( "data/spacialObjects.data" );

    this->globalGameObjectManager_ = new objects::GameObjectManager();

    this->globalGameObjectManager_->loadVisualAppearances( visualAppearancesFile );
    this->globalGameObjectManager_->loadMaterials( materialFile );
    this->globalGameObjectManager_->loadObjects( objectFile );

    //this->globalGameObjectManager_->saveObjects( objectFile );
    //this->globalGameObjectManager_->saveMaterials( materialFile );
    //this->globalGameObjectManager_->saveVisualAppearances( visualAppearancesFile );
}

GameWorld::~GameWorld(){
    delete this->globalGameObjectManager_;
}
