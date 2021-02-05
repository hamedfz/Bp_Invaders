#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
        bool stateSet = false;

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
        sf::Sprite myPlayer;
        sf::Vector2f myPlayerCenter;
        //player health
        sf::Texture HeartTex;
        sf::Sprite HeartSample;
        std::vector<sf::Sprite> Hearts;
        //player explosion
        sf::SoundBuffer explosionBuffer;
        sf::Sound explosionSound;

    //projectile
        //player projectile
        sf::Texture PlayerProjectileTex;
        sf::Sprite PlayerProjectileSample;
        std::vector<sf::Sprite> PlayerProjectiles;
            //sounds
        sf::SoundBuffer ShootBuffer;
        sf::Sound ShootSound;
        sf::SoundBuffer ChickenHitBuffer;
        sf::Sound ChickenHitSound;
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
