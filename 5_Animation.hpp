#pragma once

#include "0_Info.hpp"
#include "2_Game.hpp"

class Animation
{
    private:
        /* data */
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;
        float totalTime;
        float switchTime;

    public:
        sf::IntRect uvRect;
    
    public:
        Animation();
        
        void setValues(sf::Texture &texture , sf::Vector2u imageCount , float switchTime);
        void Update( int row , float deltaTime );
};