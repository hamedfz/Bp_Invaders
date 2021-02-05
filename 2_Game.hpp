#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h>

enum State{ MainMenu , Playing , Win , Lose , Quit };

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
    //states
        State state;

    //time handling
        sf::Clock clock;

    //window
        sf::RenderWindow myWindow;

    //font section
        sf::Text text;
        sf::Font font;

    //background
        sf::Texture myBackgroundTex;
        sf::Sprite  myBackground;

    //myPlayer
        //player
        sf::Texture myPlayerTex;
        sf::Sprite myPlayerSample;
        std::vector<sf::Sprite> myPlayer;
        sf::Vector2f myPlayerCenter;
        //player health
        sf::Texture HeartTex;
        sf::Sprite HeartSample;
        std::vector<sf::Sprite> Hearts;

    //projectile
        //player projectile
        sf::Texture PlayerProjectileTex;
        sf::Sprite PlayerProjectileSample;
        std::vector<sf::Sprite> PlayerProjectiles;
        int ShootTimer;
        //enemy projectile
        sf::Texture eggProjectileTex;
        sf::Sprite eggProjectileSample;
        std::vector< sf::Sprite > eggProjectiles;
        int eggTimer;
        
    //enemy
        sf::Texture myEnemyTex;
        sf::Sprite myEnemy;
        std::vector<sf::Sprite> myEnemies;
        std::string Direction = "Left";
};
