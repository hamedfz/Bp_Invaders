#include "2_Game.hpp"

void Game::processEvents()
{
    sf::Event event;
    while(myWindow.pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed) 
        {
            myWindow.close();
        }
        else if( event.KeyPressed && event.key.code == sf::Keyboard::Escape )
        {
            myWindow.close();
        }
    }
}