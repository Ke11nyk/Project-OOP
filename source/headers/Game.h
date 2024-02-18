#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "GameMenu.h"
#include "AssetManager.h"
#include "Animator.h"
#include "Player.h"
#include "SettingsValues.h"
#include <iostream>
#include <vector>
#include <fstream>


class Game
{
    AssetManager manager;

    // settings
    std::vector<sf::String> vecTitles = { "Run to exit", L"Біжи до виходу", "Start", L"Старт", "Settings", L"Налаштування", "About game", L"Про гру", "Exit", L"Вихід", "English", "English", L"Українська", L"Українська", "To menu", L"До меню", "Language", L"Мова", "Character", L"Персонаж", "Stickman", L"Стікмен", 
        "Man", L"Поц", "To settings", L"До налаштувань", "Points: ", L"Очки: ", "Time: ", L"Час: ", "Screen", L"Екран", "Fullscreen", L"Повний екран", "level", L"рівень",
                              L"Біжи до виходу",  L"Старт", L"Налаштування", L"Про гру", L"Вихід", "English", L"Українська", L"До меню", L"Мова", L"Персонаж", L"Стікмен", 
        L"Поц", L"До налаштувань", L"Очки: ", L"Час: ", L"Екран", L"Повний екран", L"рівень"};

    std::vector<sf::String> vecAbout = {"A game about a stickman who needs to get to the door by \njumping on platforms.\
 Originally implemented in Python, the \ncurrent implementation is in C++ using the SFML library. \n\n\
Currently, a static level is implemented. \nRandomization of levels, endless mode are planned. \
    \n\nMade by Artem Verbytskyi as part of a project for OOOP \
    \n\n\n\n\nCopyright © 2023 by Ke11nyk", L"Гра про стікмена, якому потрібно дістатися до дверей, \nстрибаючи по платформам\
  Спочатку реалізовано на Python, \nпоточна реалізація на C++ з використанням бібліотеки SFML. \n\n\
На даний момент реалізований статичний рівень. \nПланується рандомізація рівнів, нескінченний режим. \
     \n\nВиконано Артемом Вербицьким в рамках проекту для ОООП \
     \n\n\n\n\nCopyright © 2023 by Ke11nyk" };

    std::vector<sf::String> vecSkin = { "source/images/figure.png", "source/images/figure1.png" };

    std::vector<sf::String> vecBackground = { "source/images/background.png" , "source/images/settings.png" , "source/images/about(1).png", "source/images/level1(1).png" };

    std::vector<sf::String> vecTexture = { "source/images/plat.png", "source/images/plat1.png", "source/images/door.png", "source/images/door1.png" };

    SettingsValues settingsValues;

    // main window
    sf::RenderWindow WWin;
    sf::Image IIcon;
    sf::RectangleShape RSBackground;
    sf::Text TxtTitle;
    bool bFullscreen;

    // other windows
    sf::Text TxtSettings;
    sf::Text TxtAbout;

    // player
    sf::Time TTm;
    sf::Sprite SPlayerSprite;
    Animator PlayerAnim = Animator(SPlayerSprite);

    sf::Text TxtPoints;
    int nPoints = 0;

    // states of game
    bool bPreEx = false;
    bool bEndLevel = false;
    bool bDoorOpened = false;

    // map of level
    sf::Sprite SPlat;
    sf::Sprite SDoor;

    int nTs = 50;

    std::vector<sf::String> vecTileMap;

    // camera
    float fOffsetX = 0, fOffsetY = 0;

    // size of window
    int nWidth = sf::VideoMode::getDesktopMode().width;
    int nHeight = sf::VideoMode::getDesktopMode().height;

    // size of background
    int nBgWidth = settingsValues.getWidth();
    int nBgHeight = settingsValues.getHeight();


    void InitText(sf::Text& TxtMtext, float fXpos, float fYpos, const sf::String StrStr, 
        int nSizeFont, sf::Color ColMenuTextColor, int nBord, sf::Color ColBorderColor);
    void LevelMenu();
    void Level();
    void Settings();
    void SettingsLanguage();
    void SettingsPers();
    void SettingsScreen();
    void AboutGame();
    void input(Player& stick);
    void update(sf::Time const& TDeltaTime, Player& stick);
    void Camera(Player& stick, std::vector<sf::String> vecTileMap);
    void drawMap(std::vector<sf::String> vecTileMap, int nSize);
    void readMap(std::vector<sf::String>& vecTileMap, int nLevel);
    void readValues(std::vector<int>& vecValues, std::string sNameFile);
    void readValues(SettingsValues& settingValues, std::string sNameFile);
    void writeValues(const std::vector<int>& vecValues, const std::string& sNameFile);
    void writeValues(const SettingsValues settingValues, const std::string& sNameFile);
    void clearValues(std::string sNameFile);
    void preExit();
    void endOfTheLevel(int nStart, int& nFinish, sf::Clock CTimer, bool& bTimer);
    

public:
    void createWindow();
    void mainloop();
    

    int getPoints()
    {
        return nPoints;
    }

    void setPoints(int nValue)
    {
        nPoints = nValue;
    }

    void setOffsetX(float fX)
    {
        fOffsetX = fX;
    }

    float getOffsetX()
    {
        return fOffsetX;
    }

    void setOffsetY(float fY)
    {
        fOffsetY = fY;
    }

    float getOffsetY()
    {
        return fOffsetY;
    }

    void setWidth(int nValue)
    {
        nWidth = nValue;
    }

    int getWidth()
    {
        return nWidth;
    }

    void setHeight(int nValue)
    {
        nHeight = nValue;
    }

    int getHeight()
    {
        return nHeight;
    }

    void setFullscreen(bool bValue)
    {
        bFullscreen = bValue;
    }

    bool getFullscreen()
    {
        return bFullscreen;
    }

    void setTs(int nValue)
    {
        nTs = nValue;
    }

    int getTs()
    {
        return nTs;
    }

    void setDoorOpened(bool bValue)
    {
        bDoorOpened = bValue;
    }

    bool getDoorOpened()
    {
        return bDoorOpened;
    }

    void setPreEx(bool bValue)
    {
        bPreEx = bValue;
    }

    bool getPreEx()
    {
        return bPreEx;
    }

    void setEndLevel(bool bValue)
    {
        bEndLevel = bValue;
    }

    bool getEndLevel()
    {
        return bEndLevel;
    }
};
