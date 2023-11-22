#include "Game.h"

void Game::CreateWindow()
{
    // creating of the main window
    if(getFullscreen()) win.create(sf::VideoMode::getDesktopMode(), Titles[language], sf::Style::Fullscreen);
    else              win.create(sf::VideoMode::getDesktopMode(), Titles[language], sf::Style::Titlebar);

    win.setMouseCursorVisible(false);
    win.setSize(sf::Vector2u(getWidth(), getHeight()));

    background.setSize(sf::Vector2f(bgWidth, bgHeight));
    background.setTexture(&AssetManager::GetTexture(Bg[0]));

    if (!icon.loadFromFile("source/images/icon.png")) exit(4);
    win.setIcon(32, 32, icon.getPixelsPtr());

    Title.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Title, 469.5, 50, Titles[language], 200, sf::Color::White, 20, sf::Color::Black);
}

void Game::mainloop()
{
    // creating of the menu
    std::vector<sf::String> nameMenu {Titles[1 + language], Titles[2 + language], Titles[3 + language], Titles[4 + language]};
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
                    case 0:LevelMenu();  break;
                    case 1:Settings();   break;
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

void Game::drawMap(sf::String TileMap[H], int size)
{
    plat.setTexture(AssetManager::GetTexture(Texture[size]));

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
                plat.setTextureRect(sf::IntRect(0, 0, getTs(), getTs()));
            if (TileMap[i][j] == 'o') // points
                plat.setTextureRect(sf::IntRect(getTs(), 0, getTs(), getTs()));
            if (TileMap[i][j] == ' ') // nothing
                continue;

            plat.setPosition(j * getTs() - getOffsetX(), i * getTs() - getOffsetY());
            win.draw(plat);
        }
}

void Game::readMap(sf::String TileMap[H], int level)
{
    std::ifstream file("source/maps/level" + std::to_string(level) + ".txt");
    std::string s;

    if (!file) exit(33);

    for (int i = 0; i < H; i++)
    {
        std::getline(file, s);
        TileMap[i] = s;
    }
}

void Game::LevelMenu()
{
    readMap(TileMap, 1);

    Set.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));

    backgroundSet.setSize(sf::Vector2f(bgWidth, bgHeight));
    backgroundSet.setTexture(&AssetManager::GetTexture(Bg[0]));

    std::vector<sf::String> nameMenu { "1 " + Titles[17 + language], "2 " + Titles[17 + language], "3 " + Titles[17 + language], "4 " + Titles[17 + language], "5 " + Titles[17 + language] };
    GameMenu myMenu(win, 300, 250, 100, 120, nameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    sf::RectangleShape panel;
    panel.setSize(sf::Vector2f(960, 540));
    panel.setPosition(sf::Vector2f(650, 270));
    panel.setTexture(&AssetManager::GetTexture("source/images/level(1).png"));
    //panel.setFillColor(sf::Color::Black);

    sf::Text Exit;
    Exit.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Exit, 50, 50, "Press escape to return to the main menu", 50, sf::Color::Magenta, 5, sf::Color::Black);

    setTs(25);
    setOffsetX(-650);
    setOffsetY(-270);

    bool map = true;
    int start = 1;
    int end = 6;

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) mainloop();
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up) 
                { 
                    myMenu.MoveUp(); readMap(TileMap, myMenu.getSelectedMenuNumber() + 1);
                }

                if (event.key.code == sf::Keyboard::Down) 
                { 
                    if ((myMenu.getSelectedMenuNumber() == end + 1) && (end + 1 < 6))
                    {
                        start++; end++;
                    }
                    myMenu.MoveDown(); 
                    readMap(TileMap, myMenu.getSelectedMenuNumber() + 1);
                }

                if (event.key.code == sf::Keyboard::Return) Level();
            }
        }

        win.clear();
        win.draw(backgroundSet);
        win.draw(Exit);

        if(map) 
        {
            win.draw(panel);
            drawMap(TileMap, 1);
        }

        myMenu.draw();
        win.display();
    }
}

void Game::Level()
{
    Player stick = Player(win, TileMap, Pers[pers], 3 + 2 * pers);
    stick.setTexture(Pers[pers]);

    Points.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    //Time.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));

    sf::RectangleShape backgroundPlay;
    backgroundPlay.setSize(sf::Vector2f(bgWidth, bgHeight));
    backgroundPlay.setTexture(&AssetManager::GetTexture(Bg[3]));

    sf::Clock clock;
    bool preEx = false;

    setTs(50);
    setOffsetX(0);
    setOffsetY(0);


    while (win.isOpen())
    {
        sf::Time dt = clock.restart();

        input(stick, preEx);
        if (!preEx) update(dt, stick);

        win.clear();

        win.draw(backgroundPlay);

        auto drawStick = stick.getStick();
        win.draw(drawStick);

        drawMap(TileMap, 0);

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
    panel.setPosition(sf::Vector2f(bgWidth / 2 - 400, bgHeight / 2 - 200));
    //panel.setTexture(&AssetManager::GetTexture("source/images/background.png"));
    panel.setFillColor(sf::Color::Red);

    sf::Text Exit;
    Exit.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Exit, bgWidth / 2 - 360, bgHeight / 2 - 170, "If you exit, your progress\nwill not be saved\n\n\nPress escape to exit", 50, sf::Color::Magenta, 5, sf::Color::Black);

    win.draw(panel);
    win.draw(Exit);
}

void Game::Settings()
{
    Set.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Set, setTitle, 50, Titles[2 + language], 200, sf::Color::White, 20, sf::Color::Black);

    backgroundSet.setSize(sf::Vector2f(bgWidth, bgHeight));
    backgroundSet.setTexture(&AssetManager::GetTexture(Bg[1]));

    std::vector<sf::String> nameMenu { Titles[8 + language], Titles[9 + language], Titles[15 + language], Titles[7 + language]};
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
                    case 2: SettingsScreen();  break;
                    case 3: mainloop();  break;

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

    backgroundSet.setSize(sf::Vector2f(bgWidth, bgHeight));
    backgroundSet.setTexture(&AssetManager::GetTexture(Bg[1]));

    std::vector<sf::String> nameMenu { Titles[5 + language], Titles[6 + language], Titles[12 + language]};
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
                    case 1: {language = 18; about = 1; setTitle = 244; InitText(Title, 243.5, 50, Titles[language], 200, sf::Color::White, 20, sf::Color::Black); SettingsLanguage(); }    break;
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

    backgroundSet.setSize(sf::Vector2f(bgWidth, bgHeight));
    backgroundSet.setTexture(&AssetManager::GetTexture(Bg[1]));

    std::vector<sf::String> nameMenu { Titles[10 + language], Titles[11 + language], Titles[12 + language]};
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

void Game::SettingsScreen()
{
    Set.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Set, setTitle, 50, Titles[2 + language], 200, sf::Color::White, 20, sf::Color::Black);

    backgroundSet.setSize(sf::Vector2f(bgWidth, bgHeight));
    backgroundSet.setTexture(&AssetManager::GetTexture(Bg[1]));

    std::vector<sf::String> nameMenu { "1024*576", "1280*720", "1920*1080", Titles[16 + language], Titles[12 + language] };
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
                    case 0: {setFullscreen(false); setWidth(1024); setHeight(576);  CreateWindow(); SettingsScreen(); }  break;
                    case 1: {setFullscreen(false); setWidth(1280); setHeight(720);  CreateWindow(); SettingsScreen(); }  break;
                    case 2: {setFullscreen(false); setWidth(1920); setHeight(1080); CreateWindow(); SettingsScreen(); }  break;
                    case 3: {setFullscreen(true);  setWidth(1920); setHeight(1080); CreateWindow(); SettingsScreen(); }  break;                                  break;
                    case 4: Settings();  break;

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

    backgroundAb.setSize(sf::Vector2f(bgWidth, bgHeight));
    backgroundAb.setTexture(&AssetManager::GetTexture(Bg[2]));

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