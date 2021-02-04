#include "2_Game.hpp"

void Game::run()
{
    while(myWindow.isOpen())
    {
        processEvents();
        update();
        render();
    }        
}