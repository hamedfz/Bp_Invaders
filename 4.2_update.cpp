#include "2_Game.hpp"

void Game::update()
{

    switch( state )
    {
        case MainMenu:
            break;
        case Playing:
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
        if( ShootTimer < 40 )
        {
            ShootTimer++;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && ShootTimer >= 40 )
        {
            ShootTimer = 0;
            ShootSound.play();
            ProjectileLimit--;
            PlayerProjectileSample.setPosition(myPlayerCenter.x-5,myPlayerCenter.y-50);
            PlayerProjectiles.push_back(PlayerProjectileSample);
            ProjectileLimitText.setString(std::to_string(ProjectileLimit));
        }
        //projectile move and delete
        for( int i = 0 ; i < PlayerProjectiles.size() ; i++)
        {
            PlayerProjectiles[i].move(0.f,-7.f);
            if( PlayerProjectiles[i].getPosition().y + PlayerProjectiles[i].getGlobalBounds().height < 0 )
            {    
                PlayerProjectiles.erase( PlayerProjectiles.begin()+i );
            }
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
    
    //gifts
        if( giftTimer > 2000 )
        {
            giftTimer = 0;
            int random_x = rand()%((int)(myWindow.getSize().x-giftSample.getGlobalBounds().width));
            giftSample.setPosition(random_x,0);
            gifts.push_back(giftSample);
        }
        else
        {
            giftTimer++;
        }
        //gift move and delete
        for( int i = 0 ; i < gifts.size() ; i++ )
        {
            gifts[i].move(0.f,+1.f);
            if( gifts[i].getPosition().y > myWindow.getSize().y )
            {
                gifts.erase( gifts.begin()+i );
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
                    ChickenHitSound.play();
                    myEnemies.erase( myEnemies.begin()+i );
                }
            }
        }
                //collision vs enemy projectiles and player
        for( int k = 0 ; k < eggProjectiles.size() ; k++ )
        {
            if( eggProjectiles[k].getGlobalBounds().intersects( myPlayer.getGlobalBounds() ) )
            {
                eggShipSound.play();
                Health--;
                HealthText.setString(std::to_string(Health));
                eggProjectiles.erase( eggProjectiles.begin()+k );
            }
        }
            //gifts collision
        for( int i = 0 ; i < gifts.size() ; i++ )
        {
            if( gifts[i].getGlobalBounds().intersects(myPlayer.getGlobalBounds()) )
            {
                rewardSound.play();
                int random = rand()%3 ;
                if( random == 0 )
                {
                    if( Health < 3 )
                    {
                        Health++;
                        HealthText.setString(std::to_string(Health));
                    }
                }
                else
                {
                    ProjectileLimit += 5 ;
                    ProjectileLimitText.setString(std::to_string(ProjectileLimit));
                }
                gifts.erase(gifts.begin()+i);
            }
        }
        //state changes
        if( myEnemies.size() == 0 && !stateSet )
        {
            state = Win;
            stateSet = true;
        }
        else if( Health == 0 && !stateSet )
        {
            state = Lose;
            explosionSound.play();
            messageText.setString("Game Over");
            stateSet = true;
        }
        else if( ProjectileLimit == 0 && !stateSet )
        {
            state = Lose;
            explosionSound.play();
            messageText.setString("Out of ammo");
            stateSet = true;
        }
        break; //end case of playing

        case Win:
            messageText.setString("You Win");
            break;
        
        case Lose:
            
            break;
        
        case Pause:
            break;
    }
}
