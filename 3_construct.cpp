#include "2_Game.hpp"
#include "1_Info.hpp"
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
    if( !myBackgroundTex.loadFromFile("res/background.png"))
    {
        throw "Background Image Missing";
    }
    myBackground.setTexture(myBackgroundTex);
    myBackground.setScale( SCREEN_WIDTH/myBackground.getLocalBounds().width , SCREEN_HEIGHT/myBackground.getLocalBounds().height );



    //font section
    if( !font.loadFromFile("res/arial.ttf"))
    {
        throw "Font Missing";
    }
    text.setFont(font);
    text.setFillColor( sf::Color::Magenta);
    text.setCharacterSize(50);
    text.setPosition(myWindow.getSize().x/2 - 100 , myWindow.getSize().y/2 - 50 );


    //myPlayer creation
    if( !myPlayerTex.loadFromFile("res/myPlayer.png") )
    {
        throw "myPlayer Image Missing";
    }
    myPlayerSample.setTexture(myPlayerTex);
    myPlayerSample.setScale(MYPLAYER_WIDTH/myPlayerSample.getLocalBounds().width , MYPLAYER_HEIGHT/myPlayerSample.getLocalBounds().height);
    myPlayerSample.setPosition(myWindow.getSize().x/2 , myWindow.getSize().y - myPlayerSample.getLocalBounds().height/2 - 20 );
    myPlayerCenter = sf::Vector2f( myPlayerSample.getPosition().x + myPlayerSample.getGlobalBounds().width/2 - 4 , myPlayerSample.getPosition().y + myPlayerSample.getGlobalBounds().height/2 );
    myPlayer.push_back(myPlayerSample);
        //hearts
    if( !HeartTex.loadFromFile("res/heart.png") )
    {
        throw "Heart Image Missing";
    }
    HeartSample.setTexture(HeartTex);
    HeartSample.setScale( 40 / HeartSample.getLocalBounds().width , 45/HeartSample.getLocalBounds().height );
    HeartSample.setPosition( 15 , myWindow.getSize().y - HeartSample.getGlobalBounds().height - 15 );
    for( int i = 0 ; i < HEALTH ; i++ )
    {
        Hearts.push_back(HeartSample);
        HeartSample.move( HeartSample.getGlobalBounds().width + 5 , 0 );
    }

    //projectile creation
        //player projectile
    if( !PlayerProjectileTex.loadFromFile("res/PlayerProjectile.png") )
    {
        throw "PlayerProjectile Image Missing";
    }
    ShootTimer = 0;
    PlayerProjectileSample.setTexture(PlayerProjectileTex);
    PlayerProjectileSample.setScale( 20 / PlayerProjectileSample.getLocalBounds().width , 45/PlayerProjectileSample.getLocalBounds().height );
        //enemy projectile
    if( !eggProjectileTex.loadFromFile("res/egg.png") )
    {
        throw "eggProjectile Image Missing";
    }
    eggProjectileSample.setTexture(eggProjectileTex);
    eggTimer = 0;


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
}