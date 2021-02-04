#include "2_Game.hpp"
#include "1_Info.hpp"
#include <iostream>

Game::Game() 
{
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
    text.setString("You Win!");
    text.setFont(font);
    text.setFillColor( sf::Color::Magenta);
    text.setCharacterSize(50);
    text.setPosition(myWindow.getSize().x/2 - 100 , myWindow.getSize().y/2 - 50 );



    //myPlayer creation
    if( !myPlayerTex.loadFromFile("res/myPlayer.png") )
    {
        throw "myPlayer Image Missing";
    }
    myPlayer.setTexture(myPlayerTex);
    myPlayer.setScale(MYPLAYER_WIDTH/myPlayer.getLocalBounds().width , MYPLAYER_HEIGHT/myPlayer.getLocalBounds().height);
    myPlayer.setPosition(myWindow.getSize().x/2 , myWindow.getSize().y - myPlayer.getLocalBounds().height/2 );
    myPlayerCenter = sf::Vector2f( myPlayer.getPosition().x + myPlayer.getGlobalBounds().width/2 - 4 , myPlayer.getPosition().y + myPlayer.getGlobalBounds().height/2 );
    shootTimer = 0;



    //projectile creation
    if( !PlayerProjectileTex.loadFromFile("res/PlayerProjectile.png") )
    {
        throw "PlayerProjectile Image Missing";
    }
    PlayerProjectileSample.setTexture(PlayerProjectileTex);

    

    //enemy creation
    if(!myEnemyTex.loadFromFile("res/ChickenEnemy.png"))
    {
        throw "ChickenEnemy Image Missing";
    }
    myEnemy.setTexture(myEnemyTex);
    myEnemy.setScale(60/myEnemy.getLocalBounds().width , 70/myEnemy.getLocalBounds().height);
    myEnemy.setPosition(myWindow.getSize().x/2 - myEnemy.getGlobalBounds().width/2 , myWindow.getSize().y/2 - myEnemy.getGlobalBounds().height/2);
    //0
    for( int i = 0 ; i < 7 ; i++ )
    {
        myEnemies_0_.push_back(myEnemy);
        myEnemies_0_[i].move( (i-2)*(myEnemy.getGlobalBounds().width + 50 ) , 0 );
    }
    //1
    myEnemy.move(0,-myEnemy.getGlobalBounds().height-10);
    for( int i = 0 ; i < 7 ; i++ )
    {
        myEnemies_1_.push_back(myEnemy);
        myEnemies_1_[i].move( (i-2)*(myEnemy.getGlobalBounds().width + 50 ) , 0 );
    }
    //2
    myEnemy.move(0,-myEnemy.getGlobalBounds().height-10);
    for( int i = 0 ; i < 7 ; i++ )
    {
        myEnemies_2_.push_back(myEnemy);
        myEnemies_2_[i].move( (i-2)*(myEnemy.getGlobalBounds().width + 50 ) , 0 );
    }
    //3
    myEnemy.move(0,-myEnemy.getGlobalBounds().height-10);
    for( int i = 0 ; i < 7 ; i++ )
    {
        myEnemies_3_.push_back(myEnemy);
        myEnemies_3_[i].move( (i-2)*(myEnemy.getGlobalBounds().width + 50 ) , 0 );
    }
    //4
    myEnemy.move(0,-myEnemy.getGlobalBounds().height-10);
    for( int i = 0 ; i < 7 ; i++ )
    {
        myEnemies_4_.push_back(myEnemy);
        myEnemies_4_[i].move( (i-2)*(myEnemy.getGlobalBounds().width + 50 ) , 0 );
    }
}