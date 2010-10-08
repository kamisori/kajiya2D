#include <string>
#include <vector>
#include <objects/animation.hpp>
namespace objects
{
    void Animation::next(){
        this->currentFrame_++;
        if( this->currentFrame_ >= this->frames_.size() ){
            this->currentFrame_ = 0;
        }
    }

    //increase currentFrame_ and return new current Sprite*
    sf::Sprite* Animation::nextFrame()
    {
        this->next();
        return this->frames_[this->currentFrame_];
    }

    sf::Image* Animation::getAllFrames()
    {
        return this->allFrames_;
    }

    std::string Animation::getAnimationId()
    {
        return this->animationId_;
    }

    //data will be provided from a csv style file something like "running_fox_north";"fox1.bmp";3;5; with 3 rows of frames and 5 collumns
    Animation::Animation( std::string animationId, std::string fileName, sf::Vector2i rowsAndCollumns, int delayPerFrame ){
        this->animationId_ = animationId;
        this->delayPerFrame_ = delayPerFrame;
        this->allFrames_ = new sf::Image();
        if( allFrames_->LoadFromFile( fileName ) ){
//            this->allFrames_ = &temporaryImage;

            sf::Vector2i* imageDimensions = new sf::Vector2i();
            sf::Vector2i* spriteDimensions = new sf::Vector2i();
            imageDimensions->y = this->allFrames_->GetHeight();
            imageDimensions->x = this->allFrames_->GetWidth();

            spriteDimensions->y = imageDimensions->y / rowsAndCollumns.y;
            spriteDimensions->x = imageDimensions->x / rowsAndCollumns.x;
            for( int y = 0; y <= imageDimensions->y - spriteDimensions->y; y += spriteDimensions->y ){
                for( int x = 0; x <= imageDimensions->x - spriteDimensions->x; x += spriteDimensions->x ){
                    sf::Sprite* temporarySprite = new sf::Sprite();
                    temporarySprite->SetCenter( ( spriteDimensions->x / 2 ), ( spriteDimensions->y / 2 ) );
                    temporarySprite->SetImage( (*allFrames_) );
                    temporarySprite->SetBlendMode(sf::Blend::None);
                    temporarySprite->SetSubRect( sf::IntRect( x, y, spriteDimensions->x, spriteDimensions->y ) );
                    this->frames_.push_back( temporarySprite );
                }
            }

            if( this->frames_.size() != (unsigned) ( rowsAndCollumns.x * rowsAndCollumns.y ) )
            {
                exit(1);
            }
        }
    }

    Animation::Animation(){
        exit(1);
    }
    Animation::~Animation(){
        this->frames_.clear();
        delete this->allFrames_;
    }
}
