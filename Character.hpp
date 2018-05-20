#ifndef HEADER_CHARACTER
#define HEADER_CHARACTER

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

enum{UP, DOWN, LEFT, RIGHT};
enum{STATIC1, LEFTSTEP, STATIC2, RIGHTSTEP};

class Character
{
    public:
        Character(sf::Texture& spriteSheet, sf::Vector2f spawnPoint, sf::Vector2f characterSize,
                  float speed, int nbAnimSteps, sf::Vector2f origin, std::string name, int health = 3);
        ~Character();

        void ManageMoving();
        void ChangeSpeed(float amount, std::string mode = "OFFSET");
        void ManageAnimation();

        void ManageBombs();
        void ChangeMaxBombs(int amount, std::string mode = "OFFSET");

        void RefreshTextureRect();
        void Respawn();
        void Move(sf::Vector2f offset);

        void setPosition(sf::Vector2f pos);

        sf::Sprite getSprite();
        float getSpeed();
        int getHealth();

    protected:
        sf::RenderWindow m_app;

        //Attributs relatifs au sprite
        sf::Texture m_spriteSheet;
        sf::Sprite m_sprite;
        sf::Vector2f m_size;
        sf::Vector2f m_originOnSheet;

        //Propriétés du personnage
        sf::Vector2f m_spawnPoint;
        float m_speed;
        std::string m_name;
        int m_health;
        int m_maxBombs, m_currentBombs;
        sf::Clock m_timerBomb;

        //Gestion de l'animation
        sf::Clock m_timer;
        int m_animState;
        int m_currentSide;
        int m_nbAnimSteps;
        int m_msPerFrame;
};

#endif
