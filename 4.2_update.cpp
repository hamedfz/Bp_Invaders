#include "2_Game.hpp"

void Game::update()
{
//myPlayer movements
    if( (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && myPlayer[0].getPosition().x > 0) ||
     (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && myPlayer[0].getPosition().x > 0) )
    {
        myPlayer[0].move(-3.f,0.f);
    }

    if( (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && myPlayer[0].getPosition().x + myPlayer[0].getGlobalBounds().width < myWindow.getSize().x) || 
    (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && myPlayer[0].getPosition().x + myPlayer[0].getGlobalBounds().width < myWindow.getSize().x) )
    {
        myPlayer[0].move(3.f,0.f);
    }

    myPlayerCenter = sf::Vector2f( myPlayer[0].getPosition().x + myPlayer[0].getGlobalBounds().width/2 - 4 , myPlayer[0].getPosition().y + myPlayer[0].getGlobalBounds().height/2 );

//shooting
    if( ShootTimer < 40 )
    {
        ShootTimer++;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && ShootTimer >= 40 )
    {
        ShootTimer = 0;
        PlayerProjectileSample.setPosition(myPlayerCenter.x-5,myPlayerCenter.y-50);
        PlayerProjectiles.push_back(PlayerProjectileSample);
    }
    //projectile move and delete
    for( int i = 0 ; i < PlayerProjectiles.size() ; i++)
    {
        PlayerProjectiles[i].move(0.f,-7.f);
        if( PlayerProjectiles[i].getPosition().y + PlayerProjectiles[i].getGlobalBounds().height < 0 )
            PlayerProjectiles.erase( PlayerProjectiles.begin()+i );
    }

//egg projectiles
    if( eggTimer > 390 )
    {
        eggTimer = 0;
        int random = rand()%myEnemies.size();
        eggProjectileSample.setPosition( myEnemies[random].getPosition().x + myEnemies[random].getGlobalBounds().width/2
         , myEnemies[random].getPosition().y + myEnemies[random].getGlobalBounds().height );
        eggProjectiles.push_back(eggProjectileSample);
    }
    else
    {
        eggTimer++; 
    }
    //egg move and delete
    for( int i = 0 ; i < eggProjectiles.size() ; i++ )
    {
        eggProjectiles[i].move(0.f,+1.f);
        if( eggProjectiles[i].getPosition().y > myWindow.getSize().y )
        {
            eggProjectiles.erase( eggProjectiles.begin()+i );
        }
    }

//enemies movements
    if( Direction == "Left" )
    {
        for( int i = 0 ; i < myEnemies.size() ; i++)
        {
            myEnemies[i].move(-1.f,0.f);
        }
    }
    else
    {
        for( int i = 0 ; i < myEnemies.size() ; i++)
        {
            myEnemies[i].move(1.f,0.f);
        }
    }
                    //direction change
    for( int i = 0 ; i < myEnemies.size() ; i++ )
    {
        if( myEnemies[i].getPosition().x < 0 )
        {
            Direction = "Right";
            break;
        }
        else if( myEnemies[i].getPosition().x + myEnemy.getGlobalBounds().width > myWindow.getSize().x )
        {
            Direction = "Left";
            break;
        }
    }

//collision
        //collision vs playerprojectiles and enemies
    for( int k = 0 ; k < PlayerProjectiles.size() ; k++ )
    {
        for( int i = 0 ; i < myEnemies.size() ; i++ )
        {
            if( PlayerProjectiles[k].getGlobalBounds().intersects( myEnemies[i].getGlobalBounds() ) )
            {
                PlayerProjectiles.erase( PlayerProjectiles.begin()+k );
                myEnemies.erase( myEnemies.begin()+i );
            }
        }
    }
            //collision vs enemy projectiles and player
    for( int k = 0 ; k < eggProjectiles.size() ; k++ )
    {
        if( eggProjectiles[k].getGlobalBounds().intersects( myPlayer[0].getGlobalBounds() ) )
        {
            Hearts.erase( Hearts.begin()+Hearts.size()-1 );
            eggProjectiles.erase( eggProjectiles.begin()+k );
        }
    }

//state changes
    if( myEnemies.size() == 0 )
    {
        state = Win;
    }

    if( Hearts.size() == 0 )
    {
        state = Lose;
        myPlayer.erase( myPlayer.begin() );
    }
}
