#include "Options.hpp"

using namespace std;
using namespace sf;

Options::Options(Sprite& background)
{
    Texture spritesSheet;
    if(!spritesSheet.loadFromFile("Ressources/Feuille_Sprites_Options.png"))
        cerr << "Erreur de chargement de la feuille de sprites." << endl;

    /* On donne la feuille de sprites,
    la position des 3 états possibles de chaque bouton sur la feuille,
    ainsi que leur position sur la fenêtre */
    myExitButton = new Button(spritesSheet,
                              IntRect(0,284,90,90), IntRect(90,284,90,90), IntRect(180,284,90,90),
                              Vector2f(900, 400));
    myVolumeButton = new Button(spritesSheet,
                                IntRect(0,180,600,104), IntRect(0,180,600,104), IntRect(0,180,600,104),
                                Vector2f(20, 40));
    myUpVolumeButton = new Button(spritesSheet,
                                  IntRect(0,0,90,90), IntRect(90,0,90,90), IntRect(180,0,90,90),
                                  Vector2f(640, 47));
    myDownVolumeButton = new Button(spritesSheet,
                                  IntRect(0,90,90,90), IntRect(90,90,90,90), IntRect(180,90,90,90),
                                  Vector2f(750, 47));

    myExitButton->switchTexture("RELEASED");
    myVolumeButton->switchTexture("RELEASED");
    myUpVolumeButton->switchTexture("RELEASED");
    myDownVolumeButton->switchTexture("RELEASED");

    myBackgroundSprite = background;
}

string Options::Open(RenderWindow &app, Music& music) //Le RenderWindow en référence permet de modifier l'app de GameManager directement
{
    cout << "Ouverture du Menu d'options." << endl << endl;

    //On assigne la taille correspondant aux options à l'appli
    app.setSize(Vector2u(myBackgroundSprite.getTextureRect().width, myBackgroundSprite.getTextureRect().height));
    app.setTitle("Tetris : Menu d'Options");

    // Boucle principale
    while (app.isOpen())
    {
        Event event;

        while (app.pollEvent(event)) //Tant qu'un event est capté...
        {
            switch(event.type)
            {
                //Si on clique sur la croix, on demande au GameManager d'arrêter le programme
                case Event::Closed :
                    return "EXIT";
                    break;

                case Event::KeyPressed : //Si on appuie sur une touche...
                    switch(event.key.code)
                    {
                        //Si on presse Echap, on demande au GameManager d'ouvrir le menu principal
                        case Keyboard::Escape :
                            return "OPEN_MENU";
                            break;
                    }
                    break;
                case Event::MouseButtonPressed :
                    if (myExitButton->isCursorOnButton(app))
                        return "OPEN_MENU";
                    else if (myUpVolumeButton->isCursorOnButton(app))
                        modifyVolume(int(+10), music);
                    else if (myDownVolumeButton->isCursorOnButton(app))
                        modifyVolume(int(-10), music);
                    break;
                case Event::MouseMoved :
                    if (myExitButton->isCursorOnButton(app))
                        myExitButton->switchTexture("HOVERED");
                    else if (myUpVolumeButton->isCursorOnButton(app))
                        myUpVolumeButton->switchTexture("HOVERED");
                    else if (myDownVolumeButton->isCursorOnButton(app))
                        myDownVolumeButton->switchTexture("HOVERED");
                    else
                    {
                        myExitButton->switchTexture("RELEASED");
                        myUpVolumeButton->switchTexture("RELEASED");
                        myDownVolumeButton->switchTexture("RELEASED");
                    }
                    break;
            }
        }

        // Affichages
        app.clear();

        //On affiche le background
        app.draw(myBackgroundSprite);
        //On affiche les boutons grâce à la méthode Button::getSprite()
        app.draw(myExitButton->getSprite());
        app.draw(myVolumeButton->getSprite());
        app.draw(myUpVolumeButton->getSprite());
        app.draw((myDownVolumeButton->getSprite()));

        app.display();
    }
}

void Options::modifyVolume(int amount, Music& music)
{
    if (music.getVolume() >= 100 - amount)
        music.setVolume(100);
    else if (music.getVolume() <= amount * -1)
        music.setVolume(0);
    else
        music.setVolume(music.getVolume() + amount);

    cout << "Le volume de la musique est maintenant de : " << music.getVolume() << "." << endl;
}

Options::~Options()
{
    delete myExitButton;
    delete myVolumeButton;
    delete myUpVolumeButton;
    delete myDownVolumeButton;
}
