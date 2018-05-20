#include "Credits.hpp"

using namespace std;
using namespace sf;

Credits::Credits(Sprite &background)
{
    Texture spritesSheet;
    if(!spritesSheet.loadFromFile("Ressources/Feuille_Sprites_Credits.png"))
        cerr << "Erreur de chargement de la feuille de sprites." << endl;

    myExitButton = new Button(spritesSheet,
                              IntRect(0, 0, 90, 90), IntRect(90, 0, 90, 90), IntRect(180, 0, 90, 90),
                              Vector2f(900, 400));

    myExitButton->switchTexture("RELEASED");

    myBackgroundSprite = background;
}

string Credits::Open(RenderWindow &app) //Le RenderWindow en référence permet de modifier l'app de GameManager directement
{
    cout << "Ouverture de la page des credits." << endl << endl;

    //On assigne la taille correspondant aux crédits à l'appli
    app.setSize(Vector2u(myBackgroundSprite.getTextureRect().width, myBackgroundSprite.getTextureRect().height));
    app.setTitle("Tetris : Credits");

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

                case Event::KeyPressed : //Si on appuie sur une touche...
                    switch(event.key.code)
                    {
                        //Si on presse Echap dans les credits, on retourne au menu
                        case Keyboard::Escape :
                            return "OPEN_MENU";
                    }
                case Event::MouseButtonPressed :
                    if (myExitButton->isCursorOnButton(app))
                        return "OPEN_MENU";
                case Event::MouseMoved :
                    if (myExitButton->isCursorOnButton(app))
                        myExitButton->switchTexture("HOVERED");
                    else
                        myExitButton->switchTexture("RELEASED");
            }

        }

        // Affichages
        app.clear();

        //On affiche le background
        app.draw(myBackgroundSprite);
        app.draw(myExitButton->getSprite());

        app.display();
    }
}

Credits::~Credits()
{
    delete myExitButton;
}
