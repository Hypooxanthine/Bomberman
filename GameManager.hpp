#ifndef HEADER_GAMEMANAGER
#define HEADER_GAMEMANAGER

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Menu.hpp"
#include "Options.hpp"
#include "Credits.hpp"
#include "Game.hpp"

class GameManager
{
    public:
        GameManager(std::string toDo = "OPEN_MENU");
        ~GameManager();

    protected:
        sf::RenderWindow myApp;
        Menu *myMenu;
        Game *myGame;
        Options *myOptions;
        Credits *myCredits;

        sf::Texture myBackgroundTexture, myGameBackgroundTexture;
        sf::Sprite myBackgroundSprite, myGameBackgroundSprite;

        sf::Music myMusic;
};

#endif
