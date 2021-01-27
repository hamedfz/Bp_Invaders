#include "headers.h"
using namespace sf;

class Game
{
    public:
        Game();
        void run();
    private:
        void processEvents();
        void update();
        void render();

    private:
        RenderWindow mwindow;
        RectangleShape mPlayer;
};

int main()
{
    Game game;
    game.run();
    return 0;
}

Game::Game() 
{
    mwindow.create(VideoMode(800, 600),"Space Invaders");
    mwindow.setFramerateLimit(60);

    mPlayer.setSize(Vector2f(80.f,80.f));
    mPlayer.setPosition(mwindow.getSize().x/2,mwindow.getSize().y/2);
    mPlayer.setFillColor(Color::Red);
}

void Game::run()
{
    while(mwindow.isOpen())
    {
        processEvents();
        update();
        render();
    }        
}

void Game::processEvents()
{
    Event event;
    while(mwindow.pollEvent(event)) 
    {
        if (event.type == Event::Closed) 
        {
            mwindow.close();
        }
        else if( event.KeyPressed && event.key.code == Keyboard::Escape )
        {
            mwindow.close();
        }
    }
}

void Game::update()
{

    if( Keyboard::isKeyPressed(Keyboard::A) && mPlayer.getPosition().x > 0 )
    {
        mPlayer.move(-5.f,0.f);
    }

    if( Keyboard::isKeyPressed(Keyboard::D) && mPlayer.getPosition().x + mPlayer.getSize().x < mwindow.getSize().x )
    {
        mPlayer.move(5.f,0.f);
    }

    if( Keyboard::isKeyPressed(Keyboard::W) && mPlayer.getPosition().y > 0 )
    {
        mPlayer.move(0.f,-5.f);
    }

    if( Keyboard::isKeyPressed(Keyboard::S) && mPlayer.getPosition().y + mPlayer.getSize().y < mwindow.getSize().y  )
    {
        mPlayer.move(0.f,5.f);
    }
}

void Game::render() 
{
    mwindow.clear(Color::White);
    mwindow.draw(mPlayer);
    mwindow.display();
}