#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <stdio.h>

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>

#include <objects/gameObjectManager.hpp>
#include <objects/gameObjectManager.hpp>
#include <objects/animation.hpp>
#include <objects/spacialObject.hpp>
#include <kajiya2D.hpp>
#include <conversion.hpp>

#define NACCURACY 1000
#define PI 3.14159
#define RATIO 32

#define RED 255,0,0,255
#define GREEN 0,255,0,255
#define BLUE 0,0,255,255

#define WHITE 255,255,255,255
#define BLACK 0, 0, 0, 255

#define YELLOW 255,255,0,255




InputHandler::InputHandler(sf::RenderWindow* appWindow, sf::Mutex* GlobalMutex)
{
    keyInput_ = &appWindow->GetInput();
    GlobalMutex_ = GlobalMutex;

    globalflags_.moveCameraDown = false;
    globalflags_.moveCameraLeft = false;
    globalflags_.moveCameraRight = false;
    globalflags_.moveCameraUp = false;
    globalflags_.showSprites = true;
    globalflags_.displaySpritesLibrary = false;
    globalflags_.Running = true;

    globalflags_.createObject = false;
    globalflags_.createAlignedBox = false;
    globalflags_.createOrientedBox = false;
    globalflags_.createCircle = false;
    globalflags_.createPolygon = false;
    globalflags_.createEdge = false;
    globalflags_.created = false;

    Launch();
}
InputHandler::~InputHandler()
{
    Terminate();
}


void InputHandler::Run()
{
    while( globalflags_.Running )
    {
        GlobalMutex_->Lock();

        globalflags_.moveCameraUp    = keyInput_->IsKeyDown(sf::Key::Up);
        globalflags_.moveCameraDown  = keyInput_->IsKeyDown(sf::Key::Down);
        globalflags_.moveCameraLeft  = keyInput_->IsKeyDown(sf::Key::Left);
        globalflags_.moveCameraRight = keyInput_->IsKeyDown(sf::Key::Right);
/*
        if(globalflags_.created){
            globalflags_.created = false;
            globalflags_.createAlignedBox = false;
            globalflags_.createCircle = false;
            globalflags_.createEdge = false;
            globalflags_.createOrientedBox = false;
            globalflags_.createPolygon = false;
        }

        if(globalflags_.createAlignedBox){

        }else if(globalflags_.createCircle){
        }else if(globalflags_.createEdge){
        }else if(globalflags_.createOrientedBox){
        }else if(globalflags_.createPolygon){
        }
*/
        GlobalMutex_->Unlock();
    }
}

void kajiya2D::loadLevelData( std::string worldname, std::string levelname )
{
    std::string visualAppearancesFile ( "data/visualAppearances.data" );
    std::string materialFile ( "data/materials.data" );
    std::string objectFile ( "data/spacialObjects.data" );

    this->globalGameObjectManager_ = new objects::GameObjectManager();

    this->globalGameObjectManager_->loadVisualAppearances( visualAppearancesFile );
    this->globalGameObjectManager_->loadMaterials( materialFile );
    this->globalGameObjectManager_->loadObjects( objectFile );
}

void kajiya2D::intitializeRenderContext()
{
    resolution_.x = 800;
    resolution_.y = 600;

    if(!dejaVuSans_.LoadFromFile("data/DejaVuSans.ttf"))
    {
        exit(0);
    }

    ViewRect_ = sf::FloatRect(0, 0, resolution_.x, resolution_.y);
    twoDCam_ = sf::View(ViewRect_);
    appWindow_ = new sf::RenderWindow(sf::VideoMode(resolution_.x, resolution_.y, 32), "kajiya2D");
    appWindow_->UseVerticalSync(true);

    /* Creating a fullscreen window with the best video mode supported
    App.Create(sf::VideoMode::GetMode(0), "SFML Window", sf::Style::Fullscreen);
    sf::VideoMode DesktopMode = sf::VideoMode::GetDesktopMode(); */

    sf::Vector2f tmp;
    tmp.x = -( resolution_.x/2 );
    tmp.y = -( resolution_.y/2 );
    twoDCam_.Move(tmp);
    appWindow_->SetView(twoDCam_);
}

void kajiya2D::initializeThreads()
{
    GlobalMutex_ = new sf::Mutex();
    inputHandlerThread_ = new InputHandler(appWindow_, GlobalMutex_);
}

void kajiya2D::handleEvents()
{
    handleSystemEvents();
    handleInputEvents();
}

void kajiya2D::handleSystemEvents()
{
    sf::Event Event;
    while (appWindow_->GetEvent(Event))
    {
        //close window
        if (Event.Type == sf::Event::Closed){
            appWindow_->Close();
            inputHandlerThread_->globalflags_.Running = false;
        }
        // Escape key pressed
        if(Event.Type == sf::Event::KeyPressed){
            if(Event.Key.Code == sf::Key::Escape){
                appWindow_->Close();
                inputHandlerThread_->globalflags_.Running = false;
            }
            if(Event.Key.Code == sf::Key::F1){
                if(inputHandlerThread_->globalflags_.showSprites){
                    inputHandlerThread_->globalflags_.showSprites = false;
                }else{
                    inputHandlerThread_->globalflags_.showSprites = true;
                }
            }
            if(Event.Key.Code == sf::Key::F2){
                if(inputHandlerThread_->globalflags_.displaySpritesLibrary){
                    inputHandlerThread_->globalflags_.displaySpritesLibrary = false;
                }else{
                    inputHandlerThread_->globalflags_.displaySpritesLibrary = true;
                }
            }
/*                if(Event.Key.Code == sf::Key::F5){
                //save
            }
            if(Event.Key.Code == sf::Key::F6){
                //(re)load
            }
            if(Event.Key.Code == sf::Key::N){
                createObject = true;
            }

            if(createObject)
            {
                if(Event.Key.Code == sf::Key::A){
                    createObject = false;
                    createAlignedBox = true;
                }else if(Event.Key.Code == sf::Key::O){
                    createObject = false;
                    createOrientedBox = true;
                }else if(Event.Key.Code == sf::Key::C){
                    createObject = false;
                    createCircle = true;
                }else if(Event.Key.Code == sf::Key::P){
                    createObject = false;
                    createPolygon = true;
                }else if(Event.Key.Code == sf::Key::E){
                    createObject = false;
                    createEdge = true;
                }
            }*/

        }
    }
}

void kajiya2D::handleInputEvents()
{
    sf::Vector2f tmpOffset;
    tmpOffset.x = 0;
    tmpOffset.y = 0;

    if(inputHandlerThread_->globalflags_.moveCameraDown){
        tmpOffset.y += 10;
    }
    if(inputHandlerThread_->globalflags_.moveCameraUp){
        tmpOffset.y -= 10;
    }
    if(inputHandlerThread_->globalflags_.moveCameraLeft){
        tmpOffset.x -= 10;
    }
    if(inputHandlerThread_->globalflags_.moveCameraRight){
        tmpOffset.x += 10;
    }

    twoDCam_.Move(tmpOffset);
    //std::cout << conversion::itoa( (int)(twoDCam_.GetCenter().x * NACCURACY) );
    //std::cout << conversion::itoa( (int)(twoDCam_.GetCenter().y * NACCURACY) )<< "\r\n";
    appWindow_->SetView(twoDCam_);
}

void kajiya2D::displaySpritesLibrary()
{
    sf::Vector2f tmpSpritePosition;
    appWindow_->SetView(appWindow_->GetDefaultView());
    tmpSpritePosition.x = 10;
    tmpSpritePosition.y = 10;
    int i = 0;
    sf::String title("Visual Appearances Library", dejaVuSans_, 15);
    sf::String spriteDesc;
    spriteDesc.SetFont(dejaVuSans_);
    spriteDesc.SetSize(12);
    spriteDesc.SetColor(sf::Color( YELLOW ));
    title.SetColor(sf::Color( YELLOW ));
    title.Move(tmpSpritePosition);
    appWindow_->Draw(title);
    tmpSpritePosition.y += 30;
    objects::VisualAppearance* tmpAppearance = globalGameObjectManager_->nextVisualAppearance( i );
    //itearate through the animations and
    while( tmpAppearance != NULL )
    {
        //move to next row, display next VA
        tmpSpritePosition.y += 10;
        //itearate through the animations
        objects::Animation* tmpAnim = tmpAppearance->getCurrentAnimation();

        //print the name/ID of the current animation
        spriteDesc.SetText( tmpAppearance->getVisualAppearanceId() + " " + tmpAnim->getAnimationId() );
        spriteDesc.SetPosition(tmpSpritePosition);
        appWindow_->Draw(spriteDesc);

        //move to next collumn, now display the current animation
        tmpSpritePosition.x += 150;
        sf::Sprite* tmpSprite = tmpAnim->getNextFrame();
        tmpSprite->SetPosition( tmpSpritePosition );
        tmpSprite->SetRotation( 0 );
        sf::Vector2f tmp = tmpSprite->GetCenter();
        tmpSprite->SetCenter( 0.0, 0.0 );

        appWindow_->Draw((*tmpSprite));
        tmpSprite->SetCenter( tmp );
        tmpSpritePosition.x += tmpSprite->GetSize().x + 20;

        sf::Sprite tmpAllFramesSprite;
        sf::Image* fooimage = tmpAnim->getAllFrames();
        tmpAllFramesSprite.SetImage((*fooimage));
        tmpAllFramesSprite.SetPosition( tmpSpritePosition );
        tmp = tmpAllFramesSprite.GetCenter();
        tmpAllFramesSprite.SetCenter( 0.0, 0.0 );
        appWindow_->Draw(tmpAllFramesSprite);
        tmpAllFramesSprite.SetCenter( tmp );
        tmpSpritePosition.y += tmpSprite->GetSize().y + 10;
        i++;
        tmpAppearance = globalGameObjectManager_->nextVisualAppearance( i );
        tmpSpritePosition.x = 10;
    }
}

void kajiya2D::showObjectWithTextures( objects::SpacialObject* tmpObject )
{
    objects::Animation* tmpAnim = tmpObject->getVisualAppearance()->getCurrentAnimation();
    sf::Sprite* tmpSprite = tmpAnim->getNextFrame();

    if( tmpObject->shape_ == objects::ALIGNED_BOX ||
        tmpObject->shape_ == objects::ORIENTED_BOX )
    {
        tmpSprite->SetPosition( ( tmpObject->bodyDefinition_.position_.x*RATIO ),
                               -( tmpObject->bodyDefinition_.position_.y*RATIO ) );

        tmpSprite->SetRotation( tmpObject->box_.angle*(180/PI) );
        appWindow_->Draw( (*tmpSprite) );
    }
}

void kajiya2D::showObject( objects::SpacialObject* tmpObject )
{
    if( tmpObject->shape_ == objects::ALIGNED_BOX ||
        tmpObject->shape_ == objects::ORIENTED_BOX )
    {
       sf::Color innerColor;
       sf::Color outlineColor;
       if(tmpObject->bodyDefinition_.type_ == objects::STATIC)
       {
           innerColor = sf::Color( RED );
       }
       else if(tmpObject->bodyDefinition_.type_ == objects::DYNAMIC)
       {
           innerColor = sf::Color( GREEN );
       }
       else if(tmpObject->bodyDefinition_.type_ == objects::KINEMATIC)
       {
           innerColor = sf::Color( BLUE );
       }
       else
       {
           innerColor = sf::Color( WHITE );
       }

       if(tmpObject->selected_)
       {
           outlineColor = sf::Color( YELLOW );
       }
       else
       {
           outlineColor = sf::Color( WHITE );
       }

       sf::Shape physicsSprite = sf::Shape::Rectangle( -tmpObject->box_.halfSize.x*RATIO,
                                                       -tmpObject->box_.halfSize.y*RATIO,
                                                        tmpObject->box_.halfSize.x*RATIO,
                                                        tmpObject->box_.halfSize.y*RATIO,
                                                        innerColor,
                                                        1.0f,                           //Outline thicknes i think
                                                        outlineColor );

       physicsSprite.SetPosition( tmpObject->bodyDefinition_.position_.x*RATIO,
                                 -tmpObject->bodyDefinition_.position_.y*RATIO);
       physicsSprite.SetRotation( ( tmpObject->box_.angle ) * (180/PI) );
       physicsSprite.EnableFill( true );

       appWindow_->Draw( physicsSprite );
    }
}

void kajiya2D::displayLevel()
{
    int i = 0;
    objects::SpacialObject* tmpObject = globalGameObjectManager_->nextSpacialObject( i );
    while( tmpObject != NULL )
    {
        if(inputHandlerThread_->globalflags_.showSprites){
            showObjectWithTextures( tmpObject );
        }
        else{
            showObject( tmpObject );
        }
        i++;
        tmpObject = globalGameObjectManager_->nextSpacialObject( i );
    }

}

void kajiya2D::runKajiya2D()
{
    while (inputHandlerThread_->globalflags_.Running)
    {
        handleEvents();
        if(inputHandlerThread_->globalflags_.displaySpritesLibrary)
        {
            displaySpritesLibrary();
        }
        else
        {
            displayLevel();
        }
        appWindow_->Display();
        appWindow_->Clear();
    }
}

kajiya2D::kajiya2D()
{
    //this->globalGameObjectManager_->saveObjects( objectFile );
    //this->globalGameObjectManager_->saveMaterials( materialFile );
    //this->globalGameObjectManager_->saveVisualAppearances( visualAppearancesFile );

    loadLevelData("","");
    intitializeRenderContext();
    initializeThreads();
}

kajiya2D::~kajiya2D(){
    delete this->globalGameObjectManager_;
}
