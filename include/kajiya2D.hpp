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

struct MouseClick{
    sf::Mouse::Button clickButton;
    int X;
    int Y;
    bool pressed;
};

class InputHandler :public sf::Thread
{
    private:
        const sf::Input* keyInput_;
        virtual void Run();
    public:
        MouseClick* mouseClickEvent_;
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
