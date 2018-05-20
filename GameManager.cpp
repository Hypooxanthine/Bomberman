#include "GameManager.hpp"

using namespace std;
using namespace sf;

GameManager::GameManager(string toDo)
{
    bool reCreate = false;

    cout << "Instanciation de l'objet GameManager." << endl << endl;

    if(!myBackgroundTexture.loadFromFile("Ressources/Background.png"))
        cerr << "Erreur de chargement du Background." << endl;
    else
        myBackgroundSprite.setTexture(myBackgroundTexture);

    if(!myGameBackgroundTexture.loadFromFile("Ressources/Game_Background.png"))
        cerr << "Erreur de chargement du Game Background." << endl;
    else
        myGameBackgroundSprite.setTexture(myGameBackgroundTexture);

    if(!myMusic.openFromFile("Ressources/Tetris.ogg"))
        cerr << "Erreur de chargement de la musique." << endl;
    else
    {
        myMusic.play();
        myMusic.setVolume(0);
        myMusic.setLoop(true);
    }

    //On ouvre la fenêtre
    myApp.create(VideoMode(1000, 500, 32), "Bomberman", Style::Resize|Style::Titlebar|Style::Close);

    //On instancie les différentes parties du programme
    myMenu = new Menu(myBackgroundSprite);
    myGame = new Game();
    myOptions = new Options(myBackgroundSprite);
    myCredits = new Credits(myBackgroundSprite);

    /*La boucle permettant de naviguer dans tout le programme
    Tant qu'on n'a pas quitté un membre du programme en disant
    que l'on veut quitter le programme entier, on continue à
    afficher ce qu'on demande */
    while(toDo != "EXIT")
    {
        if(toDo == "OPEN_GAME")
        {
            toDo = myGame->Open(myApp);
            reCreate = true;
        }
        else if(toDo == "OPEN_OPTIONS")
        {
            toDo = myOptions->Open(myApp, myMusic);
            reCreate = false;
        }
        else if(toDo == "OPEN_CREDITS")
        {
            toDo = myCredits->Open(myApp);
            reCreate = false;
        }
        //En cas de problème, on ouvre le Menu principal
        else
        {
            toDo = myMenu->Open(myApp, reCreate);
            reCreate = false;
        }
    }
}

GameManager::~GameManager()
{
    cout << "Destruction de l'objet GameManager." << endl;

    delete myMenu;
    delete myGame;
    delete myOptions;
    delete myCredits;

    myMusic.stop();
    myApp.close();

    system("PAUSE");
}
