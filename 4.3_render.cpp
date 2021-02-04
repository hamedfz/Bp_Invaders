#include "2_Game.hpp"

void Game::render() 
{
//clear last frame
    myWindow.clear();

//playing state
    if( win == false )
    {
        myWindow.draw(myBackground);
    //draw enemies
        //0
        for( int i = 0 ; i < myEnemies_0_.size() ; i++ )
        {
            myWindow.draw(myEnemies_0_[i]);
        }
        //1
        for( int i = 0 ; i < myEnemies_1_.size() ; i++ )
        {
            myWindow.draw(myEnemies_1_[i]);
        }
        //2
        for( int i = 0 ; i < myEnemies_2_.size() ; i++ )
        {
            myWindow.draw(myEnemies_2_[i]);
        }
        //3
        for( int i = 0 ; i < myEnemies_3_.size() ; i++ )
        {
            myWindow.draw(myEnemies_3_[i]);
        }
        //4
        for( int i = 0 ; i < myEnemies_4_.size() ; i++ )
        {
            myWindow.draw(myEnemies_4_[i]);
        }
    //draw projectiles
        for( int i = 0 ; i < PlayerProjectiles.size() ; i++ )
        {
            myWindow.draw(PlayerProjectiles[i]);
        }
        myWindow.draw(myPlayer);
    }
//game end state
    else
    {
        myWindow.draw(myBackground);
        myWindow.draw(text);
    }
//display
    myWindow.display();
}