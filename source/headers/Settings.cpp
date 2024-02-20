#include "Settings.h"

#define VALUES "source/values.txt"
#define FONTH "source/fontes/Gilroy-Heavy.woff"
#define FONTM "source/fontes/Gilroy-Medium.woff"


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

void Settings::InitText(sf::Text& TxtMtext, float fXpos, float fYpos, const sf::String StrStr,
    int nSizeFont, sf::Color ColMenuTextColor, int nBord, sf::Color ColBorderColor) // text formatting 
{
    TxtMtext.setCharacterSize(nSizeFont);
    TxtMtext.setPosition(fXpos, fYpos);
    TxtMtext.setString(StrStr);
    TxtMtext.setFillColor(ColMenuTextColor);
    TxtMtext.setOutlineThickness(nBord);
    TxtMtext.setOutlineColor(ColBorderColor);

}

// work with settings values in file
void Settings::readValues(SettingsValues& settingValues, std::string sFileName) // reading a map from a text document and assigning it to an array
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

void Settings::clearValues(std::string sFileName)
{
    std::ofstream file(sFileName, std::ios_base::trunc); //Видаляє вміст існуючого файлу при створенні його керуючого об'єкта.
    file.close();
}

void Settings::writeValues(SettingsValues settingValues, const std::string& sFileName)
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
void Settings::main(sf::RenderWindow& WWin)
{
    readValues(settingsValues, VALUES);

    TxtSettings.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtSettings, settingsValues.getSettingTitle(), 50, vecTitles[4 + settingsValues.getLanguage()], 200, sf::Color::White, 20, sf::Color::Black);

    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[1]));

    std::vector<sf::String> vecNameMenu{ vecTitles[16 + settingsValues.getLanguage()], vecTitles[18 + settingsValues.getLanguage()], vecTitles[30 + settingsValues.getLanguage()], vecTitles[14 + settingsValues.getLanguage()] };
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
                    case 0: Language(WWin);  return;  break;
                    case 1: Skin(WWin);      break;
                    case 2: Screen(WWin);    break;
                    case 3: return;          break;

                    default: break;
                    }
                }
            }
        }

        WWin.clear();

        std::tuple<sf::RectangleShape, sf::Text> t(RSBackground, TxtSettings);
        WinDraw(WWin, t);

        myMenu.draw();
        WWin.display();
    }
}


void Settings::Language(sf::RenderWindow& WWin)
{
    
    TxtSettings.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtSettings, settingsValues.getSettingTitle(), 50, vecTitles[4 + settingsValues.getLanguage()], 200, sf::Color::White, 20, sf::Color::Black);

    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[1]));

    std::vector<sf::String> vecNameMenu{ vecTitles[10 + settingsValues.getLanguage()], vecTitles[12 + settingsValues.getLanguage()], vecTitles[24 + settingsValues.getLanguage()] };
    GameMenu myMenu(WWin, 950, 350, 100, 120, vecNameMenu);
    myMenu.setColorTextMenu(sf::Color::White, sf::Color::Red, sf::Color::Black);
    myMenu.AlignMenu(2);

    while (WWin.isOpen())
    {
        readValues(settingsValues, VALUES);
        std::vector<sf::String> vecNameMenuN{ vecTitles[10 + settingsValues.getLanguage()], vecTitles[12 + settingsValues.getLanguage()], vecTitles[24 + settingsValues.getLanguage()] };
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
                    case 0: {settingsValues.setLanguageValues(0, 573, 469.5); myMenu.setVecMainMenu(vecNameMenuN); }  break;
                    case 1: {settingsValues.setLanguageValues(1, 244, 231.5); myMenu.setVecMainMenu(vecNameMenuN); }  break;
                    case 2: return;                                              break;

                    default: break;
                    }

                    clearValues(VALUES); writeValues(settingsValues, VALUES); /*Language(WWin); return;*/
                }
            }
        }

        WWin.clear();

        std::tuple<sf::RectangleShape, sf::Text> t(RSBackground, TxtSettings);
        WinDraw(WWin, t);

        myMenu.draw();
        WWin.display();
    }
}

void Settings::Skin(sf::RenderWindow& WWin)
{
    TxtSettings.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtSettings, settingsValues.getSettingTitle(), 50, vecTitles[4 + settingsValues.getLanguage()], 200, sf::Color::White, 20, sf::Color::Black);

    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[1]));

    std::vector<sf::String> vecNameMenu{ vecTitles[20 + settingsValues.getLanguage()], vecTitles[22 + settingsValues.getLanguage()], vecTitles[24 + settingsValues.getLanguage()] };
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
                    case 2: return;                         break;

                    default: break;
                    }

                    clearValues(VALUES); writeValues(settingsValues, VALUES); return;
                }
            }
        }

        WWin.clear();

        std::tuple<sf::RectangleShape, sf::Text> t(RSBackground, TxtSettings);
        WinDraw(WWin, t);

        myMenu.draw();
        WWin.display();
    }
}

void Settings::Screen(sf::RenderWindow& WWin)
{
    TxtSettings.setFont(AssetManager::GetFont(FONTH));
    InitText(TxtSettings, settingsValues.getSettingTitle(), 50, vecTitles[4 + settingsValues.getLanguage()], 200, sf::Color::White, 20, sf::Color::Black);

    RSBackground.setSize(sf::Vector2f(nBgWidth, nBgHeight));
    RSBackground.setTexture(&AssetManager::GetTexture(vecBackground[1]));

    std::vector<sf::String> vecNameMenu{ "1024*576", "1280*720", "1920*1080", vecTitles[32 + settingsValues.getLanguage()], vecTitles[24 + settingsValues.getLanguage()] };
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
                    case 4: return;                                                break;

                    default: break;
                    }

                    clearValues(VALUES); writeValues(settingsValues, VALUES); return;
                    /*setWidth(settingsValues.getWidth());
                    setHeight(settingsValues.getHeight());
                    createWindow();
                    SettingsScreen();*/
                }
            }
        }

        WWin.clear();

        std::tuple<sf::RectangleShape, sf::Text> t(RSBackground, TxtSettings);
        WinDraw(WWin, t);

        myMenu.draw();
        WWin.display();
    }
}