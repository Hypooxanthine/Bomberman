#ifndef HEADER_BUTTON
#define HEADER_BUTTON

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

class Button
{
    public:
        Button(sf::Texture &spritesSheet,
               sf::IntRect releasedTextureRect, sf::IntRect hoveredTextureRect, sf::IntRect pressedTextureRect,
               sf::Vector2f position);
        void setPosition(sf::Vector2f position);
        sf::Sprite getSprite();
        void switchTexture(std::string texture);
        bool isCursorOnButton(sf::RenderWindow& app);

    protected:
        sf::Texture myTexture;
        sf::Sprite mySprite;
        sf::IntRect myReleasedTextureRect, myHoveredTextureRect, myPressedTextureRect;
};

#endif
