#include "2_Game.hpp"

void Game::render() 
{
//clear last frame
    myWindow.clear();

//playing state
    switch(state)
    {
        case MainMenu:
            break;

        case Playing:
            //draw background
                myWindow.draw(myBackground);

            //draw projectiles
                for( int i = 0 ; i < PlayerProjectiles.size() ; i++ )
                {
                    myWindow.draw(PlayerProjectiles[i]);
                }
            //draw eggs
                for( int i = 0 ; i < eggProjectiles.size() ; i++ )
                {
                    myWindow.draw(eggProjectiles[i]);
                }
            //draw enemies
                for( int i = 0 ; i < myEnemies.size() ; i++ )
                {
                    myWindow.draw(myEnemies[i]);
                }
            //draw player
                myWindow.draw(myPlayer);
                //hearts
                for(int i = 0 ; i < Hearts.size() ; i++ )
                {
                    myWindow.draw(Hearts[i]);
                }
            break;

        case Win:
            text.setString("You Win!");
            myWindow.draw(myBackground);
            myWindow.draw(text);
            break;

        case Lose:
            myWindow.draw(myBackground);
            text.setString("Game Over!");
            myWindow.draw(text);
            break;

        case Quit:
            break;
    }
//display
    myWindow.display();
}