#include "Game.h"
#include "GameMenu.h"

int Game::mainloop()
{
    // створення головного вікна
    win.create(sf::VideoMode::getDesktopMode(), "Stickman", sf::Style::Fullscreen);
    win.setMouseCursorVisible(false);

    if (!icon.loadFromFile("source/images/icon.png")) return 1;
    win.setIcon(32, 32, icon.getPixelsPtr());

    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    sf::RectangleShape gamingBackground(sf::Vector2f(width, height));
    if (!textureWall.loadFromFile("source/images/background.png")) return 2;
    gamingBackground.setTexture(&textureWall);
    
    if (!font.loadFromFile("source/fontes/Gilroy-Heavy.woff")) return 3; 
    Title.setFont(font);
    InitText(Title, 527, 50, "Stickman", 200, sf::Color::White, 20, sf::Color::Black);

    // створення меню
    sf::String nameMenu[4]{ "Start", "Settings", "About game", "Exit" };
    game::GameMenu myMenu(win, 950, 350, 100, 120, nameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    // цикл виконання програми
    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            // функції меню
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up) {myMenu.MoveUp(); }       
                if (event.key.code == sf::Keyboard::Down) {myMenu.MoveDown(); }  
                if (event.key.code == sf::Keyboard::Return)                                    
                {
                    switch (myMenu.getSelectedMenuNumber())
                    {
                    case 0:GameStart();  break;
                    case 1:Options();    break;
                    case 2:AboutGame();  break;
                    case 3:win.close();  break;

                    default: break;
                    }
                }
            }
        }

        // промальовка всіх компонент
        win.clear();
        win.draw(gamingBackground);
        win.draw(Title);
        myMenu.draw();
        win.display();
    }
}

void Game::InitText(sf::Text& mtext, float xpos, float ypos, const sf::String str, 
    int sizeFont, sf::Color menuTextColor, int bord, sf::Color borderColor) // форматування тексту (заголовку)
{
    mtext.setCharacterSize(sizeFont);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menuTextColor);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(borderColor);

}

void Game::GameStart()
{
    sf::RenderWindow play(sf::VideoMode::getDesktopMode(), "Level 1", sf::Style::Fullscreen);
    play.setMouseCursorVisible(false);

    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    sf::RectangleShape backgroundPlay(sf::Vector2f(width, height));
    sf::Texture texturePlay;

    if (!texturePlay.loadFromFile("source/images/level1.png")) exit(1);
    backgroundPlay.setTexture(&texturePlay);

    while (play.isOpen())
    {
        sf::Event eventPlay;
        while (play.pollEvent(eventPlay))
        {
            if (eventPlay.type == sf::Event::KeyPressed)
            {
                if (eventPlay.key.code == sf::Keyboard::Escape) { play.close(); }
            }
        }
        play.clear();
        play.draw(backgroundPlay);
        play.display();
    }
}

void Game::Options()
{
    sf::RenderWindow options(sf::VideoMode::getDesktopMode(), "Options", sf::Style::Fullscreen);
    options.setMouseCursorVisible(false);

    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    sf::RectangleShape backgroundOpt(sf::Vector2f(width, height));
    sf::Texture textureOpt;
    if (!textureOpt.loadFromFile("source/images/options.png")) exit(2);

    backgroundOpt.setTexture(&textureOpt);
    while (options.isOpen())
    {
        sf::Event eventOpt;
        while (options.pollEvent(eventOpt))
        {
            if (eventOpt.type == sf::Event::Closed) options.close();
            if (eventOpt.type == sf::Event::KeyPressed)
            {
                if (eventOpt.key.code == sf::Keyboard::Escape) options.close();
            }
        }
        options.clear();
        options.draw(backgroundOpt);
        options.display();
    }
}

void Game::AboutGame()
{
    sf::RenderWindow about(sf::VideoMode::getDesktopMode(), "About game", sf::Style::Fullscreen);
    about.setMouseCursorVisible(false);

    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    sf::RectangleShape backgroundAb(sf::Vector2f(width, height));
    sf::Texture textureAb;
    if (!textureAb.loadFromFile("source/images/about.png")) exit(3);

    backgroundAb.setTexture(&textureAb);
    while (about.isOpen())
    {
        sf::Event eventPlay;
        while (about.pollEvent(eventPlay))
        {
            if (eventPlay.type == sf::Event::Closed) about.close();
            if (eventPlay.type == sf::Event::KeyPressed)
            {
                if (eventPlay.key.code == sf::Keyboard::Escape) about.close();
            }
        }
        about.clear();
        about.draw(backgroundAb);
        about.display();
    }
}