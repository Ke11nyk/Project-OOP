#include "../headers/Gameplay.h"

#define VALUES "source/values.txt"
#define FONTH "source/fontes/Gilroy-Heavy.woff"
#define FONTM "source/fontes/Gilroy-Medium.woff"
#define BACKGROUND "source/images/level(1).png"
#define EXIT "source/images/exit.png"
#define LEVEL "source/maps/level"

Gameplay::Gameplay(sf::RenderWindow& WWindow)
    :WWin(WWindow) {}

void Gameplay::InitText(sf::Text& TxtMtext, float fXpos, float fYpos, const sf::String StrStr,
    int nSizeFont, sf::Color ColMenuTextColor, int nBord, sf::Color ColBorderColor) // text formatting 
{
    TxtMtext.setCharacterSize(nSizeFont);
    TxtMtext.setPosition(fXpos, fYpos);
    TxtMtext.setString(StrStr);
    TxtMtext.setFillColor(ColMenuTextColor);
    TxtMtext.setOutlineThickness(nBord);
    TxtMtext.setOutlineColor(ColBorderColor);

}

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


void Gameplay::Input(Player& stick, bool& bGameplayState)
{
    sf::Event EEvent;

    while (WWin.pollEvent(EEvent))
    {
        //if (event.type == sf::Event::Closed) mainloop();
        if (EEvent.type == sf::Event::KeyPressed)
        {
            if ((EEvent.key.code == sf::Keyboard::Escape) && ((getPreEx()) || (getEndLevel()))) bGameplayState = false;

            if (EEvent.key.code == sf::Keyboard::Escape) setPreEx(true);
            if (EEvent.key.code == sf::Keyboard::Space) setPreEx(false);
        }

        stick.Keys(EEvent); // player sprite control
    }
}

void Gameplay::Update(sf::Time const& TDeltaTime, Player& stick)
{
    stick.update(TDeltaTime);

    TTm += TDeltaTime;
    if (TTm > sf::milliseconds(2))
    {
        setPoints(stick.getPoints());

        TTm = sf::milliseconds(0);
    }
}

void Gameplay::Camera(Player& stick, std::vector<sf::String> vecTileMap)
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


// map
void Gameplay::DrawMap(std::vector<sf::String> vecTileMap, int nSize)
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

void Gameplay::ReadMap(std::vector<sf::String>& vecTileMap, int nLevel) 
{
    std::ifstream file(LEVEL + std::to_string(nLevel) + ".txt");
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


// work with settings values in file
void Gameplay::ReadValues(SettingsValues& settingValues, std::string sFileName) 
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


// states of game
void Gameplay::LevelMenu()
{
    std::vector<sf::String> vecNameMenu{ "1 " + vecTitles[settingsValues.getLanguage()],
    "2 " + vecTitles[settingsValues.getLanguage()], "3 " + vecTitles[settingsValues.getLanguage()],
    "4 " + vecTitles[settingsValues.getLanguage()], "5 " + vecTitles[settingsValues.getLanguage()] };
    GameMenu myMenu(WWin, 300, 250, 100, 120, vecNameMenu);
    sf::RectangleShape RSPanel;
    sf::Text TxtExit;
    bool bMap = true;
    int nStart = 1, nEnd = 6;

    ReadValues(settingsValues, VALUES);
    ReadMap(vecTileMap, 1);  // assign a first-level map

    // background
    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[0]));

    // menu
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    // background of map
    RSPanel.setSize(sf::Vector2f(1240, 540));
    RSPanel.setPosition(sf::Vector2f(650, 270));
    RSPanel.setTexture(&AssetManager::GetTexture(BACKGROUND));

    // exit tip
    TxtExit.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtExit, 50, 50, vecTitles[2 + settingsValues.getLanguage()], 50, sf::Color::Magenta, 5, sf::Color::Black);

    setTs(25);
    setOffsetX(-650);
    setOffsetY(-270);

    std::tuple<sf::RectangleShape, sf::Text> tDrawElements(RSBackground, TxtExit);

    while (WWin.isOpen())
    {
        sf::Event EEvent;
        while (WWin.pollEvent(EEvent))
        {
            if ((EEvent.type == sf::Event::KeyPressed) && (EEvent.key.code == sf::Keyboard::Escape)) return;

            if (EEvent.type == sf::Event::KeyReleased)
            {
                if (EEvent.key.code == sf::Keyboard::Up)
                {
                    myMenu.MoveUp(); 
                    ReadMap(vecTileMap, myMenu.getSelectedMenuNumber() + 1);
                }

                if (EEvent.key.code == sf::Keyboard::Down)
                {
                    if ((myMenu.getSelectedMenuNumber() == nEnd + 1) && (nEnd + 1 < 6))
                    {
                        nStart++;
                        nEnd++;
                    }
                    
                    myMenu.MoveDown();
                    ReadMap(vecTileMap, myMenu.getSelectedMenuNumber() + 1);
                }

                if (EEvent.key.code == sf::Keyboard::Return) 
                { 
                    Level(); 
                    return; 
                }
            }
        }

        WWin.clear();

        WinDraw(WWin, tDrawElements);

        if (bMap)
        {
            WWin.draw(RSPanel);
            DrawMap(vecTileMap, 1);
        }

        myMenu.draw();

        WWin.display();
    }
}

void Gameplay::Level()
{
    bGameplayState = true;
    Player stick = Player(WWin, vecTileMap, vecSkin[settingsValues.getSkin()], 3 + 2 * settingsValues.getSkin());
    sf::Clock CClock, CTimer;
    bool bTimer = false;
    int nStart = CClock.getElapsedTime().asSeconds(), nFinish;

    // player
    stick.setTexture(vecSkin[settingsValues.getSkin()]);

    // background
    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[3]));

    setTs(50);
    setOffsetX(0);
    setOffsetY(0);
    setPreEx(false);
    setEndLevel(false);

    while (WWin.isOpen())
    {
        sf::Time TDt = CClock.restart();

        setDoorOpened(stick.getDoorOpened());

        Input(stick, bGameplayState);
        if (!bGameplayState) return;
        if ((!bPreEx) && (!bEndLevel)) Update(TDt, stick);

        WWin.clear();

        auto drawStick = stick.getStick();
        std::tuple<sf::RectangleShape, sf::Sprite> tDrawElements(RSBackground, drawStick);

        WinDraw(WWin, tDrawElements);

        Camera(stick, vecTileMap);
        DrawMap(vecTileMap, 0);

        if (getPreEx()) PreExit();
        if (getEndLevel()) EndOfTheLevel(nStart, nFinish, CTimer, bTimer);

        WWin.display();
    }
}

void Gameplay::PreExit()
{
    sf::RectangleShape RSPanel;
    sf::Text TxtExit;

    // exit panel
    RSPanel.setSize(sf::Vector2f(800, 400));
    RSPanel.setPosition(sf::Vector2f(nBgWidth / 2 - 400, nBgHeight / 2 - 200));
    RSPanel.setTexture(&AssetManager::GetTexture(EXIT));

    // text on exit panel
    TxtExit.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtExit, nBgWidth / 2 - 360, nBgHeight / 2 - 170, vecTitles[4 + settingsValues.getLanguage()], 50, sf::Color::White, 5, sf::Color::Black);

    WWin.draw(RSPanel);
    WWin.draw(TxtExit);
}

void Gameplay::EndOfTheLevel(int nStart, int& nFinish, sf::Clock CTimer, bool& bTimer)
{
    sf::RectangleShape RSPanel;
    sf::Text TxtExit;

    // exit panel
    RSPanel.setSize(sf::Vector2f(800, 400));
    RSPanel.setPosition(sf::Vector2f(nBgWidth / 2 - 400, nBgHeight / 2 - 200));
    RSPanel.setTexture(&AssetManager::GetTexture(EXIT));


    if (!bTimer)
    {
        nFinish = CTimer.getElapsedTime().asSeconds();
        bTimer = true;
    }
    int nTime = nFinish - nStart;

    // text on exit panel
    TxtExit.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtExit, nBgWidth / 2 - 360, nBgHeight / 2 - 170, vecTitles[6 + settingsValues.getLanguage()] 
        + std::to_string(getPoints()) + vecTitles[8 + settingsValues.getLanguage()] + std::to_string(nTime / 60) 
        + vecTitles[10 + settingsValues.getLanguage()] + std::to_string(nTime - nTime / 60 * 60) 
        + vecTitles[12 + settingsValues.getLanguage()], 50, sf::Color::White, 5, sf::Color::Black);

    WWin.draw(RSPanel);
    WWin.draw(TxtExit);
}