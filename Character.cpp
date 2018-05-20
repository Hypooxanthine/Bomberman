#include "Character.hpp"

using namespace std;

Character::Character(sf::Texture& spriteSheet, sf::Vector2f spawnPoint, sf::Vector2f characterSize,
                     float speed, int nbAnimSteps, sf::Vector2f origin, std::string name, int health)
{
    m_spriteSheet = spriteSheet;
    m_size = characterSize;
    m_nbAnimSteps = nbAnimSteps;
    m_originOnSheet = origin;
    m_spawnPoint = spawnPoint;
    m_name = name;
    m_health = health;
    m_maxBombs = 1;
    m_currentBombs = 1;

    //On assigne la feuille au sprite et on donne l'état initial du personnage
    m_sprite.setTexture(m_spriteSheet);
    RefreshTextureRect();
    Respawn();
    ChangeSpeed(speed, "SET");
}

void Character::ManageMoving()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_sprite.move(sf::Vector2f(0, -m_speed)); //Déplacement du personnage
        m_currentSide = UP; //On lui donne la bonne orientation

        ManageAnimation();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_sprite.move(sf::Vector2f(0, m_speed));
        m_currentSide = DOWN;

        ManageAnimation();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_sprite.move(sf::Vector2f(-m_speed, 0));
        m_currentSide = LEFT;

        ManageAnimation();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_sprite.move(sf::Vector2f(m_speed, 0));
        m_currentSide = RIGHT;

        ManageAnimation();
    }
    else
        m_animState = STATIC1; //Quand aucune touche directionnelle n'est appuyée, le personnage est statique

    if(m_speed == 0)
        m_animState = STATIC1;

    RefreshTextureRect(); //Il faut bien actualiser  la texture pour prendre en compte la modification du sprite
}

void Character::ManageAnimation()
{
    if(m_timer.getElapsedTime().asMilliseconds() >= m_msPerFrame && m_speed != 0) //Gestion de l'animation
        {
            m_animState++; //Si le timer a duré assez longtemps, on passe à la frame suivante de l'animation
            m_animState %= m_nbAnimSteps; //On fait attention de ne pas dépasser le nombre max de frames
            m_timer.restart(); //On redémarre le timer lors du changement de frame
        }
}

void Character::ManageBombs()
{

}

void Character::ChangeMaxBombs(int amount, std::string mode)
{
    if(mode == "SET") //Modification absolue
    {
        m_maxBombs = amount;
        cout << "m_maxBombs " << m_name << " = " << m_maxBombs << endl;
    }
    else if(mode == "OFFSET") //Modification relative
    {
        m_maxBombs += amount;
        cout << "m_maxBombs " << m_name << " = " << m_maxBombs << endl;
    }
}

void Character::ChangeSpeed(float amount, std::string mode)
{
    if(mode == "SET") //Modification absolue
    {
        m_speed = amount;
        cout << "m_speed " << m_name << " = " << m_speed << endl;
    }
    else if(mode == "OFFSET" && amount >= 0 || mode == "OFFSET" == amount < 0 && m_speed > 0) //Modification relative
    {
        m_speed += amount;
        cout << "m_speed " << m_name << " = " << m_speed << endl;
    }

    if(m_speed != 0) //On ne veut pas diviser par zéro
        m_msPerFrame = int(110 / m_speed + 110); //Formule pour faire coincider la vitesse à l'animation
    else
        m_msPerFrame = -1; //Ne pas animer un personnage immobile
    cout << "m_msPerFrame " << m_name << " = " << m_msPerFrame << endl << endl;
}

void Character::RefreshTextureRect()
{
    //On va changer le TextureRect pour qu'il corresponde aux paramètres actuels
    m_sprite.setTextureRect(sf::IntRect(m_animState * m_size.x + m_originOnSheet.x, m_currentSide * m_size.y, m_size.x, m_size.y + m_originOnSheet.y));
}

void Character::Respawn()
{
    setPosition(m_spawnPoint);
    m_animState = STATIC1;
    m_currentSide = DOWN;
    cout << "Respawning " << m_name << endl << endl;
}

void Character::Move(sf::Vector2f offset)
{
    m_sprite.move(offset);
}

void Character::setPosition(sf::Vector2f pos)
{
    m_sprite.setPosition(pos);
}

sf::Sprite Character::getSprite()
{
    return m_sprite;
}

float Character::getSpeed()
{
    return m_speed;
}

int Character::getHealth()
{
    return m_health;
}

Character::~Character()
{

}
