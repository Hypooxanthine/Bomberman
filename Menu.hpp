#ifndef HEADER_MENU
#define HEADER_MENU

#include <iostream>
#include <string>

#include "Button.hpp"

#include "SFML/Graphics.hpp"

class Menu
{
    public:
        Menu(sf::Sprite &background);
        ~Menu();
        std::string Open(sf::RenderWindow &app, bool reCreate);

    protected:
        void MouseManager(sf::RenderWindow &app);

        Button *myPlayButton, *myOptionsButton, *myCreditsButton, *myExitButton;
        sf::Sprite myBackgroundSprite;
};

#endif
