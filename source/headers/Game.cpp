#include "Game.h"

#define VALUES "source/values.txt"
#define FONTH "source/fontes/Gilroy-Heavy.woff"
#define FONTM "source/fontes/Gilroy-Medium.woff"

void Game::createWindow()
{
    readValues(settingsValues, VALUES);
    setWidth(settingsValues.getWidth()); setHeight(settingsValues.getHeight()); setFullscreen(settingsValues.getFullscreen());

    // creating of the main window
    if(getFullscreen()) WWin.create(sf::VideoMode::getDesktopMode(), vecTitles[settingsValues.getLanguage()], sf::Style::Fullscreen);
    else                WWin.create(sf::VideoMode::getDesktopMode(), vecTitles[settingsValues.getLanguage()], sf::Style::Titlebar);

    WWin.setMouseCursorVisible(false);
    WWin.setSize(sf::Vector2u(getWidth(), getHeight()));

    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[0]));

    if (!IIcon.loadFromFile("source/images/icon.png")) exit(4);
    WWin.setIcon(32, 32, IIcon.getPixelsPtr());
}

void Game::mainloop()
{
    TxtTitle.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtTitle, settingsValues.getTitle(), 50, vecTitles[settingsValues.getLanguage()], 200, sf::Color::White, 20, sf::Color::Black);

    // creating of the menu
    std::vector<sf::String> vecNameMenu {vecTitles[2 + settingsValues.getLanguage()], vecTitles[4 + settingsValues.getLanguage()], vecTitles[6 + settingsValues.getLanguage()], vecTitles[8 + settingsValues.getLanguage()]};
    GameMenu myMenu(WWin, 950, 350, 100, 120, vecNameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    while (WWin.isOpen())
    {
        sf::Event EEvent;
        while (WWin.pollEvent(EEvent))
        {
            if (EEvent.type == sf::Event::KeyReleased)
            {
                if (EEvent.key.code == sf::Keyboard::Up) {myMenu.MoveUp(); }       
                if (EEvent.key.code == sf::Keyboard::Down) {myMenu.MoveDown(); }  
                if (EEvent.key.code == sf::Keyboard::Return)                                    
                {
                    switch (myMenu.getSelectedMenuNumber())
                    {
                    case 0:LevelMenu();  break;
                    case 1:Settings();   break;
                    case 2:AboutGame();  break;
                    case 3:WWin.close();  break;

                    default: break;
                    }
                }
            }
        }

        WWin.clear();
        WWin.draw(RSBackground);
        WWin.draw(TxtTitle);
        myMenu.draw();
        WWin.display();
    }
}

void Game::InitText(sf::Text& TxtMtext, float fXpos, float fYpos, const sf::String StrStr, 
    int nSizeFont, sf::Color ColMenuTextColor, int nBord, sf::Color ColBorderColor) // text formatting 
{
    TxtMtext.setCharacterSize(nSizeFont);
    TxtMtext.setPosition(fXpos, fYpos);
    TxtMtext.setString(StrStr);
    TxtMtext.setFillColor(ColMenuTextColor);
    TxtMtext.setOutlineThickness(nBord);
    TxtMtext.setOutlineColor(ColBorderColor);

}


// actually a game
void Game::input(Player& stick)
{
    sf::Event EEvent;

    while (WWin.pollEvent(EEvent))
    {
        //if (event.type == sf::Event::Closed) mainloop();
        if (EEvent.type == sf::Event::KeyPressed)
        {
            if ((EEvent.key.code == sf::Keyboard::Escape) && ((getPreEx()) || (getEndLevel()))) mainloop();

            if (EEvent.key.code == sf::Keyboard::Escape) setPreEx(true);
            if (EEvent.key.code == sf::Keyboard::Space) setPreEx(false);
        } 

        stick.Keys(EEvent); // player sprite control
    }
}

void Game::update(sf::Time const& TDeltaTime, Player& stick)
{
    stick.update(TDeltaTime);

    TTm += TDeltaTime;
    if (TTm > sf::milliseconds(2))
    {
        setPoints(stick.getPoints());

        TTm = sf::milliseconds(0);
    }
}

void Game::Camera(Player& stick, std::vector<sf::String> vecTileMap)
{
    // move of "camera"
    if (stick.getStick().getPosition().x > 960 && stick.getStick().getPosition().x < vecTileMap[0].getSize() * getTs() - 960) // must be edited
    {
        setOffsetX(stick.getStick().getPosition().x - 960);
        stick.setOffsetX(stick.getStick().getPosition().x - 960);
    }
    if (stick.getStick().getPosition().y > 540 && stick.getStick().getPosition().y < vecTileMap.size() * getTs() - 560)
    {
        setOffsetY(stick.getStick().getPosition().y - 540);
        stick.setOffsetY(stick.getStick().getPosition().y - 540);
    }
}

void Game::drawMap(std::vector<sf::String> vecTileMap, int nSize)
{
    SPlat.setTexture(AssetManager::GetTexture(vecTexture[nSize]));
    SDoor.setTexture(AssetManager::GetTexture(vecTexture[2 + nSize]));


    for (int i = 0; i < vecTileMap.size(); i++)
        for (int j = 0; j < vecTileMap[i].getSize(); j++)
        {
            if (vecTileMap[i][j] == 'A') // blocks
                SPlat.setTextureRect(sf::IntRect(0, 0, getTs(), getTs()));
            if (vecTileMap[i][j] == 'o') // points
                SPlat.setTextureRect(sf::IntRect(getTs(), 0, getTs(), getTs()));
            if ((vecTileMap[i][j] == ' ') || (vecTileMap[i][j] == 'D')) // nothing or door
                continue;

            SPlat.setPosition(j * getTs() - getOffsetX(), i * getTs() - getOffsetY());
            WWin.draw(SPlat);
        }

    for (int i = 0; i < vecTileMap.size(); i++)
        for (int j = 0; j < vecTileMap[i].getSize(); j++)
        {
            if ((vecTileMap[i][j] == 'D')) // door
            {
                if (!getDoorOpened())
                    SDoor.setTextureRect(sf::IntRect(0, 0, getTs(), 80 - nSize * 40));
                else if (getDoorOpened())
                {
                    SDoor.setTextureRect(sf::IntRect(getTs(), 0, getTs(), 80 - nSize * 40));
                    setEndLevel(true);
                }
            }
            else continue;

            SDoor.setPosition(j * getTs() - getOffsetX(), i * getTs() + 20 - nSize * 10 - getOffsetY());
            WWin.draw(SDoor);
        }
}

void Game::readMap(std::vector<sf::String>& vecTileMap, int nLevel) // reading a map from a text document and assigning it to an array
{
    std::ifstream file("source/maps/level" + std::to_string(nLevel) + ".txt");
    std::string SS;

    if (!file) exit(33);

    vecTileMap.clear();

    while (!file.eof())
    {
        std::getline(file, SS);
        vecTileMap.push_back(SS);
    }

    file.close();
}

void Game::LevelMenu()
{
    readMap(vecTileMap, 1);  // assign a first-level map

    TxtSettings.setFont(AssetManager::GetFont(FONTH));

    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[0]));

    std::vector<sf::String> vecNameMenu { "1 " + vecTitles[34 + settingsValues.getLanguage()], "2 " + vecTitles[34 + settingsValues.getLanguage()], "3 " + vecTitles[34 + settingsValues.getLanguage()], "4 " + vecTitles[34 + settingsValues.getLanguage()], "5 " + vecTitles[34 + settingsValues.getLanguage()] };
    GameMenu myMenu(WWin, 300, 250, 100, 120, vecNameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    sf::RectangleShape RSPanel;
    RSPanel.setSize(sf::Vector2f(1240, 540));
    RSPanel.setPosition(sf::Vector2f(650, 270));
    RSPanel.setTexture(&AssetManager::GetTexture("source/images/level(1).png"));

    sf::Text TxtExit;
    TxtExit.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtExit, 50, 50, "Press escape to return to the main menu", 50, sf::Color::Magenta, 5, sf::Color::Black);

    setTs(25);
    setOffsetX(-650);
    setOffsetY(-270);

    bool bMap = true;
    int nStart = 1;
    int nEnd = 6;

    while (WWin.isOpen())
    {
        sf::Event EEvent;
        while (WWin.pollEvent(EEvent))
        {
            if (EEvent.type == sf::Event::KeyPressed)
            {
                if (EEvent.key.code == sf::Keyboard::Escape) mainloop();
            }

            if (EEvent.type == sf::Event::KeyReleased)
            {
                if (EEvent.key.code == sf::Keyboard::Up) 
                { 
                    myMenu.MoveUp(); readMap(vecTileMap, myMenu.getSelectedMenuNumber() + 1);
                }

                if (EEvent.key.code == sf::Keyboard::Down) 
                { 
                    if ((myMenu.getSelectedMenuNumber() == nEnd + 1) && (nEnd + 1 < 6))
                    {
                        nStart++; nEnd++;
                    }
                    myMenu.MoveDown(); 
                    readMap(vecTileMap, myMenu.getSelectedMenuNumber() + 1);
                }

                if (EEvent.key.code == sf::Keyboard::Return) Level();
            }
        }

        WWin.clear();
        WWin.draw(RSBackground);
        WWin.draw(TxtExit);

        if(bMap) 
        {
            WWin.draw(RSPanel);
            drawMap(vecTileMap, 1);
        }

        myMenu.draw();
        WWin.display();
    }
}

void Game::Level()
{
    Player stick = Player(WWin, vecTileMap, vecSkin[settingsValues.getSkin()], 3 + 2 * settingsValues.getSkin());
    stick.setTexture(vecSkin[settingsValues.getSkin()]);

    TxtPoints.setFont(AssetManager::GetFont(FONTH));

    sf::RectangleShape RSBackgroundPlay;
    RSBackgroundPlay.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackgroundPlay.setTexture(&AssetManager::GetTexture(vecBackground[3]));

    sf::Clock CClock, CTimer;
    bool bTimer = false;
    int nStart = CClock.getElapsedTime().asSeconds(), nFinish;

    setTs(50);
    setOffsetX(0);
    setOffsetY(0);
    setPreEx(false);
    setEndLevel(false);

    while (WWin.isOpen())
    {
        sf::Time TDt = CClock.restart();

        setDoorOpened(stick.getDoorOpened());

        input(stick);
        if ((!bPreEx) && (!bEndLevel)) update(TDt, stick);

        WWin.clear();

        WWin.draw(RSBackgroundPlay);

        auto drawStick = stick.getStick();
        WWin.draw(drawStick);

        Camera(stick, vecTileMap);
        drawMap(vecTileMap, 0);

        WWin.draw(TxtPoints);
        
        if (getPreEx()) preExit();
        if (getEndLevel()) endOfTheLevel(nStart, nFinish, CTimer, bTimer);

        
        WWin.display();
    }
}

void Game::preExit()
{
    sf::RectangleShape RSPanel;
    RSPanel.setSize(sf::Vector2f(800, 400));
    RSPanel.setPosition(sf::Vector2f(nBgWidth / 2 - 400, nBgHeight / 2 - 200));
    RSPanel.setTexture(&AssetManager::GetTexture("source/images/exit.png"));
    //panel.setFillColor(sf::Color::Red);

    sf::Text TxtExit;
    TxtExit.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtExit, nBgWidth / 2 - 360, nBgHeight / 2 - 170, "If you exit, your progress\nwill not be saved\n\nPress escape to exit\nor space to return", 50, sf::Color::White, 5, sf::Color::Black);

    WWin.draw(RSPanel);
    WWin.draw(TxtExit);
}

void Game::endOfTheLevel(int nStart, int& nFinish, sf::Clock CTimer, bool& bTimer)
{
    sf::RectangleShape RSPanel;
    RSPanel.setSize(sf::Vector2f(800, 400));
    RSPanel.setPosition(sf::Vector2f(nBgWidth / 2 - 400, nBgHeight / 2 - 200));
    RSPanel.setTexture(&AssetManager::GetTexture("source/images/exit.png"));

    
    if (!bTimer)
    {
        nFinish = CTimer.getElapsedTime().asSeconds();
        bTimer = true;
    }
    int nTime = nFinish - nStart;

    sf::Text TxtExit;
    TxtExit.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtExit, nBgWidth / 2 - 360, nBgHeight / 2 - 170, "Your score is: " + std::to_string(getPoints()) + "\nYour time is:\n" + std::to_string(nTime/60) + " minutes " + std::to_string(nTime - nTime/60*60) + " seconds" + "\n\nPress escape to exit", 50, sf::Color::White, 5, sf::Color::Black);

    WWin.draw(RSPanel);
    WWin.draw(TxtExit);
}


// work with settings values in file
void Game::readValues(SettingsValues& settingValues, std::string sFileName) // reading a map from a text document and assigning it to an array
{
    std::ifstream file(sFileName);
    int nNum;

    if (!file) exit(33);
    file.seekg(0);

    int nValue;
    float fValue;
    bool bValue;

    file >> nValue;
    settingValues.setLanguage(nValue);
    file >> nValue;
    settingValues.setSkin(nValue);
    file >> nValue;
    settingValues.setWidth(nValue);
    file >> nValue;
    settingValues.setHeight(nValue);
    file >> fValue;
    settingValues.setSettingTitle(fValue);
    file >> fValue;
    settingValues.setTitle(fValue);
    file >> bValue;
    settingValues.setFullscreen(bValue);

    file.close();
}

void Game::clearValues(std::string sFileName)
{
    std::ofstream file(sFileName, std::ios_base::trunc); //Видаляє вміст існуючого файлу при створенні його керуючого об'єкта.
    file.close();
}

void Game::writeValues(SettingsValues settingValues, const std::string& sFileName)
{
    std::ofstream file(sFileName);
    if (!file.is_open()) exit(33);

    file << settingValues.getLanguage() << " ";
    file << settingValues.getSkin() << " ";
    file << settingValues.getWidth() << " ";
    file << settingValues.getHeight() << " ";
    file << settingValues.getSettingTitle() << " ";
    file << settingValues.getTitle() << " ";
    file << settingValues.getFullscreen() << " ";

    file.close();
}


// settings
void Game::Settings()
{
    TxtSettings.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtSettings, settingsValues.getSettingTitle(), 50, vecTitles[4 + settingsValues.getLanguage()], 200, sf::Color::White, 20, sf::Color::Black);

    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[1]));

    std::vector<sf::String> vecNameMenu { vecTitles[16 + settingsValues.getLanguage()], vecTitles[18 + settingsValues.getLanguage()], vecTitles[30 + settingsValues.getLanguage()], vecTitles[14 + settingsValues.getLanguage()]};
    GameMenu myMenu(WWin, 950, 350, 100, 120, vecNameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    while (WWin.isOpen())
    {
        sf::Event EEvent;
        while (WWin.pollEvent(EEvent))
        {
            if (EEvent.type == sf::Event::KeyReleased)
            {
                if (EEvent.key.code == sf::Keyboard::Up) { myMenu.MoveUp(); }
                if (EEvent.key.code == sf::Keyboard::Down) { myMenu.MoveDown(); }
                if (EEvent.key.code == sf::Keyboard::Return)
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

        WWin.clear();
        WWin.draw(RSBackground);
        WWin.draw(TxtSettings);
        myMenu.draw();
        WWin.display();
    }
}

void Game::SettingsLanguage()
{
    TxtSettings.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtSettings, settingsValues.getSettingTitle(), 50, vecTitles[4 + settingsValues.getLanguage()], 200, sf::Color::White, 20, sf::Color::Black);

    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[1]));

    std::vector<sf::String> vecNameMenu { vecTitles[10 + settingsValues.getLanguage()], vecTitles[12 + settingsValues.getLanguage()], vecTitles[24 + settingsValues.getLanguage()]};
    GameMenu myMenu(WWin, 950, 350, 100, 120, vecNameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    while (WWin.isOpen())
    {
        sf::Event EEvent;
        while (WWin.pollEvent(EEvent))
        {
            if (EEvent.type == sf::Event::KeyReleased)
            {
                if (EEvent.key.code == sf::Keyboard::Up) { myMenu.MoveUp(); }
                if (EEvent.key.code == sf::Keyboard::Down) { myMenu.MoveDown(); }
                if (EEvent.key.code == sf::Keyboard::Return)
                {
                    switch (myMenu.getSelectedMenuNumber())
                    {
                    case 0: {settingsValues.setLanguageValues(0, 573, 469.5); }  break;
                    case 1: {settingsValues.setLanguageValues(1, 244, 231.5); }  break;
                    case 2: Settings();                                          return;

                    default: break;
                    }

                    clearValues(VALUES); writeValues(settingsValues, VALUES); SettingsLanguage();
                }
            }
        }

        WWin.clear();
        WWin.draw(RSBackground);
        WWin.draw(TxtSettings);
        myMenu.draw();
        WWin.display();
    }
}

void Game::SettingsPers()
{
    TxtSettings.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtSettings, settingsValues.getSettingTitle(), 50, vecTitles[4 + settingsValues.getLanguage()], 200, sf::Color::White, 20, sf::Color::Black);

    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[1]));

    std::vector<sf::String> vecNameMenu { vecTitles[20 + settingsValues.getLanguage()], vecTitles[22 + settingsValues.getLanguage()], vecTitles[24 + settingsValues.getLanguage()]};
    GameMenu myMenu(WWin, 950, 350, 100, 120, vecNameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    while (WWin.isOpen())
    {
        sf::Event EEvent;
        while (WWin.pollEvent(EEvent))
        {
            if (EEvent.type == sf::Event::KeyReleased)
            {
                if (EEvent.key.code == sf::Keyboard::Up) { myMenu.MoveUp(); }
                if (EEvent.key.code == sf::Keyboard::Down) { myMenu.MoveDown(); }
                if (EEvent.key.code == sf::Keyboard::Return)
                {
                    switch (myMenu.getSelectedMenuNumber())
                    {
                    case 0: { settingsValues.setSkin(0); }  break;
                    case 1: { settingsValues.setSkin(1); }  break;
                    case 2: Settings();                     return;

                    default: break;
                    }

                    clearValues(VALUES); writeValues(settingsValues, VALUES);
                }
            }
        }

        WWin.clear();
        WWin.draw(RSBackground);
        WWin.draw(TxtSettings);
        myMenu.draw();
        WWin.display();
    }
}

void Game::SettingsScreen()
{
    TxtSettings.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtSettings, settingsValues.getSettingTitle(), 50, vecTitles[4 + settingsValues.getLanguage()], 200, sf::Color::White, 20, sf::Color::Black);

    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[1]));

    std::vector<sf::String> vecNameMenu { "1024*576", "1280*720", "1920*1080", vecTitles[32 + settingsValues.getLanguage()], vecTitles[24 + settingsValues.getLanguage()] };
    GameMenu myMenu(WWin, 950, 350, 100, 120, vecNameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    while (WWin.isOpen())
    {
        sf::Event EEvent;
        while (WWin.pollEvent(EEvent))
        {
            if (EEvent.type == sf::Event::KeyReleased)
            {
                if (EEvent.key.code == sf::Keyboard::Up) { myMenu.MoveUp(); }
                if (EEvent.key.code == sf::Keyboard::Down) { myMenu.MoveDown(); }
                if (EEvent.key.code == sf::Keyboard::Return)
                {
                    switch (myMenu.getSelectedMenuNumber())
                    {
                    case 0: {settingsValues.setScreenValues(1024, 576, false);  }  break;
                    case 1: {settingsValues.setScreenValues(1280, 720, false);  }  break;
                    case 2: {settingsValues.setScreenValues(1920, 1080, false); }  break;
                    case 3: {settingsValues.setScreenValues(1920, 1080, true);  }  break;
                    case 4: Settings();                                            return;

                    default: break;
                    }

                    clearValues(VALUES); writeValues(settingsValues, VALUES); 
                    setFullscreen(settingsValues.getFullscreen()); 
                    setWidth(settingsValues.getWidth()); 
                    setHeight(settingsValues.getHeight());  
                    createWindow(); 
                    SettingsScreen();
                }
            }
        }

        WWin.clear();
        WWin.draw(RSBackground);
        WWin.draw(TxtSettings);
        myMenu.draw();
        WWin.display();
    }
}


// about a game
void Game::AboutGame()
{
    sf::RectangleShape RSBackgroundAb;

    TxtAbout.setFont(AssetManager::GetFont(FONTM));

    sf::Text TxtExit;
    TxtExit.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtExit, 50, 50, "Press escape to return to the main menu", 50, sf::Color::Magenta, 5, sf::Color::Black);

    RSBackgroundAb.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackgroundAb.setTexture(&AssetManager::GetTexture(vecBackground[2]));

    InitText(TxtAbout, 277, 150, vecAbout[settingsValues.getLanguage()], 50, sf::Color::White, 3, sf::Color::Black);

    while (WWin.isOpen())
    {
        sf::Event EEvent;
        while (WWin.pollEvent(EEvent))
        {
            if (EEvent.type == sf::Event::Closed) mainloop();
            if (EEvent.type == sf::Event::KeyPressed)
            {
                if (EEvent.key.code == sf::Keyboard::Escape) mainloop();
            }
        }
        WWin.clear();
        WWin.draw(RSBackgroundAb);
        WWin.draw(TxtAbout);
        WWin.draw(TxtExit);
        WWin.display();
    }
}