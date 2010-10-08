#include <string>
#include <vector>
#include <map>
#include <objects/gameObjectManager.hpp>
#include <gameWorld.hpp>
#include <Box2D/Box2D.h>

GameWorld::GameWorld()
{

    this->globalGameObjectManager_ = new objects::GameObjectManager();
    std::string visualAppearancesFile ("data/visualAppearances.data");
    this->globalGameObjectManager_->loadVisualAppearances( visualAppearancesFile );

    std::string objectFile ("data/spacialObjects.data");
    this->globalGameObjectManager_->loadObjects( objectFile );
}

GameWorld::~GameWorld(){
    delete this->globalGameObjectManager_;
}
