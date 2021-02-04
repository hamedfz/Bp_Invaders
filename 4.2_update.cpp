#include "2_Game.hpp"

void Game::update()
{
//myPlayer movements
    if( (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && myPlayer.getPosition().x > 0) ||
     (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && myPlayer.getPosition().x > 0) )
    {
        myPlayer.move(-3.f,0.f);
    }

    if( (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && myPlayer.getPosition().x + myPlayer.getGlobalBounds().width < myWindow.getSize().x) || 
    (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && myPlayer.getPosition().x + myPlayer.getGlobalBounds().width < myWindow.getSize().x) )
    {
        myPlayer.move(3.f,0.f);
    }

    myPlayerCenter = sf::Vector2f( myPlayer.getPosition().x + myPlayer.getGlobalBounds().width/2 - 4 , myPlayer.getPosition().y + myPlayer.getGlobalBounds().height/2 );

//shooting
    if(shootTimer < 5 )
        shootTimer++;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer >=5 )
    {
        PlayerProjectileSample.setPosition(myPlayerCenter);
        PlayerProjectiles.push_back(PlayerProjectileSample);
        shootTimer = 0;
    }

    for( int i = 0 ; i < PlayerProjectiles.size() ; i++)
    {
        PlayerProjectiles[i].move(0.f,-7.f);

        if( PlayerProjectiles[i].getPosition().y + PlayerProjectiles[i].getGlobalBounds().height < 0 )
            PlayerProjectiles.erase( PlayerProjectiles.begin()+i );
    }

//enemies movements
    if( Direction == "Left" )
    {
        //0
        for( int i = 0 ; i < myEnemies_0_.size() ; i++)
        {
            myEnemies_0_[i].move(-1.f,0.f);
        }
        //1
        for( int i = 0 ; i < myEnemies_1_.size() ; i++)
        {
            myEnemies_1_[i].move(-1.f,0.f);
        }
        //2
        for( int i = 0 ; i < myEnemies_2_.size() ; i++)
        {
            myEnemies_2_[i].move(-1.f,0.f);
        }
        //3
        for( int i = 0 ; i < myEnemies_3_.size() ; i++)
        {
            myEnemies_3_[i].move(-1.f,0.f);
        }
        //4
        for( int i = 0 ; i < myEnemies_4_.size() ; i++)
        {
            myEnemies_4_[i].move(-1.f,0.f);
        }
    }
    else
    {
        //0
        for( int i = 0 ; i < myEnemies_0_.size() ; i++)
        {
            myEnemies_0_[i].move(1.f,0.f);
        }
        //1
        for( int i = 0 ; i < myEnemies_1_.size() ; i++)
        {
            myEnemies_1_[i].move(1.f,0.f);
        }
        //2
        for( int i = 0 ; i < myEnemies_2_.size() ; i++)
        {
            myEnemies_2_[i].move(1.f,0.f);
        }
        //3
        for( int i = 0 ; i < myEnemies_3_.size() ; i++)
        {
            myEnemies_3_[i].move(1.f,0.f);
        }
        //4
        for( int i = 0 ; i < myEnemies_4_.size() ; i++)
        {
            myEnemies_4_[i].move(1.f,0.f);
        }
    }
                    //direction change
    for( int i = 0 ; i < myEnemies_0_.size() ; i++ )
    {
        //0
        if( myEnemies_0_[i].getPosition().x < 0 )
        {
            Direction = "Right";
            break;
        }
        else if( myEnemies_0_[i].getPosition().x + myEnemy.getGlobalBounds().width > myWindow.getSize().x )
        {
            Direction = "Left";
            break;
        }
        //1
        if( myEnemies_1_[i].getPosition().x < 0 )
        {
            Direction = "Right";
            break;
        }
        else if( myEnemies_1_[i].getPosition().x + myEnemy.getGlobalBounds().width > myWindow.getSize().x )
        {
            Direction = "Left";
            break;
        }
        //2
        if( myEnemies_2_[i].getPosition().x < 0 )
        {
            Direction = "Right";
            break;
        }
        else if( myEnemies_2_[i].getPosition().x + myEnemy.getGlobalBounds().width > myWindow.getSize().x )
        {
            Direction = "Left";
            break;
        }
        //3
        if( myEnemies_3_[i].getPosition().x < 0 )
        {
            Direction = "Right";
            break;
        }
        else if( myEnemies_3_[i].getPosition().x + myEnemy.getGlobalBounds().width > myWindow.getSize().x )
        {
            Direction = "Left";
            break;
        }
        //4
        if( myEnemies_4_[i].getPosition().x < 0 )
        {
            Direction = "Right";
            break;
        }
        else if( myEnemies_4_[i].getPosition().x + myEnemy.getGlobalBounds().width > myWindow.getSize().x )
        {
            Direction = "Left";
            break;
        }
    }

    if( myEnemies_0_.size() + myEnemies_1_.size() + myEnemies_2_.size() + myEnemies_3_.size() + myEnemies_4_.size() == 0 )
    {
        win = true;
    }

//collision
        //collision vs playerprojectiles and enemies
    for( int k = 0 ; k < PlayerProjectiles.size() ; k++ )
    {
        //0
        for( int i = 0 ; i < myEnemies_0_.size() ; i++ )
        {
            if( PlayerProjectiles[k].getGlobalBounds().intersects( myEnemies_0_[i].getGlobalBounds() ) )
            {
                PlayerProjectiles.erase( PlayerProjectiles.begin()+k );
                myEnemies_0_.erase( myEnemies_0_.begin()+i );
            }
        }
        //1
        for( int i = 0 ; i < myEnemies_1_.size() ; i++ )
        {
            if( PlayerProjectiles[k].getGlobalBounds().intersects( myEnemies_1_[i].getGlobalBounds() ) )
            {
                PlayerProjectiles.erase( PlayerProjectiles.begin()+k );
                myEnemies_1_.erase( myEnemies_1_.begin()+i );
            }
        }
        //2
        for( int i = 0 ; i < myEnemies_2_.size() ; i++ )
        {
            if( PlayerProjectiles[k].getGlobalBounds().intersects( myEnemies_2_[i].getGlobalBounds() ) )
            {
                PlayerProjectiles.erase( PlayerProjectiles.begin()+k );
                myEnemies_2_.erase( myEnemies_2_.begin()+i );
            }
        }
        //3
        for( int i = 0 ; i < myEnemies_3_.size() ; i++ )
        {
            if( PlayerProjectiles[k].getGlobalBounds().intersects( myEnemies_3_[i].getGlobalBounds() ) )
            {
                PlayerProjectiles.erase( PlayerProjectiles.begin()+k );
                myEnemies_3_.erase( myEnemies_3_.begin()+i );
            }
        }
        //4
        for( int i = 0 ; i < myEnemies_4_.size() ; i++ )
        {
            if( PlayerProjectiles[k].getGlobalBounds().intersects( myEnemies_4_[i].getGlobalBounds() ) )
            {
                PlayerProjectiles.erase( PlayerProjectiles.begin()+k );
                myEnemies_4_.erase( myEnemies_4_.begin()+i );
            }
        }
    }
            //collision vs enemy projectiles and player
    
}
