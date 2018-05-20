#include "Menu.hpp"

using namespace std;
using namespace sf;

Menu::Menu(Sprite &background)
{
    Texture spritesSheet;
    if(!spritesSheet.loadFromFile("Ressources/Feuille_Sprites_Menus.png"))
        cerr << "Erreur de chargement de la feuille de sprites." << endl;

    /* On donne la feuille de sprites,
    la position des 3 états possibles de chaque bouton sur la feuille,
    ainsi que leur position sur la fenêtre */
    myPlayButton = new Button(spritesSheet,
                              IntRect(0,0,600,104), IntRect(600,0,600,104), IntRect(1200,0,600,104),
                              Vector2f(200, 47));
    myOptionsButton = new Button(spritesSheet,
                                 IntRect(0,104,600,104), IntRect(600,104,600,104), IntRect(1200,104,600,104),
                                 Vector2f(200, 198));
    myCreditsButton = new Button(spritesSheet,
                                 IntRect(0,208,600,104), IntRect(600,208,600,104), IntRect(1200,208,600,104),
                                 Vector2f(200, 349));
    myExitButton = new Button(spritesSheet,
                                 IntRect(0,312,90,90), IntRect(90,312,90,90), IntRect(180,312,90,90),
                                 Vector2f(900, 400));

    myPlayButton->switchTexture("RELEASED");
    myOptionsButton->switchTexture("RELEASED");
    myCreditsButton->switchTexture("RELEASED");
    myExitButton->switchTexture("RELEASED");

    myBackgroundSprite = background;
}

string Menu::Open(RenderWindow &app, bool reCreate) //Le RenderWindow en référence permet de modifier l'app de GameManager directement
{
    cout << "Ouverture du Menu Principal." << endl << endl;

    //On assigne la taille correspodnant au menu à l'appli
    if(reCreate)
    {
        app.close();
        app.create(sf::VideoMode(myBackgroundSprite.getTextureRect().width, myBackgroundSprite.getTextureRect().height, 32), "Bomberman", Style::Resize|Style::Titlebar|Style::Close);
    }
    app.setTitle("Bomberman");

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
                        //Si on presse Echap dans le menu, même chose que Event::Closed.
                        case Keyboard::Escape :
                            return "EXIT";
                            break;
                        //Si on presse J, on demande au GameManager de lancer le jeu
                        case Keyboard::J :
                            return "OPEN_GAME";
                            break;
                        //Si on presse O, on demande au GameManager de d'ouvrir les options
                        case Keyboard::O :
                            return "OPEN_OPTIONS";
                            break;
                        //Si on presse C, on demande au GameManager de montrer les crédits
                        case Keyboard::C :
                            return "OPEN_CREDITS";
                            break;
                    }
                    break;
                case Event::MouseButtonPressed :
                    if(myPlayButton->isCursorOnButton(app))
                        return "OPEN_GAME";
                    else if (myOptionsButton->isCursorOnButton(app))
                        return "OPEN_OPTIONS";
                    else if (myCreditsButton->isCursorOnButton(app))
                        return "OPEN_CREDITS";
                    else if (myExitButton->isCursorOnButton(app))
                        return "EXIT";
                    break;
                case Event::MouseMoved :
                    MouseManager(app);
                    break;
            }

        }

        // Affichages
        app.clear();

        //On affiche le background
        app.draw(myBackgroundSprite);
        //On affiche les 3 boutons grâce à la méthode Button::getSprite()
        app.draw(myPlayButton->getSprite());
        app.draw(myOptionsButton->getSprite());
        app.draw(myCreditsButton->getSprite());
        app.draw(myExitButton->getSprite());

        app.display();
    }
}

void Menu::MouseManager(RenderWindow &app)
{
    if (myPlayButton->isCursorOnButton(app))
        myPlayButton->switchTexture("HOVERED");
    else if (myOptionsButton->isCursorOnButton(app))
        myOptionsButton->switchTexture("HOVERED");
    else if (myCreditsButton->isCursorOnButton(app))
        myCreditsButton->switchTexture("HOVERED");
    else if (myExitButton->isCursorOnButton(app))
        myExitButton->switchTexture("HOVERED");
    else
    {
        myPlayButton->switchTexture("RELEASED");
        myOptionsButton->switchTexture("RELEASED");
        myCreditsButton->switchTexture("RELEASED");
        myExitButton->switchTexture("RELEASED");
    }
}

Menu::~Menu()
{
    delete myPlayButton;
    delete myOptionsButton;
    delete myCreditsButton;
}
