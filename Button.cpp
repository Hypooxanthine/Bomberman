#include "Button.hpp"

using namespace std;
using namespace sf;

/* On demande le path,
   la position des 3 états possibles de chaque bouton sur la feuille,
   ainsi que leur position sur la fenêtre */
Button::Button(Texture &spritesSheet,
               IntRect releasedTextureRect, IntRect hoveredTextureRect, IntRect pressedTextureRect,
               Vector2f position)
{
    myTexture = spritesSheet;
    mySprite.setTexture(myTexture);

    myReleasedTextureRect = releasedTextureRect;
    myHoveredTextureRect = hoveredTextureRect;
    myPressedTextureRect = pressedTextureRect;
    setPosition(position);
}

void Button::setPosition(Vector2f position)
{
    mySprite.setPosition(position);
}

Sprite Button::getSprite()
{
    return mySprite;
}

void Button::switchTexture(string texture)
{
    if(texture == "RELEASED")
        mySprite.setTextureRect(myReleasedTextureRect);
    else if(texture == "HOVERED")
        mySprite.setTextureRect(myHoveredTextureRect);
    else if(texture == "PRESSED")
        mySprite.setTextureRect(myPressedTextureRect);
}

bool Button::isCursorOnButton(RenderWindow& app)
{
    if(Mouse::getPosition(app).x >= mySprite.getPosition().x &&
       Mouse::getPosition(app).x <= mySprite.getPosition().x + mySprite.getTextureRect().width &&
       Mouse::getPosition(app).y >= mySprite.getPosition().y &&
       Mouse::getPosition(app).y <= mySprite.getPosition().y + mySprite.getTextureRect().height)
       return true;
    else
        return false;
}
