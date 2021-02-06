#include "2_Game.hpp"
#include "0_Info.hpp"
#include <iostream>

Game::Game() 
{
    //state
    state = Playing;

    //window section
    myWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Space Invaders");
    myWindow.setFramerateLimit(FRAMERATE_LIMIT);
    myWindow.setPosition(sf::Vector2i(250,50));

    //background section
    if( !myBackgroundTex.loadFromFile("res/background2.png"))
    {
        throw "Background Image Missing";
    }
    myBackground.setTexture(myBackgroundTex);
    myBackground.setScale( SCREEN_WIDTH/myBackground.getLocalBounds().width , SCREEN_HEIGHT/myBackground.getLocalBounds().height );

    //txt file for scores
    //ptr = fopen("res/score.txt","r");
    //fscanf(ptr,"%d%d",&minFile,&secFile);
    //fclose(ptr);

    //explosion animation
            //if( !explosionTex.loadFromFile("res/explosionSheet.png") )
            //{
            //    throw "explosion spirit sheet Missing";
            //}
            //animation.setValues( explosionTex , sf::Vector2u(5,3) , 0.3f );

    //font and messages section 
    if( !font.loadFromFile("res/arial.ttf") || !funFont.loadFromFile("res/TropicalAsian.ttf") )
    {
        throw "Font Missing";
    }
    messageText.setFont(funFont);
    messageText.setCharacterSize(100);
    messageText.setOutlineThickness(5);
    messageText.setPosition(myWindow.getSize().x/2 - 150 , myWindow.getSize().y/2 - 100 );
    scoreText.setFont(funFont);
    scoreText.setCharacterSize(50);
    scoreText.setOutlineThickness(5);
    scoreText.setString("Stopwatch");
    scoreText.move( 5 , -5 );
    //bestScoreText.setFont(funFont);
    //bestScoreText.setCharacterSize(50);
    //bestScoreText.setOutlineThickness(5);
    //bestScoreText.setString("Best Score");
    //bestScoreText.move(100,100);

    //time handling
    myClock.restart().asSeconds();
    myTimerText.setFont(font);
    myTimerText.setCharacterSize(25);
    myTimerText.move( 180 , 15 );
    myTimerText.setOutlineThickness(5);
    myTimerText.setFillColor(sf::Color::Yellow);
    myTimerText.setString("0 : 0");

    //myPlayer creation
    if( !myPlayerTex.loadFromFile("res/myPlayer.png") )
    {
        throw "myPlayer Image Missing";
    }
    myPlayer.setTexture(myPlayerTex);
    myPlayer.setScale(MYPLAYER_WIDTH/myPlayer.getLocalBounds().width , MYPLAYER_HEIGHT/myPlayer.getLocalBounds().height);
    myPlayer.setPosition(myWindow.getSize().x/2 , myWindow.getSize().y - myPlayer.getLocalBounds().height/2 - 20 );
    myPlayerCenter = sf::Vector2f( myPlayer.getPosition().x + myPlayer.getGlobalBounds().width/2 - 4 , myPlayer.getPosition().y + myPlayer.getGlobalBounds().height/2 );
        //hearts
    if( !HeartTex.loadFromFile("res/heart.png") )
    {
        throw "Heart Image Missing";
    }
    HeartSample.setTexture(HeartTex);
    HeartSample.setScale( 30 / HeartSample.getLocalBounds().width , 30/HeartSample.getLocalBounds().height );
    HeartSample.setPosition( 15 , myWindow.getSize().y - HeartSample.getGlobalBounds().height - 15 );
    HealthText.setPosition( 55 , HeartSample.getPosition().y );
    HealthText.setFont(font);
    HealthText.setCharacterSize(25);
    HealthText.setFillColor(sf::Color::Yellow);
    HealthText.setString("3");
    HealthText.setOutlineThickness(5);

        //explosion
    if( !explosionBuffer.loadFromFile("res/playerExplode.oga") )
    {
        throw "playerExplode Missing";
    }    
    explosionSound.setBuffer(explosionBuffer);

    //projectile creation
        //player projectile
    if( !PlayerProjectileTex.loadFromFile("res/PlayerProjectile.png") )
    {
        throw "PlayerProjectile Image Missing";
    }
    ShootTimer = 0;
    PlayerProjectileSample.setTexture(PlayerProjectileTex);
    PlayerProjectileSample.setScale( 20 / PlayerProjectileSample.getLocalBounds().width , 45/PlayerProjectileSample.getLocalBounds().height );
    if( !ShootBuffer.loadFromFile("res/ShootSound.oga") )
    {
        throw "ShootSound Missing";
    }
    ShootSound.setBuffer(ShootBuffer);
    if( !ChickenHitBuffer.loadFromFile("res/chickenhit.oga") )
    {
        throw "chickenhit Missing";
    }
    ChickenHitSound.setBuffer(ChickenHitBuffer);
    ProjectileLimitText.setFont(font);
    ProjectileLimitText.setCharacterSize(25);
    ProjectileLimitText.setOutlineThickness(5);
    ProjectileLimitText.setFillColor(sf::Color::Yellow);
    ProjectileLimitText.setPosition( 127 , myWindow.getSize().y - HeartSample.getGlobalBounds().height - 15  );
    ProjectileInfo.setTexture(PlayerProjectileTex);
    ProjectileInfo.setScale( 20 / PlayerProjectileSample.getLocalBounds().width , 45/PlayerProjectileSample.getLocalBounds().height );
    ProjectileInfo.setPosition(100,myWindow.getSize().y - 53 );

        //enemy projectile
    if( !eggProjectileTex.loadFromFile("res/egg.png") )
    {
        throw "eggProjectile Image Missing";
    }
    eggProjectileSample.setTexture(eggProjectileTex);
    eggTimer = 0;
    if( !eggShipBuffer.loadFromFile("res/eggShip.oga") )
    {
        throw "eggShip Missing";
    }
    eggShipSound.setBuffer(eggShipBuffer);

        //eggsplash
    if( !eggSplashTex.loadFromFile("res/eggSplash.png") )
    {
        throw "eggSplash Image Missing";
    }
    eggSplashSample.setTexture(eggSplashTex);

    if( !eggDestroyedBuffer.loadFromFile("res/eggdestroy.oga") )
    {
        throw "eggSplash sound Missing";
    }
    eggDestroyedSound.setBuffer(eggDestroyedBuffer);

        //gifts
    if( !giftTex.loadFromFile("res/gift.png") )
    {
        throw "gift Image Missing";
    }
    giftSample.setTexture(giftTex);
    //reward sound
    rewardBuffer.loadFromFile("res/reward.wav");
    rewardSound.setBuffer(rewardBuffer);

    //enemy creation
    if(!myEnemyTex.loadFromFile("res/ChickenEnemy.png"))
    {
        throw "ChickenEnemy Image Missing";
    }
    myEnemy.setTexture(myEnemyTex);
    myEnemy.setScale(60/myEnemy.getLocalBounds().width , 70/myEnemy.getLocalBounds().height);
    myEnemy.setPosition(myWindow.getSize().x/2 - myEnemy.getGlobalBounds().width/2 , myWindow.getSize().y/2 - myEnemy.getGlobalBounds().height/2);
    for( int i = 0 ; i < 35 ; i++ )
    {
        myEnemies.push_back(myEnemy);
        myEnemies[i].move( (i%7-2)*(myEnemy.getGlobalBounds().width + 50 ) , 0 );
        if( i % 7 == 6 )
        {
            myEnemy.move(0,-myEnemy.getGlobalBounds().height-10);
        }
    }

    //meats
    if( !meatTex.loadFromFile("res/meat.png") )
    {
        throw "meat Image Missing";
    }
    meatSample.setTexture(meatTex);
    meatSample.setScale(0.7,0.8);
    if( !meatSoundBuffer.loadFromFile("res/foodeat.oga") )
    {
        throw "eat food sound Missing";
    }
    meatSound.setBuffer(meatSoundBuffer);

    //sounds
    if( !winSoundBuffer.loadFromFile("res/youwin.ogg") )
    {
        throw "winSound Missing";
    }
    winSound.setBuffer(winSoundBuffer);
}