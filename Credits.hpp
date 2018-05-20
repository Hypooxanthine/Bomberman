#ifndef HEADER_CREDITS
#define HEADER_CREDITS

#include <iostream>
#include <string>

#include "Button.hpp"

#include "SFML/Graphics.hpp"

class Credits
{
    public:
        Credits(sf::Sprite &background);
        ~Credits();
        std::string Open(sf::RenderWindow &app);

    protected:
        Button *myExitButton;
        sf::Sprite myBackgroundSprite;
};

#endif
