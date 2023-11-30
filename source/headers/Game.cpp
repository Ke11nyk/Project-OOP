#include "Game.h"

#define VALUES "source/values"
#define FONTH "source/fontes/Gilroy-Heavy.woff"
#define FONTM "source/fontes/Gilroy-Medium.woff"

void Game::createWindow()
{
    readValues(Values, VALUES);
    setWidth(Values[3]); setHeight(Values[4]); setFullscreen(Values[7]);

    // creating of the main window
    if(getFullscreen()) win.create(sf::VideoMode::getDesktopMode(), Titles[Values[0]], sf::Style::Fullscreen);
    else              win.create(sf::VideoMode::getDesktopMode(), Titles[Values[0]], sf::Style::Titlebar);

    win.setMouseCursorVisible(false);
    win.setSize(sf::Vector2u(getWidth(), getHeight()));

    background.setSize(sf::Vector2f(bgWidth, bgHeight));
    background.setTexture(&AssetManager::GetTexture(Bg[0]));

    if (!icon.loadFromFile("source/images/icon.png")) exit(4);
    win.setIcon(32, 32, icon.getPixelsPtr());
}

void Game::mainloop()
{
    Title.setFont(AssetManager::GetFont("source/fontes/Gilroy-Heavy.woff"));
    InitText(Title, Values[6], 50, Titles[Values[0]], 200, sf::Color::White, 20, sf::Color::Black);

    // creating of the menu
    std::vector<sf::String> nameMenu {Titles[1 + Values[0]], Titles[2 + Values[0]], Titles[3 + Values[0]], Titles[4 + Values[0]]};
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
    if (tm > sf::milliseconds(2))
    {
        //auto mystick = stick.getStick();

        setPoints(stick.getPoints());
        InitText(Points, 100, 50, Titles[13 + Values[0]] + std::to_string(points), 50, sf::Color::Magenta, 5, sf::Color::Black);

        /*setTimeM(getTimeM() + 0.03 / 60);
        setTimeS(getTimeS() + 0.03);
        InitText(Time, 1600, 50, Titles[14 + language] + std::to_string(deltaTime.asSeconds()) + ":" + std::to_string(int(getTimeS())), 50, sf::Color::Magenta, 5, sf::Color::Black);*/

        tm = sf::milliseconds(0);
    }
}

void Game::drawMap(sf::String TileMap[H], int size, Player& stick)
{
    plat.setTexture(AssetManager::GetTexture(Texture[size]));

    if (stick.getStick().getPosition().x > 960)
    {
        setOffsetX(stick.getStick().getPosition().x - 960);
        //stick.setOffsetX(stick.getStick().getPosition().x - 970);
    }
    if (stick.getStick().getPosition().y > 540)
    {
        setOffsetY(stick.getStick().getPosition().y - 540);
        //stick.setOffsetY(stick.getStick().getPosition().y - 540);
    }


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

void Game::drawMap(sf::String TileMap[H], int size)
{
    plat.setTexture(AssetManager::GetTexture(Texture[size]));


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

void Game::readMap(sf::String TileMap[H], int level) // reading a map from a text document and assigning it to an array
{
    std::ifstream file("source/maps/level" + std::to_string(level) + ".txt");
    std::string s;

    if (!file) exit(33);

    for (int i = 0; i < H; i++)
    {
        std::getline(file, s);
        TileMap[i] = s;
    }

    file.close();
}

void Game::LevelMenu()
{
    readMap(TileMap, 1);  // assign a first-level map

    Set.setFont(AssetManager::GetFont(FONTH));

    background.setSize(sf::Vector2f(bgWidth, bgHeight));
    background.setTexture(&AssetManager::GetTexture(Bg[0]));

    std::vector<sf::String> nameMenu { "1 " + Titles[17 + Values[0]], "2 " + Titles[17 + Values[0]], "3 " + Titles[17 + Values[0]], "4 " + Titles[17 + Values[0]], "5 " + Titles[17 + Values[0]] };
    GameMenu myMenu(win, 300, 250, 100, 120, nameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    sf::RectangleShape panel;
    panel.setSize(sf::Vector2f(960, 540));
    panel.setPosition(sf::Vector2f(650, 270));
    panel.setTexture(&AssetManager::GetTexture("source/images/level(1).png"));

    sf::Text Exit;
    Exit.setFont(AssetManager::GetFont(FONTH));
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
        win.draw(background);
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
    Player stick = Player(win, TileMap, Pers[Values[2]], 3 + 2 * Values[2]);
    stick.setTexture(Pers[Values[2]]);

    Points.setFont(AssetManager::GetFont(FONTH));
    //Time.setFont(AssetManager::GetFont(FONT));

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

        drawMap(TileMap, 0, stick);

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
    panel.setTexture(&AssetManager::GetTexture("source/images/exit.png"));
    //panel.setFillColor(sf::Color::Red);

    sf::Text Exit;
    Exit.setFont(AssetManager::GetFont(FONTH));
    InitText(Exit, bgWidth / 2 - 360, bgHeight / 2 - 170, "If you exit, your progress\nwill not be saved\n\nPress escape to exit\nor space to return", 50, sf::Color::White, 5, sf::Color::Black);

    win.draw(panel);
    win.draw(Exit);
}


// work with settings values in file
void Game::readValues(std::vector<int>& values, std::string nameFile) // reading a map from a text document and assigning it to an array
{
    std::ifstream file(nameFile);
    int num;

    if (!file) exit(33);
    file.seekg(0);
    for (int i = 0; i < values.size(); i++)
    {
        if (!file.eof()) //Пока не конец файла; eof - end of file
        {
            file >> num;
            values[i] = num;
        }
    }

    file.close();
}

void Game::clearValues(std::string fileName)
{
    std::ofstream file(fileName, std::ios_base::trunc); //Видаляє вміст існуючого файлу при створенні його керуючого об'єкта.
    file.close();
}

void Game::writeValues(const std::vector<int>& values, const std::string& fileName)
{
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) exit(33);

    for (const auto& number : values) {
        outputFile << number << " ";
    }

    outputFile.close();
}


// settings
void Game::Settings()
{
    Set.setFont(AssetManager::GetFont(FONTH));
    InitText(Set, Values[5], 50, Titles[2 + Values[0]], 200, sf::Color::White, 20, sf::Color::Black);

    background.setSize(sf::Vector2f(bgWidth, bgHeight));
    background.setTexture(&AssetManager::GetTexture(Bg[1]));

    std::vector<sf::String> nameMenu { Titles[8 + Values[0]], Titles[9 + Values[0]], Titles[15 + Values[0]], Titles[7 + Values[0]]};
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
        win.draw(background);
        win.draw(Set);
        myMenu.draw();
        win.display();
    }
}

void Game::SettingsLanguage()
{
    Set.setFont(AssetManager::GetFont(FONTH));
    InitText(Set, Values[5], 50, Titles[2 + Values[0]], 200, sf::Color::White, 20, sf::Color::Black);

    background.setSize(sf::Vector2f(bgWidth, bgHeight));
    background.setTexture(&AssetManager::GetTexture(Bg[1]));

    std::vector<sf::String> nameMenu { Titles[5 + Values[0]], Titles[6 + Values[0]], Titles[12 + Values[0]]};
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
                    case 0: {Values[0] = Values[1] = 0;     Values[5] = 573; Values[6] = 469; }  break;
                    case 1: {Values[0] = 18; Values[1] = 1; Values[5] = 244; Values[6] = 231; }  break;
                    case 2: Settings();                                                          return;

                    default: break;
                    }

                    clearValues(VALUES); writeValues(Values, VALUES); SettingsLanguage();
                }
            }
        }

        win.clear();
        win.draw(background);
        win.draw(Set);
        myMenu.draw();
        win.display();
    }
}

void Game::SettingsPers()
{
    Set.setFont(AssetManager::GetFont(FONTH));
    InitText(Set, Values[5], 50, Titles[2 + Values[0]], 200, sf::Color::White, 20, sf::Color::Black);

    background.setSize(sf::Vector2f(bgWidth, bgHeight));
    background.setTexture(&AssetManager::GetTexture(Bg[1]));

    std::vector<sf::String> nameMenu { Titles[10 + Values[0]], Titles[11 + Values[0]], Titles[12 + Values[0]]};
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
                    case 0: { Values[2] = 0; }  break;
                    case 1: { Values[2] = 1; }  break;
                    case 2: Settings();         return;

                    default: break;
                    }

                    clearValues(VALUES); writeValues(Values, VALUES);
                }
            }
        }

        win.clear();
        win.draw(background);
        win.draw(Set);
        myMenu.draw();
        win.display();
    }
}

void Game::SettingsScreen()
{
    Set.setFont(AssetManager::GetFont(FONTH));
    InitText(Set, Values[5], 50, Titles[2 + Values[0]], 200, sf::Color::White, 20, sf::Color::Black);

    background.setSize(sf::Vector2f(bgWidth, bgHeight));
    background.setTexture(&AssetManager::GetTexture(Bg[1]));

    std::vector<sf::String> nameMenu { "1024*576", "1280*720", "1920*1080", Titles[16 + Values[0]], Titles[12 + Values[0]] };
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
                    case 0: {setFullscreen(false); Values[3] = 1024; Values[4] = 576;  Values[7] = 0; }  break;
                    case 1: {setFullscreen(false); Values[3] = 1280; Values[4] = 720;  Values[7] = 0; }  break;
                    case 2: {setFullscreen(false); Values[3] = 1920; Values[4] = 1080; Values[7] = 0; }  break;
                    case 3: {setFullscreen(true);  Values[3] = 1920; Values[4] = 1080; Values[7] = 1; }  break;
                    case 4: Settings();  return;

                    default: break;
                    }

                    clearValues(VALUES); writeValues(Values, VALUES); setWidth(Values[3]); setHeight(Values[4]);  createWindow(); SettingsScreen();
                }
            }
        }

        win.clear();
        win.draw(background);
        win.draw(Set);
        myMenu.draw();
        win.display();
    }
}


void Game::AboutGame()
{
    sf::RectangleShape backgroundAb;

    About.setFont(AssetManager::GetFont(FONTM));

    sf::Text Exit;
    Exit.setFont(AssetManager::GetFont(FONTH));
    InitText(Exit, 50, 50, "Press escape to return to the main menu", 50, sf::Color::Magenta, 5, sf::Color::Black);

    backgroundAb.setSize(sf::Vector2f(bgWidth, bgHeight));
    backgroundAb.setTexture(&AssetManager::GetTexture(Bg[2]));

    InitText(About, 277, 150, Ab[Values[1]], 50, sf::Color::White, 3, sf::Color::Black);

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
        win.display();
    }
}