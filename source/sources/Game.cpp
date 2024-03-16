#include "../headers/Game.h"

#define VALUES "D:/Uni materials/2 course/OOP/Project OOP/source/values.txt"
#define FONTH "D:/Uni materials/2 course/OOP/Project OOP/source/fontes/Gilroy-Heavy.woff"
#define FONTM "D:/Uni materials/2 course/OOP/Project OOP/source/fontes/Gilroy-Medium.woff"
#define ICON "D:/Uni materials/2 course/OOP/Project OOP/source/images/icon.png"


// drawing elements on window
template <size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
WinDraw(sf::RenderWindow& WWin, std::tuple<Tp...>& t) {}

template <size_t I = 0, typename... Tp>
inline typename std::enable_if < I < sizeof...(Tp), void>::type
    WinDraw(sf::RenderWindow& WWin, std::tuple<Tp...>& t)
{
    WWin.draw(std::get<I>(t));
    WinDraw<I + 1, Tp...>(WWin, t);
}

/**
* \brief The method that sets up the text that will be displayed
* \param TxtMtext The text that will be setted up
* \param fXpos The position of the text on X-coordinates
* \param fYpos The position of the text on Y-coordinates
* \param StrStr The text content
* \param nSizeFont The size of the text font
* \param ColMenuTextColor The color of the text
* \param nBord The thickness of the text border
* \param ColBorderColor The color of the text border
*
* **Example using**
* \code
* TxtTitle.setFont(AssetManager::GetFont(FONTH));
* InitText(TxtTitle, 200, 50, "Title", 200, sf::Color::White, 20, sf::Color::Black);
* \endcode
*/
void Game::InitText(sf::Text& TxtMtext, float fXpos, float fYpos, const sf::String StrStr,
    int nSizeFont, sf::Color ColMenuTextColor, int nBord, sf::Color ColBorderColor) 
{
    TxtMtext.setCharacterSize(nSizeFont);
    TxtMtext.setPosition(fXpos, fYpos);
    TxtMtext.setString(StrStr);
    TxtMtext.setFillColor(ColMenuTextColor);
    TxtMtext.setOutlineThickness(nBord);
    TxtMtext.setOutlineColor(ColBorderColor);

}

/**
* \brief The method that reads settings values from file
* \param settingValues The struct in which values will be saved
* \param sNameFile The file with values
*
* **Example using**
* \code
* SettingsValues settingsValues;
* ReadValues(settingsValues, "source/values.txt");
* \endcode
*/
void Game::ReadValues(SettingsValues& settingValues, std::string sFileName) 
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

/**
* \brief The method that delete values in file
* \param sNameFile The file where values will be deleted
*
* **Example using**
* \code
* ClearValues("source/values.txt");
* \endcode
*/
void Game::ClearValues(std::string sFileName)
{
    std::ofstream file(sFileName, std::ios_base::trunc); 
    file.close();
}

/**
* \brief The method that write settings values to file
* \param settingValues The struct in which values are saved
* \param sNameFile The file where values will be saved
*
* **Example using**
* \code
* SettingsValues settingsValues;
* WriteValues(settingsValues, "source/values.txt");
* \endcode
*/
void Game::WriteValues(SettingsValues settingValues, const std::string& sFileName)
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


/**
* \brief The method that create window with parameters from file
*/
void Game::createWindow()
{
    ReadValues(settingsValues, VALUES);
    setWidth(settingsValues.getWidth()); setHeight(settingsValues.getHeight()); 

    // creating of the main window
    if(settingsValues.getFullscreen()) WWin.create(sf::VideoMode::getDesktopMode(), vecTitles[settingsValues.getLanguage()], sf::Style::Fullscreen);
    else                WWin.create(sf::VideoMode::getDesktopMode(), vecTitles[settingsValues.getLanguage()], sf::Style::Titlebar);

    WWin.setMouseCursorVisible(false);
    WWin.setSize(sf::Vector2u(getWidth(), getHeight()));

    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[0]));

    sf::Image IIcon;
    if (!IIcon.loadFromFile(ICON)) exit(4);
    WWin.setIcon(32, 32, IIcon.getPixelsPtr());
}

/**
* \brief The method that show main window
*/
void Game::mainloop()
{
    Gameplay myPlay(WWin);
    sf::Text TxtTitle;
    std::vector<sf::String> vecNameMenu{ vecTitles[2 + settingsValues.getLanguage()],
    vecTitles[4 + settingsValues.getLanguage()], vecTitles[6 + settingsValues.getLanguage()],
    vecTitles[8 + settingsValues.getLanguage()] };
    GameMenu myMenu(WWin, 950, 350, 100, 120, vecNameMenu);

    // title
    TxtTitle.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtTitle, settingsValues.getTitle(), 50, vecTitles[settingsValues.getLanguage()], 
        200, sf::Color::White, 20, sf::Color::Black);

    // background
    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[0]));

    // menu
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    std::tuple<sf::RectangleShape, sf::Text> tDrawElements(RSBackground, TxtTitle);

    while (WWin.isOpen())
    {
        sf::Event EEvent;
        while (WWin.pollEvent(EEvent))
        {
            if (EEvent.type == sf::Event::KeyReleased)
            {
                if (EEvent.key.code == sf::Keyboard::Up)    {myMenu.MoveUp(); }       
                if (EEvent.key.code == sf::Keyboard::Down)  {myMenu.MoveDown(); }  
                if (EEvent.key.code == sf::Keyboard::Return)                                    
                {
                    switch (myMenu.getSelectedMenuNumber())
                    {
                    case 0: myPlay.LevelMenu();  break;
                    case 1: Settings();          break;
                    case 2: AboutGame();         break;
                    case 3: WWin.close();        break;

                    default: break;
                    }
                }
            }
        }

        WWin.clear();

        WinDraw(WWin, tDrawElements);
        myMenu.Draw();

        WWin.display();
    }
}


/**
* \brief The method that sets up title, background and menu of the settings windows
* \param TxtSettings The title which will be displayed on the window
* \param myMenu The menu which will be displayed on the window
*
* **Example using**
* \code
* sf::Text TxtSettings;
* std::vector<sf::String> vecNameMenu{ "Stick", "Man", "To settings" };
* GameMenu myMenu(WWin, 950, 350, 100, 120, vecNameMenu);
* SettingsWindow(TxtSettings, myMenu);
* \endcode
*/
void Game::SettingsWindow(sf::Text& TxtSettings, GameMenu& myMenu)
{
    // title
    TxtSettings.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtSettings, settingsValues.getSettingTitle(), 50, vecTitles[4 + settingsValues.getLanguage()],
        200, sf::Color::White, 20, sf::Color::Black);

    // background
    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[1]));

    // menu
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);
}

/**
* \brief The method that show settings window
*/
void Game::Settings()
{
    sf::Text TxtSettings;
    std::vector<sf::String> vecNameMenu{ vecTitles[16 + settingsValues.getLanguage()],
    vecTitles[18 + settingsValues.getLanguage()], vecTitles[30 + settingsValues.getLanguage()],
    vecTitles[14 + settingsValues.getLanguage()] };
    GameMenu myMenu(WWin, 950, 350, 100, 120, vecNameMenu);

    SettingsWindow(TxtSettings, myMenu);

    std::tuple<sf::RectangleShape, sf::Text> tDrawElements(RSBackground, TxtSettings);

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
                    case 1: SettingsSkin();      break;
                    case 2: SettingsScreen();    break;
                    case 3: mainloop();          break;

                    default: break;
                    }
                }
            }
        }

        WWin.clear();

        WinDraw(WWin, tDrawElements);
        myMenu.Draw();

        WWin.display();
    }
}

/**
* \brief The method that show language settings window
*/
void Game::SettingsLanguage()
{
    sf::Text TxtSettings;
    std::vector<sf::String> vecNameMenu{ vecTitles[10 + settingsValues.getLanguage()], 
        vecTitles[12 + settingsValues.getLanguage()], vecTitles[24 + settingsValues.getLanguage()] };
    GameMenu myMenu(WWin, 950, 350, 100, 120, vecNameMenu);

    SettingsWindow(TxtSettings, myMenu);

    std::tuple<sf::RectangleShape, sf::Text> tDrawElements(RSBackground, TxtSettings);

    while (WWin.isOpen())
    {
        sf::Event EEvent;
        while (WWin.pollEvent(EEvent))
        {
            if (EEvent.type == sf::Event::KeyReleased)
            {
                if (EEvent.key.code == sf::Keyboard::Up)    { myMenu.MoveUp(); }
                if (EEvent.key.code == sf::Keyboard::Down)  { myMenu.MoveDown(); }
                if (EEvent.key.code == sf::Keyboard::Return)
                {
                    switch (myMenu.getSelectedMenuNumber())
                    {
                    case 0: {settingsValues.setLanguageValues(0, 573, 469.5); }  break;
                    case 1: {settingsValues.setLanguageValues(1, 244, 231.5); }  break;
                    case 2: Settings();                                          return;

                    default: break;
                    }

                    ClearValues(VALUES); WriteValues(settingsValues, VALUES); SettingsLanguage();
                }
            }
        }

        WWin.clear();

        WinDraw(WWin, tDrawElements);
        myMenu.Draw();

        WWin.display();
    }
}

/**
* \brief The method that show skin settings window
*/
void Game::SettingsSkin()
{
    sf::Text TxtSettings;
    std::vector<sf::String> vecNameMenu{ vecTitles[20 + settingsValues.getLanguage()], 
        vecTitles[22 + settingsValues.getLanguage()], vecTitles[24 + settingsValues.getLanguage()] };
    GameMenu myMenu(WWin, 950, 350, 100, 120, vecNameMenu);

    SettingsWindow(TxtSettings, myMenu);

    std::tuple<sf::RectangleShape, sf::Text> tDrawElements(RSBackground, TxtSettings);

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
                    case 0: settingsValues.setSkin(0);   break;
                    case 1: settingsValues.setSkin(1);   break;
                    case 2: Settings();                  return;

                    default: break;
                    }

                    ClearValues(VALUES); WriteValues(settingsValues, VALUES);
                }
            }
        }

        WWin.clear();

        WinDraw(WWin, tDrawElements);
        myMenu.Draw();

        WWin.display();
    }
}

/**
* \brief The method that show screen settings window
*/
void Game::SettingsScreen()
{
    sf::Text TxtSettings;
    std::vector<sf::String> vecNameMenu{ "1024*576", "1280*720", "1920*1080", vecTitles[32 + settingsValues.getLanguage()], 
        vecTitles[24 + settingsValues.getLanguage()] };
    GameMenu myMenu(WWin, 950, 350, 100, 120, vecNameMenu);

    SettingsWindow(TxtSettings, myMenu);

    std::tuple<sf::RectangleShape, sf::Text> tDrawElements(RSBackground, TxtSettings);

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

                    ClearValues(VALUES); WriteValues(settingsValues, VALUES); 
                    setWidth(settingsValues.getWidth()); 
                    setHeight(settingsValues.getHeight());  
                    createWindow(); 
                    SettingsScreen();
                }
            }
        }

        WWin.clear();

        WinDraw(WWin, tDrawElements);
        myMenu.Draw();

        WWin.display();
    }
}


/**
* \brief The method that show about game window
*/
void Game::AboutGame()
{
    sf::Text TxtAbout, TxtExit;

    // text about game
    TxtAbout.setFont(AssetManager::GetFont(FONTM));
    InitText(TxtAbout, 277, 150, vecAbout[settingsValues.getLanguage()], 50, sf::Color::White, 3, sf::Color::Black);

    // exit tip
    TxtExit.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtExit, 50, 50, "Press escape to return to the main menu", 50, sf::Color::Magenta, 5, sf::Color::Black);

    // background
    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[2]));

    std::tuple<sf::RectangleShape, sf::Text, sf::Text> tDrawElements(RSBackground, TxtAbout, TxtExit);

    while (WWin.isOpen())
    {
        sf::Event EEvent;
        while (WWin.pollEvent(EEvent))
        {
            if (EEvent.type == sf::Event::Closed) mainloop();
            if ((EEvent.type == sf::Event::KeyPressed) && (EEvent.key.code == sf::Keyboard::Escape)) mainloop();
        }
        WWin.clear();

        WinDraw(WWin, tDrawElements);

        WWin.display();
    }
}