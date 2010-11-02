#include <iostream>
#include <SFML/System.hpp>
#include <objects/gameObjectManager.hpp>
#include <objects/animation.hpp>
#include <gameWorld.hpp>
#include <main.hpp>
#include <stdio.h>
#include <objects/spacialObject.hpp>

#define ACCURACY 0.001
#define PI 3.14159
#define RATIO 32
#define RED 255,0,0,255
#define GREEN 0,255,0,255
#define BLUE 0,0,255,255
#define WHITE 255,255,255,255
#define YELLOW 255,255,0,255

struct flags{
    bool moveCameraUp;
    bool moveCameraDown;
    bool moveCameraLeft;
    bool moveCameraRight;

    bool showSprites;
    bool displaySpritesLibrary;

    bool Running;

/*bool createObject = false;
bool createAlignedBox = false;
bool createOrientedBox = false;
bool createCircle = false;
bool createPolygon = false;
bool createEdge = false;
bool created = false;*/

}globalflags;

sf::Mutex GlobalMutex;
GameWorld b2WorldAndVisualWorld;
sf::Vector2f resolution;

void inputThread(void* UserData)
{
    sf::Window* app = static_cast<sf::Window*>(UserData);
    const sf::Input* keyInput = &app->GetInput();
    while( globalflags.Running )
    {
        GlobalMutex.Lock();

        globalflags.moveCameraUp    = keyInput->IsKeyDown(sf::Key::Up);
        globalflags.moveCameraDown  = keyInput->IsKeyDown(sf::Key::Down);
        globalflags.moveCameraLeft  = keyInput->IsKeyDown(sf::Key::Left);
        globalflags.moveCameraRight = keyInput->IsKeyDown(sf::Key::Right);

        /*if(created){
            created = false;
            createAlignedBox = false;
            createCircle = false;
            createEdge = false;
            createOrientedBox = false;
            createPolygon = false;
        }

        if(createAlignedBox){

        }else if(createCircle){
        }else if(createEdge){
        }else if(createOrientedBox){
        }else if(createPolygon){
        }*/

        GlobalMutex.Unlock();
    }
}

int main()
{
    globalflags.moveCameraDown = false;
    globalflags.moveCameraLeft = false;
    globalflags.moveCameraRight = false;
    globalflags.moveCameraUp = false;
    globalflags.showSprites = true;
    globalflags.displaySpritesLibrary = false;
    globalflags.Running = true;

    resolution.x = 800;
    resolution.y = 600;

    //load settings and stuff
    sf::Font dejaVuSans;
    if(!dejaVuSans.LoadFromFile("data/DejaVuSans.ttf"))
    {
        exit(0);
    }
    sf::FloatRect ViewRect = sf::FloatRect(0, 0, resolution.x, resolution.y);
    sf::View twoDCam = sf::View(ViewRect);
    sf::RenderWindow App(sf::VideoMode(resolution.x, resolution.y, 32), "kajiya2D");
    App.UseVerticalSync(true);
    sf::Vector2f tmp;
    tmp.x = -( resolution.x/2 );
    tmp.y = -( resolution.y/2 );
    twoDCam.Move(tmp);
    App.SetView(twoDCam);

    /* Creating a fullscreen window with the best video mode supported
    App.Create(sf::VideoMode::GetMode(0), "SFML Window", sf::Style::Fullscreen);
    sf::VideoMode DesktopMode = sf::VideoMode::GetDesktopMode(); */

    sf::Thread inputHandler(&inputThread, &App);
    inputHandler.Launch();

    while (globalflags.Running)
    {
////////////////////            logic
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Window closed
            if (Event.Type == sf::Event::Closed){
                App.Close();
                globalflags.Running = false;
            }
            // Escape key pressed
            if(Event.Type == sf::Event::KeyPressed){
                if(Event.Key.Code == sf::Key::Escape){
                    App.Close();
                    globalflags.Running = false;
                }
                if(Event.Key.Code == sf::Key::F1){
                    if(globalflags.showSprites){
                        globalflags.showSprites = false;
                    }else{
                        globalflags.showSprites = true;
                    }
                }
                if(Event.Key.Code == sf::Key::F2){
                    if(globalflags.displaySpritesLibrary){
                        globalflags.displaySpritesLibrary = false;
                    }else{
                        globalflags.displaySpritesLibrary = true;
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

        sf::Vector2f tmpOffset;
        tmpOffset.x = 0;
        tmpOffset.y = 0;

        if(globalflags.moveCameraDown){
            tmpOffset.y += 10;
        }
        if(globalflags.moveCameraUp){
            tmpOffset.y -= 10;
        }
        if(globalflags.moveCameraLeft){
            tmpOffset.x -= 10;
        }
        if(globalflags.moveCameraRight){
            tmpOffset.x += 10;
        }

        sf::View tmpView = App.GetView();
        tmpView.Move(tmpOffset);
        App.SetView(tmpView);

        if(globalflags.displaySpritesLibrary){
            sf::Vector2f tmpSpritePosition;
            App.SetView(App.GetDefaultView());
            tmpSpritePosition.x = 10;
            tmpSpritePosition.y = 10;
            int i = 0;
            sf::String title("Visual Appearances Library", dejaVuSans, 15);
            sf::String spriteDesc;
            spriteDesc.SetFont(dejaVuSans);
            spriteDesc.SetSize(12);
            spriteDesc.SetColor(sf::Color( YELLOW ));
            title.SetColor(sf::Color( YELLOW ));
            title.Move(tmpSpritePosition);
            App.Draw(title);
            tmpSpritePosition.y += 30;
            objects::VisualAppearance* tmpAppearance = b2WorldAndVisualWorld.globalGameObjectManager_->nextVisualAppearance( i );
                //itearate through the animations and 
            while( tmpAppearance != NULL )
            {
                //move to next row, display next VA
                tmpSpritePosition.y += 10;

                //print the name/ID of the current animation
                objects::Animation* tmpAnim = tmpAppearance->getCurrentAnimation();
                spriteDesc.SetText( tmpAppearance->getVisualAppearanceId() + " " + tmpAnim->getAnimationId() );
                spriteDesc.SetPosition(tmpSpritePosition);
                App.Draw(spriteDesc);

                //move to next collumn, now display the current animation
                tmpSpritePosition.x += 150;
                sf::Sprite* tmpSprite = tmpAnim->getNextFrame();
                tmpSprite->SetPosition( tmpSpritePosition );
                tmpSprite->SetRotation( 0 );
                sf::Vector2f tmp = tmpSprite->GetCenter();
                tmpSprite->SetCenter( 0.0, 0.0 );

                App.Draw((*tmpSprite));
                tmpSprite->SetCenter( tmp );
                tmpSpritePosition.x += tmpSprite->GetSize().x + 20;

                sf::Sprite tmpAllFramesSprite;
                sf::Image* fooimage = tmpAnim->getAllFrames();
                tmpAllFramesSprite.SetImage((*fooimage));
                tmpAllFramesSprite.SetPosition( tmpSpritePosition );
                tmp = tmpAllFramesSprite.GetCenter();
                tmpAllFramesSprite.SetCenter( 0.0, 0.0 );
                App.Draw(tmpAllFramesSprite);
                tmpAllFramesSprite.SetCenter( tmp );
                tmpSpritePosition.y += tmpSprite->GetSize().y + 10;
                i++;
                tmpAppearance = b2WorldAndVisualWorld.globalGameObjectManager_->nextVisualAppearance( i );
                tmpSpritePosition.x = 10;
            }

            App.SetView(tmpView);
        }else{

    ////////////////////            drawing/evaluating data from the calculations
            int i = 0;
            objects::SpacialObject* tmpObject = b2WorldAndVisualWorld.globalGameObjectManager_->nextSpacialObject( i );
            while( tmpObject != NULL )
            {
                objects::Animation* tmpAnim = tmpObject->getVisualAppearance()->getCurrentAnimation();

                std::string object = tmpObject->getSpacialObjectId();
                if(globalflags.showSprites){
                    sf::Sprite* tmpSprite = tmpAnim->getNextFrame();
                    if( tmpObject->shape_ == objects::ALIGNED_BOX
                       || tmpObject->shape_ == objects::ORIENTED_BOX )
                       {
                           tmpSprite->SetPosition( (tmpObject->bodyDefinition_.position_.x*RATIO),
                                                  -(tmpObject->bodyDefinition_.position_.y*RATIO) );
                           tmpSprite->SetRotation( tmpObject->box_.angle*(180/PI) );
                           App.Draw( (*tmpSprite) );
                        }
                }
                else{
                    if( tmpObject->shape_ == objects::ALIGNED_BOX
                       || tmpObject->shape_ == objects::ORIENTED_BOX )
                       {
                           sf::Color innerColor;
                           sf::Color outlineColor;
                           if(tmpObject->bodyDefinition_.type_ == objects::STATIC){
                               innerColor = sf::Color( RED );
                           } else if(tmpObject->bodyDefinition_.type_ == objects::DYNAMIC){
                               innerColor = sf::Color( GREEN );
                           } else if(tmpObject->bodyDefinition_.type_ == objects::KINEMATIC){
                               innerColor = sf::Color( BLUE );
                           }else{
                               innerColor = sf::Color( WHITE );
                           }

                           if(tmpObject->selected_)
                           {
                               outlineColor = sf::Color( YELLOW );
                           }else
                           {
                               outlineColor = sf::Color( WHITE );
                           }

                           sf::Shape physicsSprite = sf::Shape::Rectangle(-tmpObject->box_.halfSize.x*RATIO,
                                                   -tmpObject->box_.halfSize.y*RATIO,
                                                   tmpObject->box_.halfSize.x*RATIO,
                                                   tmpObject->box_.halfSize.y*RATIO,
                                                   innerColor,
                                                   1.0f,
                                                   outlineColor);

                           physicsSprite.SetPosition(tmpObject->bodyDefinition_.position_.x*RATIO,
                                                     -tmpObject->bodyDefinition_.position_.y*RATIO);
                           physicsSprite.SetRotation(( tmpObject->box_.angle )*(180/PI));
                           physicsSprite.EnableFill(true);
                           App.Draw( physicsSprite );
                        }
                }
                i++;
                tmpObject = b2WorldAndVisualWorld.globalGameObjectManager_->nextSpacialObject( i );
            }
        }
        App.Display();
        App.Clear();
    }
    return EXIT_SUCCESS;
}
