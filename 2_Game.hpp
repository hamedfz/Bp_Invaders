#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>


class Game
{
    public:
        Game();
        void run();
    private:
        void processEvents();
        void update();
        void render();

    private:
        sf::RenderWindow myWindow;

        bool win = false;
        sf::Text text;
        sf::Font font;

        //background
        sf::Texture myBackgroundTex;
        sf::Sprite  myBackground;

        //myPlayer
        sf::Texture myPlayerTex;
        sf::Sprite myPlayer;
        sf::Vector2f myPlayerCenter;
        int shootTimer;

        //projectile
            //player projectile
        sf::Texture PlayerProjectileTex;
        sf::Sprite PlayerProjectileSample;
        std::vector<sf::Sprite> PlayerProjectiles;
            //enemy projectile
        
        //enemy
        sf::Texture myEnemyTex;
        sf::Sprite myEnemy;
        std::vector<sf::Sprite> myEnemies_0_;
        std::vector<sf::Sprite> myEnemies_1_;
        std::vector<sf::Sprite> myEnemies_2_;
        std::vector<sf::Sprite> myEnemies_3_;
        std::vector<sf::Sprite> myEnemies_4_;
        std::string Direction = "Left";
};
