#ifndef HEADER_GAME
#define HEADER_GAME

#include <iostream>
#include <string>

#include "math.h"
#include "SFML/Graphics.hpp"

#include "Character.hpp"

const int HEADER_HEIGHT = 100;

const int TILES_ORIGIN_Y = 216;
const int TILE_SIZE = 56;
enum{BLOCK, GRASS, SPAWN, DIRT};

const int ICONS_ORIGIN_Y = 272;
const int ICONS_SIZE = 25;
enum{HEART};

const int BOMB_ORIGIN_Y = 297;
const int BOMB_SIZE = 56;

const int ITEMS_ORIGIN_Y = 297;
const int ITEMS_SIZE = 56;
enum{VOID = -1, BOMB_UP = 0, HEALTH_UP = 1, SPEED_UP = 2};

const float BOMBERMAN_SPEED = 1;

const sf::Vector2f BOMBERMAN_SIZE(36, 54);
const int BOMBERMAN_DISTANCE_TO_FEET_TOP = 36, BOMBERMAN_DISTANCE_TO_FEET_RIGHT = 8;
const sf::Vector2f BOMBERMAN_ORIGIN(0, 0);
const sf::Vector2f BOMBERMAN_SPAWN(TILE_SIZE * 1.5 - BOMBERMAN_SIZE.x / 2, TILE_SIZE * 2 - BOMBERMAN_SIZE.y / 2 + HEADER_HEIGHT - BOMBERMAN_DISTANCE_TO_FEET_TOP);
const int NB_ANIMATION_STEPS = 4;

const sf::Vector2i BOARD_DIMENSIONS(17, 15);
const int DIRT_PERCENTAGE = 40;

class Game
{
    public:
        Game();
        ~Game();

        std::string Open(sf::RenderWindow &app);

    protected:
        void DrawBoard(sf::RenderWindow &app);
        void DrawIcons(sf::RenderWindow &app);
        void DrawDirt(sf::RenderWindow &app);

        void DrawBombs(sf::RenderWindow &app);
        void DrawItems(sf::RenderWindow &app);

        void ManageCollisionBlock();
        void ManageCollisionDirt();

        void InitializeBoard();
        void InitializeDirt(int percentage);

        void ResetBombs();
        void ResetItems();

        void DropBomb();
        void DropItem(int item);

        sf::Image m_spriteSheetImage;
        sf::Texture m_spriteSheetTexture;

        sf::Sprite m_tileBlockSprite, m_tileGrassSprite, m_tileSpawnSprite, m_dirtSprite;
        sf::Sprite m_bombSprite;
        sf::Sprite m_heartSprite;

        Character *m_character;

        int m_board[15][17];
        int m_items[15][17];
        int m_bombs[15][17];
};

#endif
