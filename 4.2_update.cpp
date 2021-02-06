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
        //egg move and delete and creat eggsplash
        for( int i = 0 ; i < eggProjectiles.size() ; i++ )
        {
            eggProjectiles[i].move(0.f,+1.f);
            if( eggProjectiles[i].getPosition().y + eggProjectiles[i].getGlobalBounds().height > myWindow.getSize().y )
            {
                eggSplashSample.setPosition(eggProjectiles[i].getPosition().x,eggProjectiles[i].getPosition().y-6);
                eggSplash.push_back(eggSplashSample);
                eggSplashTimer.push_back(0);
                eggDestroyedSound.play();
                eggProjectiles.erase( eggProjectiles.begin()+i );
            }
        }
    //egg splash delete
        for( int i = 0 ; i < eggSplash.size() ; i++ )
        {
            if( eggSplashTimer[i] >= 180 )
            {
                eggSplash.erase( eggSplash.begin() + i );
                eggSplashTimer.erase( eggSplashTimer.begin() + i );
            }
            else
            {
                eggSplashTimer[i]++;
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
    //meat movement
        for( int i = 0 ; i < meats.size() ; i++ )
        {
            meats[i].move(0.f,+1.5f);
            if( meats[i].getPosition().y > myWindow.getSize().y )
            {
                meats.erase( meats.begin() + i );
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
                    meatSample.setPosition( myEnemies[i].getPosition().x , myEnemies[i].getPosition().y );
                    meats.push_back(meatSample);
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
            //meat collision vs player
        for( int i = 0 ; i < meats.size() ; i++ )
        {
            if( meats[i].getGlobalBounds().intersects(myPlayer.getGlobalBounds()) )
            {
                meatSound.play();
                meats.erase( meats.begin() + i );
                ProjectileLimit++;
                ProjectileLimitText.setString(std::to_string(ProjectileLimit));
            }
        }
        //state changes
        if( myEnemies.size() == 0 && !stateSet )
        {
            state = Win;
            winSound.play();
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
        //timer update
        if( myClock.getElapsedTime().asSeconds() >= 1 )
        {
            sec++;
            if( sec > 59 )
            {
                min++;
                sec = 0;
            }
            myClock.restart().asSeconds();
            myTimerText.setString( std::to_string(min) + " : " + std::to_string(sec) );
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
