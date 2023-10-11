#include "Game.h"

void Game::CreateWindow()
{
    // creating of the main window
    win.create(sf::VideoMode::getDesktopMode(), "Stickman", sf::Style::Default);
    win.setMouseCursorVisible(false);

    background.setSize(sf::Vector2f(width, height));
    background.setTexture(&AssetManager::GetTexture("source/images/background.png"));

    if (!icon.loadFromFile("source/images/icon.png")) exit(4);
    win.setIcon(32, 32, icon.getPixelsPtr());

    Title.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Title, 527, 50, "Stickman", 200, sf::Color::White, 20, sf::Color::Black);


    mainloop();
}

void Game::update(sf::Time const& deltaTime)
{
   PlayerAnim.Update(deltaTime);
}

void Game::mainloop()
{
    // creating of the menu
    sf::String nameMenu[4]{ "Start", "Settings", "About game", "Exit" };
    game::GameMenu myMenu(win, 950, 350, 100, 120, nameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    

    

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up) {myMenu.MoveUp(); }       
                if (event.key.code == sf::Keyboard::Down) {myMenu.MoveDown(); }  
                if (event.key.code == sf::Keyboard::Return)                                    
                {
                    switch (myMenu.getSelectedMenuNumber())
                    {
                    case 0:GameStart();  break;
                    case 1:Settings();    break;
                    case 2:AboutGame();  break;
                    case 3:win.close();  break;

                    default: break;
                    }
                }
            }
        }

        win.clear();
        win.draw(background);
        win.draw(Title);
        myMenu.draw();
        win.display();
    }
}

void Game::InitText(sf::Text& mtext, float xpos, float ypos, const sf::String str, 
    int sizeFont, sf::Color menuTextColor, int bord, sf::Color borderColor) // text formatting 
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
    sf::RectangleShape backgroundPlay;

    backgroundPlay.setSize(sf::Vector2f(width, height));
    backgroundPlay.setTexture(&AssetManager::GetTexture("source/images/level1.png"));

    auto spriteSize = sf::Vector2i(108, 120);
    auto& idleForward = PlayerAnim.CreateAnimation("idleForward", "source/images/figure-R.png", sf::seconds(1), true);
    idleForward.AddFrames(sf::Vector2i(0, 0), spriteSize, 3, 1);
    PlayerSprite.setPosition(600, 350);

    sf::Clock clock;

    while (win.isOpen())
    {
        sf::Event eventPlay;
        while (win.pollEvent(eventPlay))
        {
            if (eventPlay.type == sf::Event::Closed) mainloop();
            if (eventPlay.type == sf::Event::KeyPressed)
            {
                if (eventPlay.key.code == sf::Keyboard::Escape) mainloop();
            }
        }
        win.clear();
        win.draw(backgroundPlay);

        win.draw(PlayerSprite);

        sf::Time dt = clock.restart();
        update(dt);

        win.display();
    }
}

void Game::Settings()
{
    sf::RectangleShape backgroundSet;

    backgroundSet.setSize(sf::Vector2f(width, height));
    backgroundSet.setTexture(&AssetManager::GetTexture("source/images/settings.png"));

    while (win.isOpen())
    {
        sf::Event eventSet;
        while (win.pollEvent(eventSet))
        {
            if (eventSet.type == sf::Event::Closed) mainloop();
            if (eventSet.type == sf::Event::KeyPressed)
            {
                if (eventSet.key.code == sf::Keyboard::Escape) mainloop();
            }
        }
        win.clear();
        win.draw(backgroundSet);
        win.display();
    }
}

void Game::AboutGame()
{
    sf::RectangleShape backgroundAb;

    About.setFont(AssetManager::GetFont("source/fontes/Gilroy-Medium.woff"));

    backgroundAb.setSize(sf::Vector2f(width, height));
    backgroundAb.setTexture(&AssetManager::GetTexture("source/images/about.png"));

    InitText(About, 277, 150, "A game about a stickman who needs to get to the door by \njumping on platforms.\
 Originally implemented in Python, the \ncurrent implementation is in C++ using the SFML library. \n\n\
Currently, a static level is implemented. \nRandomization of levels, endless mode are planned. \
    \n\nMade by Artem Verbytskyi as part of a project for OOOP \
    \n\n\n\n\nCopyright © 2023 by Ke11nyk", 50, sf::Color::White, 3, sf::Color::Black);

    while (win.isOpen())
    {
        sf::Event eventPlay;
        while (win.pollEvent(eventPlay))
        {
            if (eventPlay.type == sf::Event::Closed) mainloop();
            if (eventPlay.type == sf::Event::KeyPressed)
            {
                if (eventPlay.key.code == sf::Keyboard::Escape) mainloop();
            }
        }
        win.clear();
        win.draw(backgroundAb);
        win.draw(About);
        win.display();
    }
}