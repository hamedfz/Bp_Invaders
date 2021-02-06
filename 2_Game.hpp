#pragma once

#include "0_Info.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <stdlib.h>

enum State{ MainMenu , Playing , Win , Lose , Pause , Resume };

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
    
    //texts messages
        sf::Text messageText , scoreText ; // , bestScoreText;

    //time handling
        sf::Clock myClock;
        sf::Text myTimerText;
        int min = 0;
        int sec = 0;

    //window
        sf::RenderWindow myWindow;
    
    //txt file
        //FILE *ptr;
        //int minFile , secFile;

    //explosion texture and animation
        //sf::Texture explosionTex;
        //Animation animation;
        //float deltaTime = 0.0f;
        //sf::Clock clockDeltaTime;

    //font section
        sf::Font funFont;
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
        int Health = HEALTH; 
        sf::Texture HeartTex;
        sf::Sprite HeartSample;
        std::vector<sf::Sprite> Hearts;
        sf::Text HealthText;
        //player explosion
        sf::SoundBuffer explosionBuffer;
        sf::Sound explosionSound;
        sf::SoundBuffer winSoundBuffer;
        sf::Sound winSound;

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
        int ProjectileLimit = 25;
        int ShootTimer = 0;
        sf::Text ProjectileLimitText;
        sf::Sprite ProjectileInfo;

        //enemy projectile
        sf::Texture eggProjectileTex;
        sf::Sprite eggProjectileSample;
        std::vector< sf::Sprite > eggProjectiles;
        sf::SoundBuffer eggShipBuffer;
        sf::Sound eggShipSound;
        int eggTimer;

        //eggSplash
        sf::Texture eggSplashTex;
        sf::Sprite eggSplashSample;
        std::vector<sf::Sprite> eggSplash;
        std::vector<int> eggSplashTimer;
        sf::SoundBuffer eggDestroyedBuffer;
        sf::Sound eggDestroyedSound;
        
        //gifts
        sf::Texture giftTex;
        sf::Sprite giftSample;
        std::vector< sf::Sprite > gifts;
        int giftTimer = 0;
        sf::SoundBuffer rewardBuffer;
        sf::Sound rewardSound;

        //meat spirits and sound
        sf::Texture meatTex;
        sf::Sprite meatSample;
        std::vector< sf::Sprite > meats;
        sf::SoundBuffer meatSoundBuffer;
        sf::Sound meatSound;

    //enemy
        sf::Texture myEnemyTex;
        sf::Sprite myEnemy;
        std::vector<sf::Sprite> myEnemies;
        std::string Direction = "Left";
};
