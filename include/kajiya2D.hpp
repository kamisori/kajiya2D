#ifndef KAJIYA2D_HPP
#define KAJIYA2D_HPP

#include <string>
#include <vector>
#include <map>
#include <objects/gameObjectManager.hpp>
#include <Box2D/Box2D.h>

struct flags{
    bool moveCameraUp;
    bool moveCameraDown;
    bool moveCameraLeft;
    bool moveCameraRight;

    bool showSprites;
    bool displaySpritesLibrary;

    bool Running;

    bool createObject;
    bool createAlignedBox;
    bool createOrientedBox;
    bool createCircle;
    bool createPolygon;
    bool createEdge;
    bool created;
};

class InputHandler :public sf::Thread
{
    private:
        const sf::Input* keyInput_;
        virtual void Run();
    public:
        sf::Mutex* GlobalMutex_;
        flags globalflags_;
        InputHandler(sf::RenderWindow* appWindow, sf::Mutex* GlobalMutex);
        ~InputHandler();
};

class kajiya2D
{
    public:
        sf::Font dejaVuSans_;

        sf::RenderWindow* appWindow_;
        sf::Thread* inputHandler_;

        sf::FloatRect ViewRect_;
        sf::View twoDCam_;

        sf::Mutex* GlobalMutex_;
        sf::Vector2f resolution_;

        objects::GameObjectManager* globalGameObjectManager_;

        InputHandler* inputHandlerThread_;
        void runKajiya2D();
        kajiya2D();
        ~kajiya2D();
    protected:

    private:
    void displaySpritesLibrary();
    void displayLevel();

    void showObjectWithTextures( objects::SpacialObject* tmpObject );
    void showObject( objects::SpacialObject* tmpObject );

    void handleEvents();
    void handleSystemEvents();
    void handleInputEvents();

    void intitializeRenderContext();
    void initializeThreads();

    void loadLevelData( std::string worldname, std::string levelname );
    void saveLevelData( std::string worldname, std::string levelname );
};

#endif
