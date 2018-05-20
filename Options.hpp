#ifndef HEADER_OPTIONS
#define HEADER_OPTIONS

#include <iostream>
#include <string>

#include "Button.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Options
{
    public:
        Options(sf::Sprite &background);
        ~Options();
        std::string Open(sf::RenderWindow &app, sf::Music& music);

    protected:
        Button *myExitButton, *myVolumeButton, *myUpVolumeButton, *myDownVolumeButton;
        sf::Sprite myBackgroundSprite;

        void modifyVolume(int amount, sf::Music& music);
};

#endif
