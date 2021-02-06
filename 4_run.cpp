#include "2_Game.hpp"

//main game loop

void Game::run()
{   
    srand(time(NULL));
    while(myWindow.isOpen())
    {
        //deltaTime for animation
        //deltaTime = clockDeltaTime.restart().asSeconds();
        processEvents();
        update();
        render();
    }        
}