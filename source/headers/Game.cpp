#include "Game.h"

void Game::CreateWindow()
{
    // creating of the main window
    win.create(sf::VideoMode::getDesktopMode(), Titles[language], sf::Style::Default);
    win.setMouseCursorVisible(false);

    background.setSize(sf::Vector2f(width, height));
    background.setTexture(&AssetManager::GetTexture("source/images/background.png"));

    if (!icon.loadFromFile("source/images/icon.png")) exit(4);
    win.setIcon(32, 32, icon.getPixelsPtr());

    Title.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Title, 469.5, 50, Titles[language], 200, sf::Color::White, 20, sf::Color::Black);


    mainloop();
}

void Game::mainloop()
{
    // creating of the menu
    sf::String nameMenu[4]{ Titles[1 + language], Titles[2 + language], Titles[3 + language], Titles[4 + language] };
    GameMenu myMenu(win, 950, 350, 100, 120, nameMenu);
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

// actually a game
void Game::input(Player& stick, bool& preEx)
{
    sf::Event event;

    while (win.pollEvent(event))
    {
        //if (event.type == sf::Event::Closed) mainloop();
        if (event.type == sf::Event::KeyPressed)
        {
            if ((event.key.code == sf::Keyboard::Escape) && preEx) mainloop();

            if (event.key.code == sf::Keyboard::Escape) preEx = true;
            if (event.key.code == sf::Keyboard::Space) preEx = false;
        } 

        stick.Keys(event); // player sprite control
    }
}

void Game::update(sf::Time const& deltaTime, Player& stick)
{
    stick.update(deltaTime);

    tm += deltaTime;
    time += deltaTime;
    if (tm > sf::milliseconds(3))
    {
        //auto mystick = stick.getStick();

        setPoints(stick.getPoints());
        InitText(Points, 100, 50, Titles[13 + language] + std::to_string(points), 50, sf::Color::Magenta, 5, sf::Color::Black);

        /*setTimeM(getTimeM() + 0.03 / 60);
        setTimeS(getTimeS() + 0.03);
        InitText(Time, 1600, 50, Titles[14 + language] + std::to_string(deltaTime.asSeconds()) + ":" + std::to_string(int(getTimeS())), 50, sf::Color::Magenta, 5, sf::Color::Black);*/

        tm = sf::milliseconds(0);
    }
}

void Game::drawMap(sf::String TileMap[H])
{
    plat.setTexture(AssetManager::GetTexture("source/images/plat.png"));

    /*if (stick.getStick().getPosition().x > 970)
    {
        setOffsetX(stick.getStick().getPosition().x - 970);
        stick.setOffsetX(stick.getStick().getPosition().x - 970);
    }
    if (stick.getStick().getPosition().y > 540)
    {
        setOffsetY(stick.getStick().getPosition().y - 540);
        stick.setOffsetY(stick.getStick().getPosition().y - 540);
    }*/


    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
        {
            if (TileMap[i][j] == 'A') // blocks
                plat.setTextureRect(sf::IntRect(0, 0, ts, ts));
            if (TileMap[i][j] == 'o') // points
                plat.setTextureRect(sf::IntRect(ts, 0, ts, ts));
            if (TileMap[i][j] == ' ') // nothing
                continue;

            plat.setPosition(j * ts - offsetX, i * ts - offsetY);
            win.draw(plat);
        }
}

void Game::GameStart()
{
    sf::String TileMap[H] = {
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                AAA                  A",
    "A                     AAAA            A",
    "AAAAA    oooo   AAA                   A",
    "A                                     A",
    "A       AAAAAA                        A",
    "A                                     A",
    "AAAAA                                 A",
    "A                     oooooo          A",
    "A              AAAA                   A",
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
    };

    Player stick = Player(win, TileMap, Pers[pers], 3 + 2 * pers);
    stick.setTexture(Pers[pers]);

    Points.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    //Time.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));

    sf::RectangleShape backgroundPlay;
    backgroundPlay.setSize(sf::Vector2f(width, height));
    backgroundPlay.setTexture(&AssetManager::GetTexture("source/images/level1(1).png"));

    sf::Clock clock;
    bool preEx = false;

    
    

    while (win.isOpen())
    {
        sf::Time dt = clock.restart();

        input(stick, preEx);
        if (!preEx) update(dt, stick);

        win.clear();

        win.draw(backgroundPlay);

        auto drawStick = stick.getStick();
        win.draw(drawStick);

        drawMap(TileMap);

        win.draw(Points);
        win.draw(Time);
        
        if (preEx) preExit();
        
        win.display();
    }
}

void Game::preExit()
{
    sf::RectangleShape panel;
    panel.setSize(sf::Vector2f(800, 400));
    panel.setPosition(sf::Vector2f(width / 2 - 400, height / 2 - 200));
    //panel.setTexture(&AssetManager::GetTexture("source/images/background.png"));
    panel.setFillColor(sf::Color::Black);

    sf::Text Exit;
    Exit.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Exit, width / 2 - 400, height / 2 - 200, "If you exit, your progress\nwill not be saved\n\nPress escape to exit", 50, sf::Color::Magenta, 5, sf::Color::Black);

    win.draw(panel);
    win.draw(Exit);
}

void Game::Settings()
{
    Set.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Set, setTitle, 50, Titles[2 + language], 200, sf::Color::White, 20, sf::Color::Black);

    backgroundSet.setSize(sf::Vector2f(width, height));
    backgroundSet.setTexture(&AssetManager::GetTexture("source/images/settings.png"));

    sf::String nameMenu[3]{ Titles[8 + language], Titles[9 + language], Titles[7 + language] };
    GameMenu myMenu(win, 950, 350, 100, 120, nameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up) { myMenu.MoveUp(); }
                if (event.key.code == sf::Keyboard::Down) { myMenu.MoveDown(); }
                if (event.key.code == sf::Keyboard::Return)
                {
                    switch (myMenu.getSelectedMenuNumber())
                    {
                    case 0: SettingsLanguage();  break;
                    case 1: SettingsPers();    break;
                    case 2: mainloop();  break;

                    default: break;
                    }
                }
            }
        }

        win.clear();
        win.draw(backgroundSet);
        win.draw(Set);
        myMenu.draw();
        win.display();
    }
}

void Game::SettingsLanguage()
{
    Set.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Set, setTitle, 50, Titles[2 + language], 200, sf::Color::White, 20, sf::Color::Black);

    backgroundSet.setSize(sf::Vector2f(width, height));
    backgroundSet.setTexture(&AssetManager::GetTexture("source/images/settings.png"));

    sf::String nameMenu[3]{ Titles[5 + language], Titles[6 + language], Titles[12 + language] };
    GameMenu myMenu(win, 950, 350, 100, 120, nameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up) { myMenu.MoveUp(); }
                if (event.key.code == sf::Keyboard::Down) { myMenu.MoveDown(); }
                if (event.key.code == sf::Keyboard::Return)
                {
                    switch (myMenu.getSelectedMenuNumber())
                    {
                    case 0: {language = about = 0; setTitle = 573;  InitText(Title, 469.5, 50, Titles[language], 200, sf::Color::White, 20, sf::Color::Black); SettingsLanguage(); }  break;
                    case 1: {language = 15; about = 1; setTitle = 244; InitText(Title, 243.5, 50, Titles[language], 200, sf::Color::White, 20, sf::Color::Black); SettingsLanguage(); }    break;
                    case 2: Settings();  break;

                    default: break;
                    }
                }
            }
        }

        win.clear();
        win.draw(backgroundSet);
        win.draw(Set);
        myMenu.draw();
        win.display();
    }
}

void Game::SettingsPers()
{
    Set.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Set, setTitle, 50, Titles[2 + language], 200, sf::Color::White, 20, sf::Color::Black);

    backgroundSet.setSize(sf::Vector2f(width, height));
    backgroundSet.setTexture(&AssetManager::GetTexture("source/images/settings.png"));

    sf::String nameMenu[3]{ Titles[10 + language], Titles[11 + language], Titles[12 + language] };
    GameMenu myMenu(win, 950, 350, 100, 120, nameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up) { myMenu.MoveUp(); }
                if (event.key.code == sf::Keyboard::Down) { myMenu.MoveDown(); }
                if (event.key.code == sf::Keyboard::Return)
                {
                    switch (myMenu.getSelectedMenuNumber())
                    {
                    case 0: { pers = 0; }  break;
                    case 1: { pers = 1; }   break;
                    case 2: Settings();  break;

                    default: break;
                    }
                }
            }
        }

        win.clear();
        win.draw(backgroundSet);
        win.draw(Set);
        myMenu.draw();
        win.display();
    }
}

void Game::AboutGame()
{
    sf::RectangleShape backgroundAb;

    About.setFont(AssetManager::GetFont("source/fontes/Gilroy-Medium.woff"));

    sf::Text Exit;
    Exit.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Exit, 50, 50, "Press escape to return to the main menu", 50, sf::Color::Magenta, 5, sf::Color::Black);

    backgroundAb.setSize(sf::Vector2f(width, height));
    backgroundAb.setTexture(&AssetManager::GetTexture("source/images/about(1).png"));

    InitText(About, 277, 150, Ab[about], 50, sf::Color::White, 3, sf::Color::Black);

    //LevelMenu myMenu(win, 950, 350, 100, 120, 120, 4, 4);
    //myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);

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
        win.draw(Exit);
        //myMenu.draw();
        win.display();
    }
}