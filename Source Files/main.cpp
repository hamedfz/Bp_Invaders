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
        RenderWindow window;

        bool win = false;
        Text text;
        Font font;

        RectangleShape player;
        Vector2f playerCenter;
        int shootTimer;

        CircleShape projectile;
        std::vector<CircleShape> projectiles;
        
        RectangleShape enemy;
        std::vector<RectangleShape> enemies;
        std::string Direction = "Left";
        int enemySpawnTimer;
};

int main()
{
    Game game;
    game.run();
    return 0;
}

Game::Game() 
{

    window.create(VideoMode(860,640),"Invaders");
    window.setFramerateLimit(60);

    if( !font.loadFromFile("arial.ttf"))
    {
        //handle error
    }
    text.setString("You Win!");
    text.setFont(font);
    text.setFillColor( sf::Color::Magenta);
    text.setCharacterSize(50);
    text.setPosition(window.getSize().x/2 - 100 , window.getSize().y/2 - 50 );

    player.setSize(Vector2f(80.f,80.f));
    player.setPosition(window.getSize().x/2 - player.getSize().x/2 ,window.getSize().y - player.getSize().y );
    player.setFillColor(Color::Green);
    playerCenter = Vector2f( player.getPosition().x + player.getSize().x/2 , player.getPosition().y + player.getSize().y/2);
    shootTimer = 0;

    projectile.setFillColor(Color::Red);
    projectile.setRadius(5.f);

    enemy.setFillColor(Color::White);
    enemy.setSize(Vector2f(50.f,50.f));
    enemy.setPosition(window.getSize().x/2 - enemy.getSize().x/2 , window.getSize().y/2 - enemy.getSize().y/2 - 100 );
    enemySpawnTimer = 0;
    //create 5 enemies
    for( int i = 0 ; i < 5 ; i++ )
    {        
        enemies.push_back(enemy);
        enemies[i].move( (i-2)*(enemy.getSize().x + 50) , 0);
    }
}

void Game::run()
{
    //srand(time(NULL));
    while(window.isOpen())
    {
        processEvents();
        update();
        render();
    }        
}

void Game::processEvents()
{
    Event event;
    while(window.pollEvent(event)) 
    {
        if (event.type == Event::Closed) 
        {
            window.close();
        }
        else if( event.KeyPressed && event.key.code == Keyboard::Escape )
        {
            window.close();
        }
    }
}

void Game::update()
{
    //player movements
    if( Keyboard::isKeyPressed(Keyboard::A) && player.getPosition().x > 0 )
    {
        player.move(-3.f,0.f);
    }

    if( Keyboard::isKeyPressed(Keyboard::D) && player.getPosition().x + player.getSize().x < window.getSize().x )
    {
        player.move(3.f,0.f);
    }

    if( Keyboard::isKeyPressed(Keyboard::W) && player.getPosition().y > 0 )
    {
        player.move(0.f,-3.f);
    }

    if( Keyboard::isKeyPressed(Keyboard::S) && player.getPosition().y + player.getSize().y < window.getSize().y  )
    {
        player.move(0.f,3.f);
    }

    playerCenter = Vector2f( player.getPosition().x + player.getSize().x/2 , player.getPosition().y + player.getSize().y/2);

    //shooting
    if(shootTimer < 5 )
        shootTimer++;

    if(Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >=5 )
    {
        projectile.setPosition(playerCenter);
        projectiles.push_back(projectile);
        shootTimer = 0;
    }

    for( int i = 0 ; i < projectiles.size() ; i++)
    {
        projectiles[i].move(0.f,-10.f);

        if( projectiles[i].getPosition().y < 0 )
            projectiles.erase( projectiles.begin()+i );

    }

    //enemies movements
    //if( enemySpawnTimer < 60 )
    //    enemySpawnTimer++;
    //else
    //{
    //    enemy.setPosition( rand()%(int)(window.getSize().x - enemy.getSize().x) , 0.f );
    //    if( enemies.size() < 8 )
    //        enemies.push_back(enemy);
    //}
    if( Direction == "Left" )
    {
        for( int i = 0 ; i < enemies.size() ; i++)
        {
                enemies[i].move(-1.f,0.f);
        }
    }
    else
    {
        for( int i = 0 ; i < enemies.size() ; i++)
        {
                enemies[i].move(1.f,0.f);
        }
    }
    for( int i = 0 ; i < enemies.size() ; i++ )
    {
        if( enemies[i].getPosition().x < 0 )
        {
            Direction = "Right";
        }
        else if(enemies[i].getPosition().x + enemy.getSize().x > window.getSize().x)
        {
            Direction = "Left";
        }
    }

    if( enemies.size() == 0 )
    {
        win = true;
    }

    //collision
    for( int i = 0 ; i < projectiles.size() ; i++ )
    {
        for( int j = 0 ; j < enemies.size() ; j++ )
        {
            if(projectiles[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
            {
                projectiles.erase( projectiles.begin()+i );
                enemies.erase( enemies.begin()+j );
                break;
            }
        }
    }
}

void Game::render() 
{
    window.clear(Color::Black);

    if( win == false )
    {
        for( int i = 0 ; i < enemies.size() ; i++ )
        {
            window.draw(enemies[i]);
        }
        for( int i = 0 ; i < projectiles.size() ; i++ )
        {
            window.draw(projectiles[i]);
        }
        window.draw(player);
    }
    else
    {
        window.draw(text);
    }   

    window.display();
}