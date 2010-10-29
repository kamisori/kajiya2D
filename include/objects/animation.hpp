#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace objects
{
#define SPRITE_SIZE 32
    typedef std::vector< std::string > FileEntry;
    class Animation
    {
        public:
            sf::Sprite* getNextFrame();
            std::string getAnimationId();

            sf::Image* getAllFrames();

            std::string constructFileEntry();
            Animation( FileEntry inData );
            ~Animation();
        protected:

        private:
            void iterateToNextFrame();

            void loadPicture();
            void buildAnimation();

            sf::Vector2i rowsAndCollumns_;
            int delayPerFrameInMs_;
            std::string animationId_;
            sf::Image* allFrames_;
            std::string fileName_;
            std::vector< sf::Sprite* > frames_;
            unsigned int currentFrame_;
    };
}
#endif
