#ifndef VISUALAPPEARANCE_HPP
#define VISUALAPPEARANCE_HPP

#include <string>
#include <vector>
#include <objects/animation.hpp>
namespace objects
{
    class VisualAppearance
    {
        public:
            void        setCurrentAnimationByAnimationId( std::string animationId );
            Animation*  getCurrentAnimation();
            std::string getVisualAppearanceId();

            std::string constructFileEntry();
            VisualAppearance( FileEntry inData );
            ~VisualAppearance();
        protected:

        private:
            void loadAnimations();

            std::string                 animationsDescriptionFile_;
            std::string                 visualAppearanceId_;
            std::vector< Animation* >   possibleAnimations_;
            Animation*                  currentAnimation_;
    };
}
#endif
