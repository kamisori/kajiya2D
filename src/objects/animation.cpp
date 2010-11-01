#include <string>
#include <vector>
#include <objects/animation.hpp>
#include <conversion.hpp>
namespace objects
{
    void Animation::iterateToNextFrame(){
        this->currentFrame_++;
        if( this->currentFrame_ >= this->frames_.size() ){
            this->currentFrame_ = 0;
        }
    }

    sf::Sprite* Animation::getNextFrame()
    {
        this->iterateToNextFrame();
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

    std::string Animation::constructFileEntry()
    {
        std::string resultString;

        resultString = "";
        resultString += this->animationId_ + ";";
        resultString += this->fileName_ + ";";
        resultString += conversion::itoa(this->rowsAndCollumns_.x) + ";";
        resultString += conversion::itoa(this->rowsAndCollumns_.y) + ";";
        resultString += conversion::itoa(this->delayPerFrameInMs_) + ";\r\n";

        return resultString;
    }

    void Animation::loadPicture()
    {
        if( allFrames_->LoadFromFile( this->fileName_ ) )
        {
            sf::Vector2i* imageDimensions = new sf::Vector2i();
            sf::Vector2i* spriteDimensions = new sf::Vector2i();

            imageDimensions->y = this->allFrames_->GetHeight();
            imageDimensions->x = this->allFrames_->GetWidth();

            spriteDimensions->y = imageDimensions->y / this->rowsAndCollumns_.y;
            spriteDimensions->x = imageDimensions->x / this->rowsAndCollumns_.x;

            for( int y = 0; y <= imageDimensions->y - spriteDimensions->y; y += spriteDimensions->y )
            {
                for( int x = 0; x <= imageDimensions->x - spriteDimensions->x; x += spriteDimensions->x )
                {
                    sf::Sprite* temporarySprite = new sf::Sprite();

                    temporarySprite->SetCenter( ( spriteDimensions->x / 2 ), ( spriteDimensions->y / 2 ) );
                    temporarySprite->SetImage( (*allFrames_) );
                    temporarySprite->SetBlendMode(sf::Blend::None);
                    temporarySprite->SetSubRect( sf::IntRect( x, y, spriteDimensions->x, spriteDimensions->y ) );

                    this->frames_.push_back( temporarySprite );
                }
            }
        }
    }

    void Animation::buildAnimation()
    {
        this->allFrames_ = new sf::Image();

        loadPicture();

        if( this->frames_.size() != (unsigned) ( this->rowsAndCollumns_.x * this->rowsAndCollumns_.y ) )
        {
            exit(1);
        }
    }

    Animation::Animation(FileEntry inData)
    {
        FileEntry::iterator itEntry;
        itEntry = inData.begin();

        this->animationId_ = (*itEntry);
        itEntry++;
        this->fileName_ = (*itEntry);
        itEntry++;
        this->rowsAndCollumns_.x = atoi((*itEntry).c_str());
        itEntry++;
        this->rowsAndCollumns_.y = atoi((*itEntry).c_str());
        itEntry++;
        this->delayPerFrameInMs_ = atoi((*itEntry).c_str());

        buildAnimation();
    }

    Animation::~Animation(){
        this->frames_.clear();
        delete this->allFrames_;
    }
}
