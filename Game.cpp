#include "Game.hpp"
#include "Maps.hpp"

using namespace std;

Game::Game()
{
    if(!m_spriteSheetImage.loadFromFile("Ressources/spritesheet.PNG"))
        cerr << endl << "Erreur lors du chargement de la feuille de sprites." << endl;
    else
    {
        m_spriteSheetImage.createMaskFromColor(sf::Color::White);
        m_spriteSheetTexture.loadFromImage(m_spriteSheetImage);
        m_spriteSheetTexture.setSmooth(true);


        //Tiles
        m_tileBlockSprite.setTexture(m_spriteSheetTexture);
        m_tileBlockSprite.setTextureRect(sf::IntRect(TILE_SIZE * BLOCK, TILES_ORIGIN_Y, TILE_SIZE, TILE_SIZE));

        m_tileGrassSprite.setTexture(m_spriteSheetTexture);
        m_tileGrassSprite.setTextureRect(sf::IntRect(TILE_SIZE * GRASS, TILES_ORIGIN_Y, TILE_SIZE, TILE_SIZE));

        m_tileSpawnSprite.setTexture(m_spriteSheetTexture);
        m_tileSpawnSprite.setTextureRect(sf::IntRect(TILE_SIZE * SPAWN, TILES_ORIGIN_Y, TILE_SIZE, TILE_SIZE));

        m_dirtSprite.setTexture(m_spriteSheetTexture);
        m_dirtSprite.setTextureRect(sf::IntRect(TILE_SIZE * DIRT, TILES_ORIGIN_Y, TILE_SIZE, TILE_SIZE));


        //Items
        m_bombSprite.setTexture(m_spriteSheetTexture);
        m_bombSprite.setTextureRect(sf::IntRect(ITEMS_SIZE * 0, ITEMS_ORIGIN_Y, ITEMS_SIZE, ITEMS_SIZE));


        //Icons
        m_heartSprite.setTexture(m_spriteSheetTexture);
        m_heartSprite.setTextureRect(sf::IntRect(ICONS_SIZE * HEART, ICONS_ORIGIN_Y, ICONS_SIZE, ICONS_SIZE));
    }

    m_character = new Character(m_spriteSheetTexture, BOMBERMAN_SPAWN, BOMBERMAN_SIZE, BOMBERMAN_SPEED, NB_ANIMATION_STEPS, BOMBERMAN_ORIGIN, "Player 1", 5);
}

std::string Game::Open(sf::RenderWindow &app)
{
    cout << "Ouverture de la fenetre de jeu." << endl << endl;
    cout << "----------BOMBERMAN----------" << endl;
    cout << "A : Add 0.5 to Player 1 speed." << endl;
    cout << "Z : Remove 0.5 top Player 1 speed." << endl;
    cout << "R : Respawn Player 1." << endl << endl;

    ResetItems();
    ResetBombs();

    app.close();
    app.create(sf::VideoMode(TILE_SIZE * BOARD_DIMENSIONS.x + 1, TILE_SIZE * BOARD_DIMENSIONS.y + HEADER_HEIGHT, 32), "Bomberman", sf::Style::Resize|sf::Style::Titlebar|sf::Style::Close);
    app.setFramerateLimit(60);

    InitializeBoard();
    InitializeDirt(DIRT_PERCENTAGE);

    while(app.isOpen())
    {
        sf::Event event;

        while(app.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed :
                    return "EXIT";
                case sf::Event::KeyPressed :
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Escape :
                            return "OPEN_MENU";
                            break;
                        case sf::Keyboard::A :
                            m_character->ChangeSpeed(0.5);
                            break;
                        case sf::Keyboard::Z :
                            m_character->ChangeSpeed(-0.5);
                            break;
                        case sf::Keyboard::R :
                            m_character->Respawn();
                            m_character->ChangeSpeed(BOMBERMAN_SPEED, "SET");
                            break;
                        case sf::Keyboard::T :
                            m_character->Respawn();
                            m_character->ChangeSpeed(BOMBERMAN_SPEED, "SET");
                            InitializeDirt(DIRT_PERCENTAGE);
                            ResetItems();
                            ResetBombs();
                            break;
                        case sf::Keyboard::B :
                            DropBomb();
                            break;
                    }
            }
        }

        m_character->ManageMoving();
        ManageCollisionBlock();
        ManageCollisionDirt();

        app.clear();
        DrawBoard(app);
        DrawDirt(app);
        DrawBombs(app);
        DrawItems(app);
        DrawIcons(app);
        app.draw(m_character->getSprite());
        app.draw(m_tileBlockSprite);
        app.display();
    }
}

void Game::DrawBoard(sf::RenderWindow &app)
{
    int x = 0, y = 0;

    for(y ; y < BOARD_DIMENSIONS.y ; y++)
    {
        x = 0;

        for(x ; x < BOARD_DIMENSIONS.x ; x++)
        {
            switch(BOARD[y][x])
            {
                case BLOCK :
                    m_tileBlockSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE + HEADER_HEIGHT);
                    app.draw(m_tileBlockSprite);
                    break;
                case GRASS :
                    m_tileGrassSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE + HEADER_HEIGHT);
                    app.draw(m_tileGrassSprite);
                    break;
                case SPAWN :
                    m_tileSpawnSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE + HEADER_HEIGHT);
                    app.draw(m_tileSpawnSprite);
                    break;
            }
        }
    }
}

void Game::DrawDirt(sf::RenderWindow &app)
{
    int x = 0, y = 0;

    for(y ; y < BOARD_DIMENSIONS.y ; y++)
    {
        x = 0;

        for(x ; x < BOARD_DIMENSIONS.x ; x++)
        {
            if(m_board[y][x] == DIRT)
            {
                m_dirtSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE + HEADER_HEIGHT);
                app.draw(m_dirtSprite);
            }
        }
    }
}

void Game::DrawBombs(sf::RenderWindow &app)
{
    int x = 0, y = 0;

    for(y ; y < BOARD_DIMENSIONS.y ; y++)
    {
        x = 0;

        for(x ; x < BOARD_DIMENSIONS.x ; x++)
        {
            if(m_bombs[y][x])
            {
                m_bombSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE + HEADER_HEIGHT);
                app.draw(m_bombSprite);
            }
        }
    }
}

void Game::DrawItems(sf::RenderWindow &app)
{
    int x = 0, y = 0;

    for(y ; y < BOARD_DIMENSIONS.y ; y++)
    {
        x = 0;

        for(x ; x < BOARD_DIMENSIONS.x ; x++)
        {
        }
    }
}

void Game::DrawIcons(sf::RenderWindow &app)
{
    m_heartSprite.setPosition(10, 30 + ICONS_SIZE);

    for(int i = 0 ; i < m_character->getHealth() ; i++)
    {
        app.draw(m_heartSprite);
        m_heartSprite.move(10 + ICONS_SIZE, 0);
    }
}

void Game::ManageCollisionBlock()
{
    //Collisions supérieures
    if( BOARD[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_DISTANCE_TO_FEET_TOP - HEADER_HEIGHT) / TILE_SIZE))]
            [int(floor((m_character->getSprite().getPosition().x) / TILE_SIZE))] == BLOCK  && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||
        BOARD[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_DISTANCE_TO_FEET_TOP - HEADER_HEIGHT) / TILE_SIZE))]
             [int(floor((m_character->getSprite().getPosition().x + BOMBERMAN_SIZE.x - BOMBERMAN_DISTANCE_TO_FEET_RIGHT) / TILE_SIZE))] == BLOCK  && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_character->Move(sf::Vector2f(0, m_character->getSpeed()));
    }

    //Collisions inférieures
    if( BOARD[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_SIZE.y - HEADER_HEIGHT) / TILE_SIZE))]
            [int(floor((m_character->getSprite().getPosition().x) / TILE_SIZE))] == BLOCK  && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
        BOARD[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_SIZE.y - HEADER_HEIGHT) / TILE_SIZE))]
             [int(floor((m_character->getSprite().getPosition().x + BOMBERMAN_SIZE.x - BOMBERMAN_DISTANCE_TO_FEET_RIGHT) / TILE_SIZE))] == BLOCK  && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_character->Move(sf::Vector2f(0, -m_character->getSpeed()));
    }

    //Collisions gauches
    if( BOARD[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_DISTANCE_TO_FEET_TOP - HEADER_HEIGHT) / TILE_SIZE))]
            [int(floor(m_character->getSprite().getPosition().x / TILE_SIZE))] == BLOCK  && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        BOARD[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_SIZE.y - HEADER_HEIGHT) / TILE_SIZE))]
            [int(floor((m_character->getSprite().getPosition().x) / TILE_SIZE))] == BLOCK  && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_character->Move(sf::Vector2f(m_character->getSpeed(), 0));
    }

    //Collisions droites
    if( BOARD[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_DISTANCE_TO_FEET_TOP - HEADER_HEIGHT) / TILE_SIZE))]
             [int(floor((m_character->getSprite().getPosition().x + BOMBERMAN_SIZE.x - BOMBERMAN_DISTANCE_TO_FEET_RIGHT) / TILE_SIZE))] == BLOCK  && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        BOARD[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_SIZE.y - HEADER_HEIGHT) / TILE_SIZE))]
             [int(floor((m_character->getSprite().getPosition().x + BOMBERMAN_SIZE.x - BOMBERMAN_DISTANCE_TO_FEET_RIGHT) / TILE_SIZE))] == BLOCK  && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_character->Move(sf::Vector2f(-m_character->getSpeed(), 0));
    }
}

void Game::ManageCollisionDirt()
{
    //Collisions supérieures
    if( m_board[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_DISTANCE_TO_FEET_TOP - HEADER_HEIGHT) / TILE_SIZE))]
            [int(floor((m_character->getSprite().getPosition().x) / TILE_SIZE))] == DIRT  && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||
        m_board[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_DISTANCE_TO_FEET_TOP - HEADER_HEIGHT) / TILE_SIZE))]
             [int(floor((m_character->getSprite().getPosition().x + BOMBERMAN_SIZE.x - BOMBERMAN_DISTANCE_TO_FEET_RIGHT) / TILE_SIZE))] == DIRT && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_character->Move(sf::Vector2f(0, m_character->getSpeed()));
    }

    //Collisions inférieures
    if( m_board[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_SIZE.y - HEADER_HEIGHT) / TILE_SIZE))]
            [int(floor((m_character->getSprite().getPosition().x) / TILE_SIZE))] == DIRT  && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
        m_board[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_SIZE.y - HEADER_HEIGHT) / TILE_SIZE))]
             [int(floor((m_character->getSprite().getPosition().x + BOMBERMAN_SIZE.x - BOMBERMAN_DISTANCE_TO_FEET_RIGHT) / TILE_SIZE))] == DIRT  && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_character->Move(sf::Vector2f(0, -m_character->getSpeed()));
    }

    //Collisions gauches
    if( m_board[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_DISTANCE_TO_FEET_TOP - HEADER_HEIGHT) / TILE_SIZE))]
            [int(floor(m_character->getSprite().getPosition().x / TILE_SIZE))] == DIRT  && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        m_board[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_SIZE.y - HEADER_HEIGHT) / TILE_SIZE))]
            [int(floor((m_character->getSprite().getPosition().x) / TILE_SIZE))] == DIRT  && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_character->Move(sf::Vector2f(m_character->getSpeed(), 0));
    }

    //Collisions droites
    if( m_board[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_DISTANCE_TO_FEET_TOP - HEADER_HEIGHT) / TILE_SIZE))]
             [int(floor((m_character->getSprite().getPosition().x + BOMBERMAN_SIZE.x - BOMBERMAN_DISTANCE_TO_FEET_RIGHT) / TILE_SIZE))] == DIRT  && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        m_board[int(floor((m_character->getSprite().getPosition().y + BOMBERMAN_SIZE.y - HEADER_HEIGHT) / TILE_SIZE))]
             [int(floor((m_character->getSprite().getPosition().x + BOMBERMAN_SIZE.x - BOMBERMAN_DISTANCE_TO_FEET_RIGHT) / TILE_SIZE))] == DIRT  && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_character->Move(sf::Vector2f(-m_character->getSpeed(), 0));
    }
}

void Game::InitializeBoard()
{
    cout << "Initialisation de la map." << endl << endl;

    int x = 0, y = 0;

    for(y ; y < BOARD_DIMENSIONS.y ; y++)
    {
        x = 0;

        for(x ; x < BOARD_DIMENSIONS.x ; x++)
        {
            m_board[y][x] = BOARD[y][x];
        }
    }
}

void Game::InitializeDirt(int percentage)
{
    cout << "Randomisation des blocs \"Dirt\"." << endl << endl;

    int x = 0, y = 0;

    for(y ; y < BOARD_DIMENSIONS.y ; y++)
    {
        x = 0;

        for(x ; x < BOARD_DIMENSIONS.x ; x++)
        {
            if(BOARD[y][x] == GRASS || BOARD[y][x] == DIRT)
            {
                if(rand() % 100 + 1 <= percentage)
                    m_board[y][x] = DIRT;
                else
                    m_board[y][x] = GRASS;
            }
        }
    }
}

void Game::ResetBombs()
{
    int x = 0, y = 0;

    for(y ; y < BOARD_DIMENSIONS.y ; y++)
    {
        x = 0;

        for(x ; x < BOARD_DIMENSIONS.x ; x++)
        {
            m_bombs[y][x] = 0;
        }
    }
}

void Game::ResetItems()
{
    int x = 0, y = 0;

    for(y ; y < BOARD_DIMENSIONS.y ; y++)
    {
        x = 0;

        for(x ; x < BOARD_DIMENSIONS.x ; x++)
        {
            m_items[y][x] = VOID;
        }
    }
}

void Game::DropBomb()
{
    m_bombs[int(floor((m_character->getSprite().getPosition().y + (BOMBERMAN_DISTANCE_TO_FEET_TOP + BOMBERMAN_SIZE.y)/2 - HEADER_HEIGHT) / TILE_SIZE))]
    [int(floor((m_character->getSprite().getPosition().x + BOMBERMAN_SIZE.x / 2) / TILE_SIZE))] = 1;
}

void Game::DropItem(int item)
{
    m_items[int(floor((m_character->getSprite().getPosition().y + (BOMBERMAN_DISTANCE_TO_FEET_TOP + BOMBERMAN_SIZE.y)/2 - HEADER_HEIGHT) / TILE_SIZE))]
    [int(floor((m_character->getSprite().getPosition().x + BOMBERMAN_SIZE.x / 2) / TILE_SIZE))] = item;

}

Game::~Game()
{
    delete m_character;
}
